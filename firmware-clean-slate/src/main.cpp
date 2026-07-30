// AeroFlex clean-slate safety firmware for Arduino Uno R4 Minima.
//
// Purpose: provide a known, non-actuating program while the rig is inspected.
// This sketch never generates step pulses, never drives direction, never
// enables a motor driver, and accepts no commands. The rig motor 24 V supply
// must remain disconnected while it is uploaded and while faults are checked.

#include <Arduino.h>

namespace {

// Kept as INPUT (high impedance). Do not change these to OUTPUT in this
// diagnostic sketch: D6/D5 are the rig's STEP/DIR lines.
constexpr uint8_t kStepPin = 6;
constexpr uint8_t kDirectionPin = 5;
constexpr uint8_t kEncoderAPin = 3;
constexpr uint8_t kEncoderBPin = 2;
constexpr uint8_t kBottomLimitPin = 11;
constexpr uint8_t kTopLimitPin = 12;
constexpr uint8_t kLoadCellDataPin = A4;
constexpr uint8_t kLoadCellClockPin = A5;

unsigned long lastHeartbeatAt = 0;

void makeRigPinsInert() {
  // Explicitly release every documented rig-connected signal. INPUT does not
  // source or sink driver/switch/load-cell current from these pins.
  pinMode(kStepPin, INPUT);
  pinMode(kDirectionPin, INPUT);
  pinMode(kEncoderAPin, INPUT);
  pinMode(kEncoderBPin, INPUT);
  pinMode(kBottomLimitPin, INPUT);
  pinMode(kTopLimitPin, INPUT);
  pinMode(kLoadCellDataPin, INPUT);
  pinMode(kLoadCellClockPin, INPUT);
}

}  // namespace

void setup() {
  makeRigPinsInert();
  Serial.begin(115200);

  // Give native USB Serial a brief chance to enumerate without blocking the
  // safety state if it is not connected.
  const unsigned long startedAt = millis();
  while (!Serial && millis() - startedAt < 1200) {
  }

  Serial.println(F("@SAFE v=1 state=clean_slate motion=disabled"));
  Serial.println(F("AeroFlex clean-slate firmware: all rig signal pins are INPUT; no commands are accepted."));
}

void loop() {
  // Reassert inert pin modes in case a library/core change ever touches them.
  makeRigPinsInert();

  const unsigned long now = millis();
  if (now - lastHeartbeatAt >= 1000) {
    lastHeartbeatAt = now;
    Serial.print(F("@SAFE v=1 ms="));
    Serial.print(now);
    Serial.println(F(" state=clean_slate motion=disabled"));
  }
}
