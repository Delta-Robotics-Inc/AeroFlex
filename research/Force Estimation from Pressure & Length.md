# Force Estimation from Pressure & Length (model-based "force sensing")

Can a pneumatic artificial muscle report the force it's exerting **without a load cell in the
load path** - by inferring it from internal pressure and length? Yes. A McKibben-type muscle's
force is a deterministic function of **pressure and contraction state together**, so measuring
both (plus a calibrated model) yields a force estimate. This is the basis for treating AeroFlex's
muscle as a self-sensing actuator.

> **Provenance.** Synthesis from a design discussion, **2026-06-09**, grounded in the standard
> McKibben modeling literature already in this folder (Chou & Hannaford; Tondu & Lopez; static
> braided models) and the embedded-sensing work (Smart Braid). Equations are the textbook ideal
> model; the calibration guidance is the practical counterweight to it.

Related local references:
- [`Research Papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf) - Chou & Hannaford (1996), the standard force-pressure-length model + measured hysteresis.
- [`Research Papers/McKibben_Robot_Muscle.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/McKibben_Robot_Muscle.pdf) - Tondu & Lopez (2000), model with empirical correction factor.
- [`Research Papers/Static Modeling of Braided Pneumatic Muscle Actuator.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Static%20Modeling%20of%20Braided%20Pneumatic%20Muscle%20Actuator.pdf) - static force-pressure-stroke surface.
- [`Research Papers/Smart Braid Air Muscles that Measure Force and Displacement.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Smart%20Braid%20Air%20Muscles%20that%20Measure%20Force%20and%20Displacement.pdf) - embedded sensing that measures force/displacement directly.
- [`Research Papers/Contraction Sensing with Smart Braid McKibben Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Contraction%20Sensing%20with%20Smart%20Braid%20McKibben%20Muscles.pdf) - follow-on Smart Braid journal paper focused on inductance-based contraction sensing.
- [`PAM Design Variables.md`](PAM%20Design%20Variables.md) - every variable feeding the constants below (braid angle, diameter, etc.).

---

## The core relationship

For a McKibben muscle, output force `F` depends on **gauge pressure `P`** and **contraction
ratio `ε`** (how far it has shortened from rest), not pressure alone. The idealized
Gaylord / **Chou-Hannaford** model:

```
F = (π · D₀² · P / 4) · [ (3 / tan²θ₀)·(1 − ε)²  −  (1 / sin²θ₀) ]
```

| Symbol | Meaning |
|---|---|
| `P`  | gauge pressure (psig / Pa) - what the AeroFlex PTD1 sensor reads (0 = atmospheric) |
| `ε`  | contraction ratio `(L₀ − L) / L₀` - needs a **length** measurement |
| `L₀` | rest length (fully extended, unpressurized) |
| `θ₀` | braid angle at rest |
| `D₀` | rest diameter at `θ₀` |

What the equation tells you, in plain terms:

1. **Force is ~linear in pressure at a fixed length:** `F ≈ k(L)·P − F_threshold`. So for an
   *isometric* hold, pressure alone is enough.
2. **Force falls as it contracts.** Maximum force when fully stretched (`ε = 0`); force reaches
   **zero at free contraction**, where the bracket goes to zero - the classic **θ → 54.7°**
   threshold (`cos²θ = 1/3`). Past that geometry the muscle can no longer pull.
3. **Therefore once length changes, pressure is not sufficient** - you need both `P` and `L`.

This is the same 54.7° contract-vs-extend threshold noted in the reticulated/fiber-net actuator
work (see README → *Festo Fluidic Muscle & embedded-braid construction*).

---

## What you'd have to add

AeroFlex already measures the two pressures (`m=` muscle, `t=` supply) and battery. To estimate
force it needs **one more channel: length / displacement.** Options, cheapest → best:

| Sensor | Notes |
|---|---|
| **String potentiometer (draw-wire)** | Simplest retrofit; absolute length, analog out straight into a spare ADC pin. |
| **Linear encoder / magnetic linear (AS5311 + strip)** | High resolution, digital. |
| **Embedded conductive/strain fiber** | The "smart braid" approach - sensing fiber co-formed into the sleeve. Most elegant, hardest to fabricate. See *Smart Braid Air Muscles* PDF and the Wakimoto conductive-fiber work (README → external refs). |
| **IMU / joint encoder on the driven linkage** | If the muscle drives a known kinematic joint, joint angle → muscle length by geometry. Often free if the limb is already instrumented. |

With `P` and `L` in hand, `F = model(P, L)` becomes a **derived channel** - no new physical force
sensor in the load path.

---

## The big caveat: hysteresis

The ideal equation is optimistic. Real McKibben muscles show **10-30 % force hysteresis** from
**Coulomb friction between the bladder and the braid** - at the *same* `(P, L)` the force is
higher while inflating than while deflating. Chou & Hannaford measured exactly this. Consequences:

- A single-valued `F(P, L)` model carries that 10-30 % error band.
- For better accuracy, the model has to be **direction-aware** - separate inflate/deflate
  surfaces, or a friction/hysteresis term (e.g. a Coulomb offset `± F_fric·sign(dP)` or a
  Bouc-Wen / Preisach operator).
- Other second-order effects the ideal model drops: bladder elastic resistance (a `−P`-like and a
  length-dependent term), end-cap / dead-volume geometry, and a **threshold pressure** below which
  nothing moves. Tondu & Lopez fold these into an empirical correction factor.

---

## Recommended approach: calibrate, don't trust the formula

Use the equation for intuition and initial scaling; get real numbers from a bench calibration.

1. **Rig** the muscle in series with a **load cell** (an in-line tension sensor), with a way to
   set / measure length (the same displacement sensor you'll deploy, or a lead screw + scale).
2. **Sweep** pressure × length across the operating envelope; log `(P, L, F)`. Capture **both
   inflation and deflation** sweeps if you want the hysteresis band.
3. **Fit** a surface `F(P, L)` (low-order polynomial or thin-plate spline) **or** build a 2-D
   lookup table with interpolation. Store inflate/deflate separately if needed.
4. In operation: read `P` + `L`, evaluate the surface/LUT → estimated `F` (± stated band).

This converts the muscle into a soft force sensor whose accuracy you can actually quote.

---

## Limitations to keep in mind

- **Quasi-static only.** The above estimates the *static* equilibrium force. Fast motion adds
  inertial and viscous/damping terms (air dynamics, braid friction rate-dependence) the static
  surface won't capture. For a slow lift/hold (AeroFlex's regime) this is fine; for dynamic
  control it isn't.
- **Per-muscle calibration.** Braid angle, diameter, and bladder vary unit-to-unit and drift with
  break-in and wear, so the surface is specific to a muscle (or a tightly-controlled production
  batch) and should be re-checked periodically.
- **Temperature.** Gas law + rubber stiffness shift with temperature; a temp channel (the other
  sensor already contemplated for AeroFlex) improves the estimate if the muscle runs hot/cold.

---

## Fit into AeroFlex

- **Firmware:** add the length sensor on a spare ADC, compute `F = model(P, L)` each tick, and
  print it on the telemetry line as another `name=value` token, e.g.
  `... valve=closed force=142 ...`.
- **HUD:** the app auto-captures unknown `name=value` channels, and the gauge system is modular -
  a `force` gauge is one entry in the `GAUGES[]` array (label, units, zones). No parser changes
  beyond that.
- **Why bother:** a force estimate enables force/impedance control, overload detection independent
  of the pressure cap, and a real "how hard is it pulling" readout for the wearer - without a
  load cell in the structural path.
