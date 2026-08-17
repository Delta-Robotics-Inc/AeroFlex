#include <Arduino.h>
#include <stdio.h>

// AeroFlex test-rig: bottom-zero, two-speed travel commissioning.
//
// HARD RULES:
//   1. The physical bottom switch defines position 0 for every test.
//   2. No upward test travel is allowed until bottom homing succeeds.
//   3. Upward pulses always check D12; downward pulses always check D11.
//   4. A long traverse is limited to 350 mm fast plus 50 mm slow seeking.
//   5. Distance reported here is step-count estimated. It becomes independently
//      measured distance only after verified encoder feedback is integrated.
//
// This program NEVER moves on boot. Motion requires a serial command.
//
// Confirmed wiring:
//   D6 (purple) -> DM542T PUL+     GND (white/gray) -> PUL-
//   D5 (blue)   -> DM542T DIR+     GND (white/gray) -> DIR-
//   Top switch: D12 (purple) to GND (orange), active LOW
//   Bottom switch: D11 (yellow) to GND (orange), active LOW
//   Encoder A candidate: D3 (gray), B: D2 (white), 5V: red, GND: black

namespace {

constexpr uint8_t kStepPin = 6;
constexpr uint8_t kDirectionPin = 5;
constexpr uint8_t kTopLimitPin = 12;
constexpr uint8_t kBottomLimitPin = 11;
constexpr uint8_t kEncoderAPin = 3;
constexpr uint8_t kEncoderBPin = 2;

// Commissioning observation: D5 HIGH drove the carriage physically downward
// toward D11. Therefore physical UP requires D5 LOW.
constexpr bool kUpDirectionHigh = false;
constexpr long kPulsesPerMotorRevolution = 1600;
constexpr long kEncoderCountsPerRevolution = 1600;

// Confirmed working estimate. Override for a session with l<mm> if calibration
// improves. At 3.80 +/- 0.19 mm/rev, step-estimated distance has about +/-5%
// uncertainty before encoder verification.
float leadScrewLeadMmPerRevolution = 3.80f;

constexpr float kReportedApproximateTravelMm = 360.0f;
constexpr float kFastTraverseMm = 350.0f;
constexpr float kSlowSeekAllowanceMm = 50.0f;
constexpr float kFastStartPulseRate = 250.0f;
constexpr float kFastCruisePulseRate = 1600.0f;
constexpr float kTopSeekCruisePulseRate = 800.0f;
constexpr float kSlowSeekPulseRate = 250.0f;
// Manual test motion is deliberately bounded. The app sends x when its hold
// control is released, but firmware also caps an individual hold command at
// about 4 mm using the current, uncalibrated lead estimate.
constexpr long kManualJogPulses = 200;
constexpr float kManualJogPulseRate = 100.0f;
constexpr long kManualHoldMaxPulses = 1684;
constexpr unsigned long kManualHoldMaxDurationMs = 10000;
constexpr float kManualHoldMinPulseRate = 10.0f;
constexpr float kManualHoldMaxPulseRate = 400.0f;
constexpr long kFastRampPulses = 8000;
constexpr long kTopSeekRampPulses = 1000;
constexpr float kDepartureReleaseCheckMm = 2.0f;
constexpr unsigned long kDebounceMs = 30;
constexpr unsigned long kTelemetryIntervalMs = 200;
constexpr unsigned long kDiagnosticTelemetryIntervalMs = 1000;

struct LimitSwitch {
  uint8_t pin;
  const __FlashStringHelper* name;
  bool stablePressed;
  bool lastRawPressed;
  unsigned long lastRawChangeAt;
};

enum class StopReason {
  Completed,
  DirectionalLimit,
  SerialAbort,
};

struct MoveResult {
  long pulsesSent;
  StopReason reason;
};

struct EncoderSnapshot {
  long count;
  unsigned long aEdges;
  unsigned long bEdges;
  unsigned long invalidTransitions;
  bool aHigh;
  bool bHigh;
};

LimitSwitch topLimit{kTopLimitPin, F("TOP"), false, false, 0};
LimitSwitch bottomLimit{kBottomLimitPin, F("BOTTOM"), false, false, 0};

bool bottomPressSeenSinceBoot = false;
bool bottomLimitValidated = false;
bool bottomReferenceKnown = false;
bool topReferenceKnown = false;
long positionFromBottomPulses = 0;
long lastDownTravelPulses = 0;
long lastUpTravelPulses = 0;

volatile long encoderCount = 0;
volatile unsigned long encoderAEdges = 0;
volatile unsigned long encoderBEdges = 0;
volatile unsigned long encoderInvalidTransitions = 0;
volatile uint8_t encoderPreviousState = 0;

const char* motionPhase = "idle";
const char* motionDirection = "none";
bool motionActive = false;
bool motionPositionValid = false;
long motionPositionBasePulses = 0;
long motionPulsesSent = 0;
long motionPulsesRequested = 0;
unsigned int motionPulseRate = 0;
unsigned long lastTelemetryAt = 0;
unsigned long lastDiagnosticTelemetryAt = 0;

// Four-times quadrature decoder. Sign only defines the provisional direction;
// testing will establish whether positive means carriage up or down.
constexpr int8_t kQuadratureDelta[16] = {
    0,  1, -1, 0,
   -1,  0,  0, 1,
    1,  0,  0, -1,
    0, -1,  1, 0,
};

void encoderEdgeIsr() {
  const bool aHigh = digitalRead(kEncoderAPin) == HIGH;
  const bool bHigh = digitalRead(kEncoderBPin) == HIGH;
  const uint8_t currentState =
      (static_cast<uint8_t>(aHigh) << 1) | static_cast<uint8_t>(bHigh);
  const uint8_t changed = encoderPreviousState ^ currentState;

  if (changed & 0b10) {
    ++encoderAEdges;
  }
  if (changed & 0b01) {
    ++encoderBEdges;
  }
  if (changed == 0b11) {
    ++encoderInvalidTransitions;
  } else {
    encoderCount +=
        kQuadratureDelta[(encoderPreviousState << 2) | currentState];
  }
  encoderPreviousState = currentState;
}

EncoderSnapshot snapshotEncoder() {
  noInterrupts();
  const EncoderSnapshot snapshot{
      encoderCount,
      encoderAEdges,
      encoderBEdges,
      encoderInvalidTransitions,
      digitalRead(kEncoderAPin) == HIGH,
      digitalRead(kEncoderBPin) == HIGH,
  };
  interrupts();
  return snapshot;
}

void resetEncoderDiagnostics() {
  noInterrupts();
  encoderCount = 0;
  encoderAEdges = 0;
  encoderBEdges = 0;
  encoderInvalidTransitions = 0;
  encoderPreviousState =
      (static_cast<uint8_t>(digitalRead(kEncoderAPin) == HIGH) << 1) |
      static_cast<uint8_t>(digitalRead(kEncoderBPin) == HIGH);
  interrupts();
  Serial.println(F("Encoder diagnostic counters reset. No motion commanded."));
}

void printEncoderStatus() {
  const EncoderSnapshot encoder = snapshotEncoder();
  Serial.println(F("Encoder diagnostic (motor motion is NOT commanded):"));
  Serial.print(F("  A candidate: gray D3 raw="));
  Serial.println(encoder.aHigh ? F("HIGH") : F("LOW"));
  Serial.print(F("  B: white D2 raw="));
  Serial.println(encoder.bHigh ? F("HIGH") : F("LOW"));
  Serial.print(F("  Quadrature count: "));
  Serial.println(encoder.count);
  Serial.print(F("  A edge count: "));
  Serial.println(encoder.aEdges);
  Serial.print(F("  B edge count: "));
  Serial.println(encoder.bEdges);
  Serial.print(F("  Invalid two-bit transitions: "));
  Serial.println(encoder.invalidTransitions);
  Serial.print(F("  Revolutions at 1600 counts/rev: "));
  Serial.println(
      static_cast<float>(encoder.count) / kEncoderCountsPerRevolution, 4);
  Serial.print(F("  Linear estimate at current lead (mm): "));
  Serial.println(static_cast<float>(encoder.count) *
                     leadScrewLeadMmPerRevolution /
                     kEncoderCountsPerRevolution,
                 3);
  Serial.println(F("  Count sign is provisional until UP/DOWN is observed."));
}

void printEncoderMoveComparison(const __FlashStringHelper* moveName,
                                long commandPulses,
                                const EncoderSnapshot& before,
                                const EncoderSnapshot& after) {
  const long encoderDelta = after.count - before.count;
  const unsigned long invalidDelta =
      after.invalidTransitions - before.invalidTransitions;
  Serial.print(moveName);
  Serial.println(F(" encoder comparison:"));
  Serial.print(F("  Command pulses emitted: "));
  Serial.println(commandPulses);
  Serial.print(F("  Encoder count delta: "));
  Serial.println(encoderDelta);
  Serial.print(F("  Absolute encoder/command ratio: "));
  if (commandPulses > 0) {
    Serial.println(static_cast<float>(labs(encoderDelta)) / commandPulses, 4);
  } else {
    Serial.println(F("n/a"));
  }
  Serial.print(F("  Encoder-estimated travel (mm): "));
  Serial.println(static_cast<float>(labs(encoderDelta)) *
                     leadScrewLeadMmPerRevolution /
                     kEncoderCountsPerRevolution,
                 3);
  Serial.print(F("  Invalid transitions during move: "));
  Serial.println(invalidDelta);
}

bool isPressed(uint8_t pin) {
  return digitalRead(pin) == LOW;
}

float pulsesPerMm() {
  return static_cast<float>(kPulsesPerMotorRevolution) /
         leadScrewLeadMmPerRevolution;
}

long mmToPulses(float mm) {
  return lroundf(mm * pulsesPerMm());
}

float pulsesToMm(long pulses) {
  return static_cast<float>(pulses) / pulsesPerMm();
}

void writeFrameIfReady(const char* frame, size_t length) {
  if (!Serial || length == 0 ||
      Serial.availableForWrite() < static_cast<int>(length)) {
    return;
  }
  Serial.write(reinterpret_cast<const uint8_t*>(frame), length);
}

void emitEvent(const char* level, const char* code,
               const char* reason = "none") {
  char frame[160];
  const int length =
      snprintf(frame, sizeof(frame),
               "@E v=1 ms=%lu level=%s code=%s reason=%s\n", millis(), level,
               code, reason);
  if (length > 0 && static_cast<size_t>(length) < sizeof(frame)) {
    writeFrameIfReady(frame, static_cast<size_t>(length));
  }
}

void beginMotionTelemetry(const char* phase, bool movingUp,
                          long requestedPulses, long sentOffset = 0) {
  motionPhase = phase;
  motionDirection = movingUp ? "up" : "down";
  motionActive = true;
  motionPositionValid = bottomReferenceKnown;
  motionPositionBasePulses =
      positionFromBottomPulses - (movingUp ? sentOffset : -sentOffset);
  motionPulsesSent = sentOffset;
  motionPulsesRequested = requestedPulses;
  motionPulseRate = 0;
  emitEvent("info", "motion_started", phase);
}

void endMotionTelemetry(StopReason reason) {
  if (reason == StopReason::SerialAbort) {
    emitEvent("warn", "motion_aborted", "serial_stop");
  } else if (reason == StopReason::DirectionalLimit) {
    emitEvent("info", "motion_stopped", "directional_limit");
  } else {
    emitEvent("info", "motion_segment_complete", motionPhase);
  }
  motionPhase = "idle";
  motionDirection = "none";
  motionActive = false;
  motionPositionValid = bottomReferenceKnown;
  motionPulseRate = 0;
}

void emitTelemetry(bool force = false) {
  const unsigned long now = millis();
  if (!force && now - lastTelemetryAt < kTelemetryIntervalMs) {
    return;
  }
  lastTelemetryAt = now;

  const EncoderSnapshot encoder = snapshotEncoder();
  const bool positionValid =
      motionActive ? motionPositionValid : bottomReferenceKnown;
  long positionPulses = positionFromBottomPulses;
  if (motionActive && motionPositionValid) {
    positionPulses = motionPositionBasePulses +
                     (motionDirection[0] == 'u' ? motionPulsesSent
                                                : -motionPulsesSent);
  }

  char positionMm[18];
  if (positionValid) {
    dtostrf(pulsesToMm(positionPulses), 0, 3, positionMm);
  } else {
    snprintf(positionMm, sizeof(positionMm), "nan");
  }

  char frame[256];
  const int length = snprintf(
      frame, sizeof(frame),
      "@T v=1 ms=%lu mot=%s dir=%s pps=%u sent=%ld req=%ld pv=%u "
      "posp=%ld posmm=%s enc=%ld inv=%lu top=%u bot=%u safe=%u bref=%u "
      "tref=%u\n",
      now, motionPhase, motionDirection, motionPulseRate, motionPulsesSent,
      motionPulsesRequested, positionValid ? 1U : 0U, positionPulses,
      positionMm, encoder.count, encoder.invalidTransitions,
      isPressed(kTopLimitPin) ? 1U : 0U,
      isPressed(kBottomLimitPin) ? 1U : 0U,
      bottomLimitValidated ? 1U : 0U, bottomReferenceKnown ? 1U : 0U,
      topReferenceKnown ? 1U : 0U);
  if (length > 0 && static_cast<size_t>(length) < sizeof(frame)) {
    writeFrameIfReady(frame, static_cast<size_t>(length));
  }

  if (force || now - lastDiagnosticTelemetryAt >=
                   kDiagnosticTelemetryIntervalMs) {
    lastDiagnosticTelemetryAt = now;
    char lead[16];
    dtostrf(leadScrewLeadMmPerRevolution, 0, 4, lead);
    char diagnostics[192];
    const int diagnosticLength = snprintf(
        diagnostics, sizeof(diagnostics),
        "@D v=1 ms=%lu ea=%lu eb=%lu ah=%u bh=%u lead=%s fs=unavail "
        "fv=0 fn=nan\n",
        now, encoder.aEdges, encoder.bEdges, encoder.aHigh ? 1U : 0U,
        encoder.bHigh ? 1U : 0U, lead);
    if (diagnosticLength > 0 &&
        static_cast<size_t>(diagnosticLength) < sizeof(diagnostics)) {
      writeFrameIfReady(diagnostics,
                        static_cast<size_t>(diagnosticLength));
    }
  }
}

void printState(const LimitSwitch& limit) {
  Serial.print(limit.name);
  Serial.println(limit.stablePressed ? F(" switch: PRESSED")
                                     : F(" switch: released"));
}

void printRawState(const LimitSwitch& limit) {
  const bool pressed = isPressed(limit.pin);
  Serial.print(limit.name);
  Serial.print(F(" D"));
  Serial.print(limit.pin);
  Serial.print(F(" raw="));
  Serial.print(pressed ? F("LOW (pressed)") : F("HIGH (released)"));
  Serial.print(F("; debounced="));
  Serial.println(limit.stablePressed ? F("pressed") : F("released"));
}

void updateLimit(LimitSwitch& limit, unsigned long now) {
  const bool rawPressed = isPressed(limit.pin);
  if (rawPressed != limit.lastRawPressed) {
    limit.lastRawPressed = rawPressed;
    limit.lastRawChangeAt = now;
  }

  if (rawPressed != limit.stablePressed &&
      now - limit.lastRawChangeAt >= kDebounceMs) {
    limit.stablePressed = rawPressed;
    printState(limit);

    if (limit.pin == kBottomLimitPin) {
      if (limit.stablePressed) {
        bottomPressSeenSinceBoot = true;
      } else if (bottomPressSeenSinceBoot && !bottomLimitValidated) {
        bottomLimitValidated = true;
        Serial.println(F("BOTTOM safety check PASSED for this boot."));
        emitEvent("info", "bottom_safety_passed");
        emitTelemetry(true);
      }
    }
  }
}

bool abortRequested() {
  if (!Serial.available()) {
    return false;
  }
  const char received = static_cast<char>(Serial.read());
  if (received == 'x' || received == 'X') {
    Serial.println(F("STOP: serial abort received."));
    return true;
  }
  return false;
}

void emitPulse(float pulseRate) {
  const unsigned long halfPeriodUs =
      static_cast<unsigned long>(500000.0f / pulseRate);
  digitalWrite(kStepPin, HIGH);
  delayMicroseconds(halfPeriodUs);
  digitalWrite(kStepPin, LOW);
  delayMicroseconds(halfPeriodUs);
}

MoveResult movePulses(long requestedPulses, bool movingUp, float startRate,
                      float cruiseRate, long rampPulses,
                      long sentOffset = 0) {
  const bool departingBottom = movingUp && isPressed(kBottomLimitPin);
  const bool departingTop = !movingUp && isPressed(kTopLimitPin);
  const long departureReleaseCheckPulses =
      mmToPulses(kDepartureReleaseCheckMm);

  digitalWrite(kDirectionPin,
               movingUp ? kUpDirectionHigh : !kUpDirectionHigh);
  delayMicroseconds(50);

  long sent = 0;
  StopReason reason = StopReason::Completed;
  const long usableRamp =
      max(1L, min(rampPulses, max(1L, requestedPulses / 2L)));

  for (; sent < requestedPulses; ++sent) {
    updateLimit(topLimit, millis());
    updateLimit(bottomLimit, millis());

    if (abortRequested()) {
      reason = StopReason::SerialAbort;
      break;
    }
    if (movingUp && isPressed(kTopLimitPin)) {
      Serial.println(F("STOP: top limit is pressed."));
      reason = StopReason::DirectionalLimit;
      break;
    }
    if (!movingUp && isPressed(kBottomLimitPin)) {
      Serial.println(F("STOP: bottom limit is pressed."));
      reason = StopReason::DirectionalLimit;
      break;
    }
    if (departingBottom && sent >= departureReleaseCheckPulses &&
        isPressed(kBottomLimitPin)) {
      Serial.println(F(
          "STOP: upward command did not release the bottom switch within "
          "2 mm. Check physical direction before continuing."));
      reason = StopReason::DirectionalLimit;
      break;
    }
    if (departingTop && sent >= departureReleaseCheckPulses &&
        isPressed(kTopLimitPin)) {
      Serial.println(F(
          "STOP: downward command did not release the top switch within "
          "2 mm. Check physical direction before continuing."));
      reason = StopReason::DirectionalLimit;
      break;
    }

    const float accelerating =
        min(1.0f, static_cast<float>(sent) / usableRamp);
    const float decelerating =
        min(1.0f,
            static_cast<float>(requestedPulses - sent - 1) / usableRamp);
    const float ramp = min(accelerating, decelerating);
    const float rate = startRate + (cruiseRate - startRate) * ramp;
    motionPulsesSent = sentOffset + sent;
    motionPulseRate = static_cast<unsigned int>(rate + 0.5f);
    emitTelemetry();
    emitPulse(rate);
  }

  motionPulsesSent = sentOffset + sent;
  motionPulseRate = 0;
  emitTelemetry(true);
  digitalWrite(kStepPin, LOW);
  return MoveResult{sent, reason};
}

MoveResult moveConstantRate(long requestedPulses, bool movingUp,
                            float pulseRate, long sentOffset = 0) {
  return movePulses(requestedPulses, movingUp, pulseRate, pulseRate, 1,
                    sentOffset);
}

void manualJog(bool movingUp, long requestedPulses, float pulseRate,
               const char* phase) {
  // Manual test movement is intentionally not a position-establishing move.
  // Clear references so a short diagnostic pulse train can never be mistaken
  // for a homed/tracked carriage position.
  bottomReferenceKnown = false;
  topReferenceKnown = false;
  positionFromBottomPulses = 0;

  Serial.print(F("MANUAL JOG: "));
  Serial.print(movingUp ? F("UP") : F("DOWN"));
  Serial.print(F("; maximum "));
  Serial.print(requestedPulses);
  Serial.print(F(" pulses at "));
  Serial.print(pulseRate, 0);
  Serial.println(F(" pulses/s. Limits and x stop remain active."));
  emitEvent("warn", "manual_jog_started", phase);

  beginMotionTelemetry(phase, movingUp, requestedPulses);
  const MoveResult result =
      moveConstantRate(requestedPulses, movingUp, pulseRate);
  endMotionTelemetry(result.reason);
  emitEvent("info", "manual_jog_finished",
            result.reason == StopReason::Completed ? "bounded" : "stopped");
  emitTelemetry(true);
}

bool confirmPressed(uint8_t pin) {
  delay(kDebounceMs);
  updateLimit(topLimit, millis());
  updateLimit(bottomLimit, millis());
  return isPressed(pin);
}

void printTrackedStatus() {
  Serial.print(F("Bottom zero reference: "));
  Serial.println(bottomReferenceKnown ? F("KNOWN") : F("NOT SET"));
  Serial.print(F("Top reference: "));
  Serial.println(topReferenceKnown ? F("KNOWN") : F("NOT SET"));
  Serial.print(F("Lead (mm/rev): "));
  Serial.println(leadScrewLeadMmPerRevolution, 4);
  Serial.print(F("Bottom safety check: "));
  Serial.println(bottomLimitValidated ? F("PASSED") : F("NOT YET PASSED"));

  if (bottomReferenceKnown) {
    Serial.print(F("Tracked position above bottom (pulses): "));
    Serial.println(positionFromBottomPulses);
    Serial.print(F("Tracked position above bottom (step-estimated mm): "));
    Serial.println(pulsesToMm(positionFromBottomPulses), 3);
  }

  if (lastDownTravelPulses > 0) {
    Serial.print(F("Last DOWN end-to-end travel (step-estimated mm): "));
    Serial.println(pulsesToMm(lastDownTravelPulses), 3);
  }
  if (lastUpTravelPulses > 0) {
    Serial.print(F("Last UP end-to-end travel (step-estimated mm): "));
    Serial.println(pulsesToMm(lastUpTravelPulses), 3);
  }
  Serial.println(F(
      "Step distance remains pulse-count estimated. Encoder diagnostics are "
      "active, but encoder distance is not calibrated/authoritative yet."));
}

void printHelp() {
  Serial.println(F("Commands (motor never moves on boot):"));
  Serial.println(F("  s       show switches, references, and tracked distance"));
  Serial.println(F("  e       show encoder raw states, edges, count, and errors"));
  Serial.println(F("  z       reset encoder diagnostic counters; does not move"));
  Serial.println(F("  t / h   guarded TOP seek, ramping to 800 pulses/s"));
  Serial.println(F("  f       guarded fast seek TOP at 1600 pulses/s"));
  Serial.println(F("  d       TOP -> 350 mm fast, then slow seek BOTTOM; set BOTTOM=0"));
  Serial.println(F("  u       BOTTOM=0 -> 350 mm fast, then slow seek TOP"));
  Serial.println(F("  mU/mD   fixed manual pulse test: 200 pulses at 100 pulses/s"));
  Serial.println(F("  jU,<pps>/jD,<pps>  hold manual test: 10-400 pulses/s, max 10 s / 1684 pulses; limits stay active"));
  Serial.println(F("  l<mm>   override lead for this session; example: l3.80"));
  Serial.println(F("  x       request stop during motion"));
}

void seekTopSlowly() {
  Serial.println(F("T command received: physical UP uses D5 LOW."));
  printRawState(topLimit);
  printRawState(bottomLimit);

  if (isPressed(kTopLimitPin)) {
    topReferenceKnown = true;
    Serial.println(F("Top switch is pressed; top reference established."));
    emitEvent("info", "reference_set", "top");
    emitTelemetry(true);
    return;
  }

  Serial.println(F(
      "Guarded TOP seek: ramping from 250 to 800 pulses/s. Send x to stop."));
  const long requestedPulses =
      mmToPulses(kFastTraverseMm + kSlowSeekAllowanceMm);
  beginMotionTelemetry("top_slow", true, requestedPulses);
  const EncoderSnapshot encoderBefore = snapshotEncoder();
  const MoveResult result = movePulses(
      requestedPulses, true, kFastStartPulseRate, kTopSeekCruisePulseRate,
      kTopSeekRampPulses);
  endMotionTelemetry(result.reason);
  const EncoderSnapshot encoderAfter = snapshotEncoder();
  printEncoderMoveComparison(F("TOP SEEK"), result.pulsesSent, encoderBefore,
                             encoderAfter);

  if (result.reason == StopReason::DirectionalLimit &&
      confirmPressed(kTopLimitPin)) {
    topReferenceKnown = true;
    if (bottomReferenceKnown) {
      positionFromBottomPulses += result.pulsesSent;
    }
    Serial.println(F("Top reference established."));
    emitEvent("info", "reference_set", "top");
  } else {
    topReferenceKnown = false;
    Serial.println(F("ERROR: top was not confirmed; reference is invalid."));
    emitEvent("error", "reference_invalid", "top_not_confirmed");
  }
  printTrackedStatus();
  emitTelemetry(true);
}

void seekTopFast() {
  if (isPressed(kTopLimitPin)) {
    topReferenceKnown = true;
    Serial.println(F("Top switch is already pressed; top reference established."));
    emitEvent("info", "reference_set", "top");
    emitTelemetry(true);
    return;
  }

  Serial.println(
      F("FAST TOP SEEK: 1600 pulses/s. Top limit checked before every pulse."));
  Serial.println(F("Send x to stop; 24 V disconnect is the immediate stop."));
  const long requestedPulses =
      mmToPulses(kFastTraverseMm + kSlowSeekAllowanceMm);
  beginMotionTelemetry("top_fast", true, requestedPulses);
  const EncoderSnapshot encoderBefore = snapshotEncoder();
  const MoveResult result =
      moveConstantRate(requestedPulses, true, kFastCruisePulseRate);
  endMotionTelemetry(result.reason);
  const EncoderSnapshot encoderAfter = snapshotEncoder();
  printEncoderMoveComparison(F("FAST TOP SEEK"), result.pulsesSent,
                             encoderBefore, encoderAfter);

  if (result.reason == StopReason::DirectionalLimit &&
      confirmPressed(kTopLimitPin)) {
    topReferenceKnown = true;
    if (bottomReferenceKnown) {
      positionFromBottomPulses += result.pulsesSent;
    }
    Serial.println(F("Top reference established."));
    emitEvent("info", "reference_set", "top");
  } else {
    topReferenceKnown = false;
    Serial.println(F("ERROR: top was not confirmed; reference is invalid."));
    emitEvent("error", "reference_invalid", "top_not_confirmed");
  }
  printTrackedStatus();
  emitTelemetry(true);
}

void homeBottomFromTop() {
  if (!bottomLimitValidated) {
    Serial.println(
        F("REFUSED: press and release the bottom switch once after reset."));
    emitEvent("warn", "motion_refused", "bottom_safety_not_passed");
    return;
  }
  if (!topReferenceKnown || !isPressed(kTopLimitPin)) {
    Serial.println(F("REFUSED: carriage must be at the pressed top switch. Run t first."));
    emitEvent("warn", "motion_refused", "top_not_referenced");
    return;
  }
  if (isPressed(kBottomLimitPin)) {
    Serial.println(F("REFUSED: top and bottom switches cannot both be pressed."));
    emitEvent("error", "motion_refused", "both_limits_pressed");
    return;
  }

  topReferenceKnown = false;
  bottomReferenceKnown = false;
  Serial.println(F("DOWN: accelerating across 350 mm fast segment."));
  const long fastRequested = mmToPulses(kFastTraverseMm);
  const long totalRequested =
      fastRequested + mmToPulses(kSlowSeekAllowanceMm);
  beginMotionTelemetry("down_fast", false, totalRequested);
  const EncoderSnapshot encoderBefore = snapshotEncoder();
  const MoveResult fast = movePulses(fastRequested, false, kFastStartPulseRate,
                                     kFastCruisePulseRate, kFastRampPulses);
  endMotionTelemetry(fast.reason);
  long totalSent = fast.pulsesSent;

  if (fast.reason == StopReason::SerialAbort) {
    Serial.println(F("Bottom reference NOT set."));
    emitTelemetry(true);
    return;
  }

  if (fast.reason != StopReason::DirectionalLimit) {
    Serial.println(F("DOWN: fast segment complete; slow-seeking bottom."));
    beginMotionTelemetry("down_slow", false, totalRequested, totalSent);
    const MoveResult slow =
        moveConstantRate(mmToPulses(kSlowSeekAllowanceMm), false,
                         kSlowSeekPulseRate, totalSent);
    endMotionTelemetry(slow.reason);
    totalSent += slow.pulsesSent;
    if (slow.reason == StopReason::SerialAbort) {
      Serial.println(F("Bottom reference NOT set."));
      emitTelemetry(true);
      return;
    }
  } else {
    Serial.println(F("WARNING: bottom was reached before the 350 mm segment completed."));
  }

  if (confirmPressed(kBottomLimitPin)) {
    bottomReferenceKnown = true;
    positionFromBottomPulses = 0;
    lastDownTravelPulses = totalSent;
    Serial.println(F("BOTTOM HOME CONFIRMED: position set to 0."));
    emitEvent("info", "reference_set", "bottom_zero");
  } else {
    Serial.println(F("ERROR: bottom not found within 400 mm; zero is NOT set."));
    emitEvent("error", "reference_invalid", "bottom_not_confirmed");
  }
  const EncoderSnapshot encoderAfter = snapshotEncoder();
  printEncoderMoveComparison(F("DOWN"), totalSent, encoderBefore, encoderAfter);
  printTrackedStatus();
  emitTelemetry(true);
}

void moveBottomToTop() {
  if (!bottomReferenceKnown || !isPressed(kBottomLimitPin)) {
    Serial.println(F("REFUSED: bottom must be homed and physically pressed. Run d first."));
    emitEvent("warn", "motion_refused", "bottom_not_homed");
    return;
  }
  if (!bottomLimitValidated) {
    Serial.println(F("REFUSED: bottom safety check has not passed."));
    emitEvent("warn", "motion_refused", "bottom_safety_not_passed");
    return;
  }

  topReferenceKnown = false;
  positionFromBottomPulses = 0;
  Serial.println(F("UP: accelerating across 350 mm fast segment."));
  const long fastRequested = mmToPulses(kFastTraverseMm);
  const long totalRequested =
      fastRequested + mmToPulses(kSlowSeekAllowanceMm);
  beginMotionTelemetry("up_fast", true, totalRequested);
  const EncoderSnapshot encoderBefore = snapshotEncoder();
  const MoveResult fast = movePulses(fastRequested, true, kFastStartPulseRate,
                                     kFastCruisePulseRate, kFastRampPulses);
  endMotionTelemetry(fast.reason);
  long totalSent = fast.pulsesSent;
  positionFromBottomPulses += fast.pulsesSent;

  if (fast.reason == StopReason::SerialAbort) {
    Serial.println(F("Top reference NOT set."));
    printTrackedStatus();
    emitTelemetry(true);
    return;
  }

  if (fast.reason != StopReason::DirectionalLimit) {
    Serial.println(F("UP: fast segment complete; slow-seeking top."));
    beginMotionTelemetry("up_slow", true, totalRequested, totalSent);
    const MoveResult slow =
        moveConstantRate(mmToPulses(kSlowSeekAllowanceMm), true,
                         kSlowSeekPulseRate, totalSent);
    endMotionTelemetry(slow.reason);
    totalSent += slow.pulsesSent;
    positionFromBottomPulses += slow.pulsesSent;
    if (slow.reason == StopReason::SerialAbort) {
      Serial.println(F("Top reference NOT set."));
      printTrackedStatus();
      emitTelemetry(true);
      return;
    }
  } else {
    Serial.println(F("WARNING: top was reached before the 350 mm segment completed."));
  }

  if (confirmPressed(kTopLimitPin)) {
    topReferenceKnown = true;
    lastUpTravelPulses = totalSent;
    Serial.println(F("TOP CONFIRMED."));
    emitEvent("info", "reference_set", "top");
  } else {
    Serial.println(F("ERROR: top not found within 400 mm."));
    emitEvent("error", "reference_invalid", "top_not_confirmed");
  }
  const EncoderSnapshot encoderAfter = snapshotEncoder();
  printEncoderMoveComparison(F("UP"), totalSent, encoderBefore, encoderAfter);
  printTrackedStatus();
  emitTelemetry(true);
}

void handleLeadCommand() {
  const String value = Serial.readStringUntil('\n');
  const float measuredLead = value.toFloat();
  if (measuredLead <= 0.0f || measuredLead > 50.0f) {
    Serial.println(F("REFUSED: lead must be between 0 and 50 mm/rev."));
    emitEvent("warn", "lead_refused", "out_of_range");
    return;
  }
  leadScrewLeadMmPerRevolution = measuredLead;
  bottomReferenceKnown = false;
  topReferenceKnown = false;
  positionFromBottomPulses = 0;
  Serial.print(F("Lead set to "));
  Serial.print(leadScrewLeadMmPerRevolution, 4);
  Serial.println(F(" mm/rev; references cleared. Re-home before motion."));
  emitEvent("info", "lead_changed", "references_cleared");
  emitTelemetry(true);
}

void handleManualJogCommand() {
  String direction = Serial.readStringUntil('\n');
  direction.trim();
  direction.toUpperCase();

  if (direction == "U") {
    manualJog(true, kManualJogPulses, kManualJogPulseRate, "manual_up");
  } else if (direction == "D") {
    manualJog(false, kManualJogPulses, kManualJogPulseRate, "manual_down");
  } else {
    Serial.println(F("REFUSED: manual command must be mU or mD."));
    emitEvent("warn", "manual_jog_refused", "direction_required");
  }
}

void handleManualHoldCommand() {
  String argument = Serial.readStringUntil('\n');
  argument.trim();
  argument.toUpperCase();
  if (argument.length() < 3 || argument.charAt(1) != ',') {
    Serial.println(F("REFUSED: hold command must be jU,<pps> or jD,<pps>."));
    emitEvent("warn", "manual_hold_refused", "format_required");
    return;
  }

  const char direction = argument.charAt(0);
  const float pulseRate = argument.substring(2).toFloat();
  if ((direction != 'U' && direction != 'D') ||
      pulseRate < kManualHoldMinPulseRate ||
      pulseRate > kManualHoldMaxPulseRate) {
    Serial.println(F("REFUSED: manual hold needs U/D and 10-400 pulses/s."));
    emitEvent("warn", "manual_hold_refused", "bounds");
    return;
  }

  // Keep both a distance cap and a time cap. At 10 pulses/s the test advances
  // only 100 pulses in 10 seconds, making rotor/shaft behavior observable.
  const long requestedPulses = min(
      kManualHoldMaxPulses,
      static_cast<long>(lroundf(pulseRate * kManualHoldMaxDurationMs / 1000.0f)));
  manualJog(direction == 'U', requestedPulses, pulseRate,
            direction == 'U' ? "manual_hold_up" : "manual_hold_down");
}

void printBanner() {
  Serial.println();
  Serial.println(F("AeroFlex bottom-zero two-speed commissioning"));
  Serial.print(F("Approximate reported travel: "));
  Serial.print(kReportedApproximateTravelMm, 1);
  Serial.println(F(" mm."));
  Serial.println(F("Fast segment: 350 mm at up to 1600 pulses/s."));
  Serial.println(F("T command: guarded TOP seek at up to 800 pulses/s."));
  Serial.println(F("Slow limit seek: at most 50 mm at 250 pulses/s."));
  Serial.println(F("HARD RULE: every test establishes bottom switch as zero."));
  Serial.println(F("After reset, press and release bottom before motion."));
  printHelp();
}

}  // namespace

void setup() {
  pinMode(kStepPin, OUTPUT);
  pinMode(kDirectionPin, OUTPUT);
  digitalWrite(kStepPin, LOW);
  digitalWrite(kDirectionPin, LOW);

  pinMode(kTopLimitPin, INPUT_PULLUP);
  pinMode(kBottomLimitPin, INPUT_PULLUP);
  // Temporary low-speed diagnostic pull-ups for the encoder's open-collector
  // outputs. Fit external pull-ups before relying on high-speed measurements.
  pinMode(kEncoderAPin, INPUT_PULLUP);
  pinMode(kEncoderBPin, INPUT_PULLUP);
  encoderPreviousState =
      (static_cast<uint8_t>(digitalRead(kEncoderAPin) == HIGH) << 1) |
      static_cast<uint8_t>(digitalRead(kEncoderBPin) == HIGH);
  attachInterrupt(digitalPinToInterrupt(kEncoderAPin), encoderEdgeIsr, CHANGE);
  attachInterrupt(digitalPinToInterrupt(kEncoderBPin), encoderEdgeIsr, CHANGE);

  Serial.begin(115200);
  const unsigned long serialWaitStarted = millis();
  while (!Serial && millis() - serialWaitStarted < 2000) {
  }

  topLimit.stablePressed = isPressed(topLimit.pin);
  topLimit.lastRawPressed = topLimit.stablePressed;
  bottomLimit.stablePressed = isPressed(bottomLimit.pin);
  bottomLimit.lastRawPressed = bottomLimit.stablePressed;
  bottomPressSeenSinceBoot = bottomLimit.stablePressed;

  printBanner();
  printState(topLimit);
  printState(bottomLimit);
  emitEvent("info", "boot", "motion_locked");
  emitTelemetry(true);
}

void loop() {
  updateLimit(topLimit, millis());
  updateLimit(bottomLimit, millis());
  emitTelemetry();

  if (!Serial.available()) {
    return;
  }

  const char command = static_cast<char>(Serial.read());
  switch (command) {
    case 's':
    case 'S':
      printRawState(topLimit);
      printRawState(bottomLimit);
      printTrackedStatus();
      break;
    case 'e':
    case 'E':
      printEncoderStatus();
      break;
    case 'z':
    case 'Z':
      resetEncoderDiagnostics();
      break;
    case 't':
    case 'T':
    case 'h':
    case 'H':
      seekTopSlowly();
      break;
    case 'f':
    case 'F':
      seekTopFast();
      break;
    case 'd':
    case 'D':
      homeBottomFromTop();
      break;
    case 'u':
    case 'U':
      moveBottomToTop();
      break;
    case 'm':
    case 'M':
      handleManualJogCommand();
      break;
    case 'j':
    case 'J':
      handleManualHoldCommand();
      break;
    case 'l':
    case 'L':
      handleLeadCommand();
      break;
    case 'x':
    case 'X':
      Serial.println(F("No motion is active."));
      emitEvent("info", "stop_ignored", "idle");
      break;
    case '?':
      printHelp();
      break;
    case '\r':
    case '\n':
      break;
    default:
      Serial.println(F("Unknown command. Send ? for help."));
      break;
  }
}
