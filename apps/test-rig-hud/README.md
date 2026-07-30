# AeroFlex test-rig live console

This is the local-first operator dashboard for the AeroFlex tensile-test rig.
It shows live carriage position, commanded motion, limit switches, reference
validity, encoder diagnostics, load-cell availability, raw serial traffic, and
a rolling 60-second trend. It also provides guarded access to the existing
commissioning commands.

The dashboard is intentionally separate from [`../hud/`](../hud/), which
targets pneumatic-muscle controllers.

## Run it

Use desktop Chrome or Edge. Either open [`index.html`](index.html) directly or
serve the repository root:

```powershell
python -m http.server 8000
```

Then open:

```text
http://localhost:8000/apps/test-rig-hud/
```

Close Arduino IDE, PlatformIO's serial monitor, and any other program holding
the controller's serial port. Click **Connect**, choose the Uno R4 Minima, and
wait for `PROTOCOL V1`.

The **Demo** button runs a repeating unloaded-commissioning scenario without
hardware. It covers bottom-switch boot validation, top seek, bottom homing,
step-estimated upward travel, encoder disagreement, a refused command, and the
currently unavailable load-cell channel.

## Safety model

- The browser is a monitor and remote, never the safety authority.
- Motion buttons require a fresh telemetry link, an explicitly armed browser
  session, an idle firmware state, and any command-specific prerequisites.
- Every motion command presents a confirmation. The **Stop** button and
  `Escape` key send `x` immediately without confirmation.
- **Manual test** is a separate, typed-confirmation mode with a dedicated
  press-and-hold Up/Down zone. The slider permits 10–400 pulses/s; releasing
  a button sends Stop and firmware also caps a held command by time and about
  4 mm. Each manual move clears position references; it does not disable D11/D12
  directional checks or the immediate Stop path.
- The browser disarms on disconnect, stale telemetry, reload, or motion start.
- Firmware still checks D12 before every upward pulse and D11 before every
  downward pulse. Bottom zero, travel bounds, and all command refusals remain
  firmware-owned.
- The 24 V disconnect remains the immediate physical stop.

Use the rig only unloaded and continuously supervised until the commissioning
work documented in [`../../firmware/README.md`](../../firmware/README.md) is
complete.

## Data and export

The console retains up to 30,000 telemetry, diagnostic, event, and raw serial
records in browser memory. **CSV** exports the retained session with both host
and device timestamps. Reloading the page clears the session.

Step-position is shown only while the bottom reference is valid. Encoder travel
is labelled as a relative, uncalibrated estimate and is never substituted for
absolute carriage position.

The force panel deliberately reads:

```text
UNAVAILABLE — HX711 DT REPAIR REQUIRED
```

Firmware publishes `fs=unavail fv=0 fn=nan`; the dashboard will not infer a
force value from those fields.

## Serial protocol

Firmware streams a core `@T` frame at up to 5 Hz and a diagnostic `@D` frame at
up to 1 Hz. Discrete state changes use `@E` events. Unknown fields are ignored,
so protocol v1 can be extended additively.

The dashboard can extract a limited subset of values from the older
human-readable output, but live in-motion updates require protocol v1.
