# AeroFlex Telemetry HUD

A zero-install, single-file browser dashboard for pneumatic muscle
controllers. Big dotted donut gauges for pressure, a raw-serial stream, a
60-second trend graph, battery / valve / status tiles, and command buttons
(target up/down, lift, lower, auto-cycle, e-stop). It reads your
controller's USB-serial telemetry directly in the browser via the Web
Serial API and can send commands back - no drivers, no install, no build
step.

Everything is one file: [`index.html`](index.html). Open it, click
Connect, pick your controller's port. There is also a **Demo** button that
simulates a full controller so you can explore the HUD with no hardware at
all.

## Run it

1. Open `index.html` in **Chrome or Edge** (desktop). Web Serial is not
   available in Firefox or Safari. Double-click the file, or serve it:
   ```bash
   python -m http.server 8000    # then http://localhost:8000/apps/hud/
   ```
2. Close any other serial monitor (Arduino IDE, logging scripts) - only
   one program can own the port.
3. Click **Connect** and pick the port. Done. The HUD remembers granted
   ports and auto-reconnects on reload.

First paint needs internet once (Tailwind and the Kode Mono font load from
CDN); after that the logic is fully local.

## Make your controller speak HUD

The HUD is controller-agnostic. It does not care what your hardware is -
an Arduino Uno R4 Minima (the reference controller), a Nano, an ESP32, a
Pi Pico - as long as it prints one telemetry line at a time over
USB-serial at **115200 baud**:

```
[STATE] m=87.5/90 t=101.2 bat=24.1 valve=FILL fd=62 vd=0 lowtank=0 lowbat=0 tmiss=0
```

| Token | Meaning | Used by |
|---|---|---|
| `[STATE]` or `[FAULT:CODE]` | System state: `BOOT`, `IDLE`, `RISING`, `HOLDING`, `LOWERING`, `FAULT` | Status card, LED mirror |
| `m=<psi>/<target>` | Muscle pressure / current target | MUSCLE gauge + target marker |
| `t=<psi>` | Supply (tank) pressure | SUPPLY gauge |
| `bat=<volts>` or `bat=<volts>(USB)` | Pack voltage; `(USB)` = maintenance power, actuation disabled | Battery card, mode chip |
| `valve=FILL\|VENT\|closed` | Valve state | Flow indicator |
| `fd=<0-100>` / `vd=<0-100>` | Fill / vent solenoid duty (peak-and-hold %) | Drive readout under the gauges |
| `lowtank=0\|1`, `lowbat=0\|1` | Supply / battery warnings | Alert bar, control lockout |
| `tmiss=0\|1` | Soft warning: supply too low to reach target | Alert bar |
| any other `name=value` | **Auto-captured** into the channel map | Your custom widgets |

Fault codes the HUD knows (shown with full descriptions in the alert bar):
`OVER-PRESSURE`, `LEAK`, `SENSOR`, `UNDER-VOLT`, `OVER-VOLT`, `E-STOP`.

Only the `[STATE]` tag is required; every other token is optional and the
HUD degrades gracefully (missing channels show as dashes). A minimal
sketch that drives the HUD:

```cpp
// Any Arduino: minimal AeroFlex-HUD-compatible telemetry
float psi(int pin){ return (analogRead(pin)*5.0/1023.0 - 0.5) * 150.0/4.0; }

void setup(){ Serial.begin(115200); }

void loop(){
  Serial.print("[IDLE] m=");  Serial.print(psi(A0), 1);
  Serial.print("/90 t=");     Serial.print(psi(A1), 1);
  Serial.print(" bat=");      Serial.print(analogRead(A2)*0.0293, 1);
  Serial.println(" valve=closed fd=0 vd=0 lowtank=0 lowbat=0 tmiss=0");
  delay(300);
}
```

### Commands the HUD sends

Single characters, written back over the same port. Implement the ones you
want; ignore the rest.

| Char | Button | Expected firmware behavior |
|---|---|---|
| `+` / `-` | Target +/- | Raise / lower the pressure target (reference firmware: 5 psi steps) |
| `f` | Lift | Fill / pressurize toward target |
| `v` | Lower | Vent |
| `s` | E-Stop / Clear | Latch a vented safe state; sent again, clear the fault |

The auto-cycle widget just alternates `f` and `v` on adjustable periods -
no extra firmware support needed.

## Adapting to your rig

All hardware assumptions are constants at the top of the script, marked
`RIG CONFIGURATION`:

| Constant | Default | Change it if |
|---|---|---|
| `BAT_MIN`, `BAT_MAX` | 21.6 / 25.2 V (6S LiPo, 24 V-solenoid floor) | Different pack or coil voltage |
| `R_COIL` | 120 ohm | Different solenoid (sets the estimated drive-power readout) |
| `psiToV()` | 150 psi transducer, 0.5-4.5 V | Different pressure sensor (only affects the volts sub-readout) |
| `GAUGES[].max` / `danger` | 150 psi full scale, hazard band at 80% (120 psi cap) | Different burst / operating limits |

## Adding a sensor or widget

The HUD is widget-driven and the parser auto-captures any `name=value`
token, so a new sensor is two small steps:

1. **Firmware:** print it on the telemetry line, e.g. `temp=42.5`.
2. **HUD:** add one entry to the `GAUGES` array:
   ```js
   { key:'temp', label:'TEMP', tag:'T1', max:80, unit:'°C',
     sub:v=>v.toFixed(1)+' °C', zones:[{t:0.75,c:'--amber'},{t:0.9,c:'--red'}] }
   ```
   A new donut tile appears and flows into the grid (commented examples
   are in the file). Non-gauge widgets follow the same `{ el, update() }`
   factory pattern.

## Cherry-picking

Each piece works standalone if you want parts rather than the whole HUD:

- **Telemetry parser** - `handleLine()`: regex per known token plus the
  generic `name=value` auto-capture loop.
- **Web Serial glue** - `openPort()` / `readLoop()` / `send()`: complete
  connect / line-buffer / write pattern, including silent auto-reconnect
  to previously granted ports.
- **Donut gauge factory** - `buildGauge()` + `arcPath()`: SVG dotted
  donut with color zones, hazard band, and target marker, driven by a
  config object.
- **LED blink mirror** - `ls()` + the `tick()` loop: maps status codes to
  blink patterns (solid / slow / fast / blip / triple-burst).
- **Diagnostics export** - `exportDiag()`: rolling ~100 min buffer of
  every sample, one-click CSV.

## Safety notes

The HUD is a monitor and remote - the controller firmware must own all
safety behavior (pressure caps, vent-on-fault, lockouts). Do not put the
only over-pressure protection in a browser tab. The control buttons
disable themselves when the link drops, on USB (maintenance) power, or
while a fault or supply/battery warning is active - mirror the same
interlocks in firmware.
