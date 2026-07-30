# AeroFlex test-rig firmware

This PlatformIO project targets the **Arduino Uno R4 Minima** installed on the
AeroFlex tensile-test rig.

## Non-negotiable coordinate and safety rules

Every present and future test program must follow these rules:

1. The physical **bottom switch defines position 0** for every test.
2. Upward test travel is prohibited until bottom homing succeeds.
3. D12 is checked before every upward pulse; D11 is checked before every
   downward pulse.
4. Long travel consists of at most **350 mm fast travel plus 50 mm slow
   seeking**. Failure to find the expected switch within that envelope
   invalidates the reference.
5. Firmware never initiates motion at boot.
6. The 24 V motor disconnect remains the true emergency stop.
7. Position is currently a **step-count estimate**, calculated from emitted
   pulses and the 3.80 mm/revolution effective-drive-travel estimate. It must not be described as
   independently measured actual distance until verified encoder feedback is
   active.

The rig is still in unloaded, continuously supervised commissioning.

## Wiring used by firmware

| Function | Uno R4 pin | Wire / driver terminal |
|---|---|---|
| Step | D6 | Purple → DM542T `PUL+` |
| Direction | D5 | Blue → DM542T `DIR+` |
| Driver returns | GND | White/gray → `PUL-` and `DIR-` |
| Top limit | D12 | Purple signal, orange GND |
| Bottom limit | D11 | Yellow signal, orange GND |

The bottom input was moved from D13 to D11 to avoid the Uno R4 Minima’s
D13/`L`-LED circuit. Both limit inputs use `INPUT_PULLUP`: released is `HIGH`,
pressed is `LOW`.

## Motion profile

- Effective drive-travel estimate: **3.80 mm/revolution**. This is linear rod
  travel per effective drive revolution; it does not assert that the threaded
  rod itself rotates.
- Driver resolution: **1600 pulses/revolution**.
- Fast segment: **350 mm**, accelerating from 250 to 1600 pulses/s and
  decelerating before the slow segment.
- Slow switch seek: at most **50 mm** at 250 pulses/s.
- Approximate reported switch-to-switch travel: **360 mm**.

At the current lead estimate, 1600 pulses/s is one motor revolution per second,
or approximately 3.8 mm/s.

## Commands

| Command | Action |
|---|---|
| `s` | Report both switches, reference validity, tracked position, and last end-to-end distances. |
| `e` | Report encoder D3/D2 raw states, per-channel edges, quadrature count, invalid transitions, revolutions, and estimated travel. Does not move. |
| `z` | Reset only the encoder diagnostic counters. Does not move or establish a position reference. |
| `t` or `h` | Guarded top seek, ramping from 250 to 800 pulses/second. It prints both limit states before moving. |
| `f` | Guarded fast seek toward the top at 1600 pulses/second, checking D12 before every pulse. |
| `d` | From the pressed top switch, move down 350 mm fast, then slow-seek the bottom switch and set bottom = 0. |
| `u` | From bottom = 0 with the bottom switch pressed, move up 350 mm fast, then slow-seek the top switch. |
| `mU` / `mD` | Manual diagnostic jog: fixed 200 pulses at 100 pulses/s (about 0.475 mm at the current lead estimate). |
| `jU,<pps>` / `jD,<pps>` | Press-and-hold manual move for the dashboard. `pps` is 10–400; releasing the control sends `x`. Firmware applies both a 10-second cap and a 1,684-pulse cap (about 4 mm). Both manual paths clear references; D12/D11 checks and `x` Stop remain active. |
| `l<mm>` | Override effective drive travel for the current session; changing it clears both references. |
| `x` | Request a stop during motion. |
| `?` | Print command help. |

After every Arduino reset, manually press and release the bottom switch once.
Downward commands remain locked until the firmware prints:

```text
BOTTOM safety check PASSED for this boot.
```

## Normal commissioning sequence

With no specimen installed:

1. Keep 24 V motor power off; open the serial monitor at 115200 baud.
2. Press and release the bottom switch once.
3. Send `s`; verify both limits and the bottom safety check.
4. Turn on 24 V motor power and keep the disconnect accessible.
5. Send `t`. If already touching the top switch, this only records the
   reference; otherwise it slow-seeks the top.
6. Send `d`. The bottom switch becomes zero only after the firmware confirms
   it remains pressed.
7. Review the reported down-travel step estimate.
8. Send `u` to perform the fast-up/slow-top sequence.
9. Review the reported up-travel step estimate and compare both directions.

If the motor stalls, skips, vibrates unusually, travels in the wrong direction,
or a switch does not stop it, send `x` and disconnect 24 V power.

When an upward command starts with the bottom switch pressed, firmware requires
D11 to release within the first 2 mm of commanded upward travel. Likewise, a
downward command leaving the top requires D12 to release within 2 mm. Failure
stops pulse output and indicates that physical direction or a switch is wrong.

## Encoder diagnostic

The installed encoder wiring is red to 5 V, black to GND, **gray to D3**, and
white to D2. Gray is the authoritative observed conductor color on this rig,
even though generic LPD3806 source material commonly describes channel A as
green. The diagnostic therefore calls D3 the A candidate until its behavior is
verified.

The current firmware uses the Arduino's internal pull-ups to permit a
low-speed, motor-power-off diagnostic of the encoder's open-collector outputs.
Before treating encoder measurements as reliable at operating speed, install a
separate external pull-up (typically 4.7 kOhm to Arduino 5 V) on D3 and D2.

With 24 V motor power off, do **not** manually rotate or translate the threaded
rod. The current mechanism uses a rotating-nut/drive assembly and the rod is
treated as non-rotating. Perform encoder verification only through a supervised
low-speed drive move after the mechanical bind is resolved:

1. Send `z`, leave the mechanism untouched for about 10 seconds, then send `e`.
   Edge counts and invalid transitions should remain zero.
2. After the bind is resolved and external pull-ups are fitted, use a short,
   supervised drive move and then send `e`. Both A and B edge counts must
   increase and the quadrature count must change.
3. Compare encoder count against a measured, short linear travel. Do not use a
   manual one-rod-revolution test.
4. After the low-speed test passes, guarded `t`,
   `d`, and `u` moves automatically report emitted motor pulses, encoder count
   delta, their absolute ratio, encoder-estimated travel, and invalid
   transitions. A 1:1 mechanical coupling should approach a ratio of 1.0000.

Do not call encoder distance independently measured until both channels pass,
one revolution produces the expected count, the coupling ratio is confirmed,
and high-speed move comparisons show no significant missed or invalid counts.

## PlatformIO

The project uses PlatformIO’s `renesas-ra` platform and `uno_r4_minima` board.
PlatformIO Core is installed at:

```text
%APPDATA%\Python\Python314\Scripts\pio.exe
```

Build and upload from `firmware/`:

```powershell
& "$env:APPDATA\Python\Python314\Scripts\pio.exe" run
& "$env:APPDATA\Python\Python314\Scripts\pio.exe" run --target upload
```

Open the COM3 monitor (replace the port if Windows changes it):

```powershell
& "$env:APPDATA\Python\Python314\Scripts\pio.exe" device monitor --port COM3 --baud 115200
```

## Live console telemetry protocol

[`../apps/test-rig-hud/`](../apps/test-rig-hud/) is the local-first Web Serial
dashboard for this firmware. The existing human-readable command responses are
unchanged. Three additive, versioned frame types let the dashboard update
during motion:

```text
@T v=1 ms=12400 mot=up_fast dir=up pps=1580 sent=22510 req=168421 pv=1 posp=22510 posmm=53.461 enc=-33462 inv=0 top=0 bot=0 safe=1 bref=1 tref=0
@D v=1 ms=12400 ea=16802 eb=16660 ah=1 bh=0 lead=3.8000 fs=unavail fv=0 fn=nan
@E v=1 ms=12400 level=warn code=motion_refused reason=bottom_not_homed
```

Core `@T` frames are attempted every 200 ms while idle and inside pulse loops.
Diagnostic `@D` frames are attempted every second. A complete frame is written
only when it fits in the Uno R4 USB transmit buffer; otherwise that sample is
skipped instead of blocking the pulse loop.

### Core `@T` fields

| Field | Meaning |
|---|---|
| `v` | Protocol version (`1`). |
| `ms` | Device uptime in milliseconds; wraps with Arduino `millis()`. |
| `mot` | `idle`, `top_slow`, `top_fast`, `down_fast`, `down_slow`, `up_fast`, or `up_slow`. |
| `dir` | Physical direction: `none`, `up`, or `down`. |
| `pps` | Current commanded pulse rate. It is not an independently measured speed. |
| `sent`, `req` | Pulses emitted and maximum pulses requested for the current command. |
| `pv` | `1` only when `posp` / `posmm` are valid relative to a confirmed bottom zero. |
| `posp`, `posmm` | Position above bottom from emitted step pulses. This remains a step-count estimate. |
| `enc` | Signed relative quadrature count. It is not absolute carriage position. |
| `inv` | Invalid two-bit encoder transitions. |
| `top`, `bot` | Raw physical pressed state for D12 and D11. |
| `safe` | Bottom press/release boot validation has passed. |
| `bref`, `tref` | Bottom and top references are known. |

### Diagnostic `@D` fields

| Field | Meaning |
|---|---|
| `ea`, `eb` | Encoder A/B edge counters. |
| `ah`, `bh` | Current raw encoder A/B logic levels. |
| `lead` | Current effective drive-travel estimate in mm/revolution. |
| `fs`, `fv`, `fn` | Force status, validity, and newtons. v1 reports `unavail`, `0`, and `nan`. |

The HX711 data wire is still cut, so firmware does not read the load cell and
does not add an HX711 dependency. Force must remain unavailable until the wire,
board power label, sign, tare, scale, and safe range are verified.

### Distance terminology

- **Step-estimated position** is absolute only after bottom homing and is based
  on emitted DM542T pulses plus the configured effective lead.
- **Encoder-estimated travel** is a relative, uncalibrated diagnostic based on
  encoder count and the same provisional lead.
- **Measured force** is unavailable.

Do not relabel any of these values as independently measured actual carriage
position or force until the corresponding hardware verification and
calibration work is complete.
