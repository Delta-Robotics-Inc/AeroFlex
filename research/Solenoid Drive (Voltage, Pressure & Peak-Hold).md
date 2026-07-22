# Solenoid Drive - Voltage, Pressure & Peak-Hold

Reference notes for driving pneumatic solenoid valves from a battery, written generally so they
carry over to future AeroFlex builds. The worked example is the **Tailonz 2V025-08** (24 V
coil) on a **6S LiPo** via the **ThermoFlex Mk.1** board, but the physics applies to any
direct-acting solenoid valve.

> **TL;DR for picking a solenoid for the next build:** a valve's coil voltage rating is the voltage
> at which it can open against its **full rated pressure**. If you run it below that (e.g. a 24 V
> coil on a sagging 22 V pack), the pressure it can crack open against drops with **V²**. Either
> size the coil to your *lowest* battery voltage under load, or regulate a fixed coil rail (boost).

---

## 1. The part (worked example)

**Tailonz/AirTac 2V025-08**, 2/2 normally-closed, **direct-acting** poppet, 1/4" port, Ø2.5 mm orifice.

| Spec | Value |
|---|---|
| Coil | **24 V DC**, rated **21.6-26.4 V** (24 V ±10%), **~120 Ω**, **~0.2 A**, **4.8 W** |
| Operating pressure | Vacuum to ~115 psi (MOPD at rated voltage) |
| Action | Direct-acting - solenoid lifts the poppet directly; **no min differential needed** |
| Response | <20-50 ms |
| Flyback | Inductive load - needs a freewheel diode (the ThermoFlex board has 100 V/20 A diodes) |

Datasheets only ever publish the **±10% tolerance** and the operating-pressure range - **no
manufacturer gives a pull-in or dropout voltage.** Everything below is physics + estimation;
**bench-verify** for any specific valve.

---

## 2. Why voltage matters: pull-in, hold, and the V² rule

A direct-acting NC valve must lift the poppet against the **spring + the inlet pressure**. Magnetic
force scales with coil current squared, and current = V/R, so:

```
F_magnetic  ∝  I²  ∝  V²
```

Two distinct thresholds:

- **Pull-in (must-operate):** the voltage needed to *crack the valve open from closed* against the
  pressure. This is the hard one - the air gap is open, so force is weakest. Scales with V².
- **Dropout / hold:** once the poppet is seated open the gap is ~closed and force is far higher for
  the same current, so it **holds open at a fraction of pull-in** (dropout typically ~30-50% of
  pull-in, ≈ 8-12 V for a 24 V coil at low pressure). → this is what makes **peak-and-hold** work.

### Estimated max pressure vs coil voltage

`P_open(V) ≈ P_rated · (V / V_rated)²`, here `≈ 115 psi · (V/24)²`:

| Coil V | Max pressure it can open against |
|---|---|
| 24.0 V | ~115 psi |
| 22.2 V (6S nominal) | ~98 psi |
| **21.6 V (rated min)** | **~93 psi** |
| 20.0 V | ~80 psi |
| 18.0 V | ~65 psi |
| 16.0 V | ~51 psi |

Estimate only (ignores the spring offset; slightly optimistic at low V). **The FILL valve, which
opens against ~90 psi tank pressure, is the first to go marginal as voltage sags.** A vent valve
(opening against the much-lower muscle pressure) and a valve that's *already open* tolerate far
lower voltage.

---

## 3. The 6S LiPo problem (why 21.6 V = 0%)

A 6S LiPo is **25.2 V full / 22.2 V nominal / ~19.8 V empty**, so it sits **below the 24 V coil
rating for most of its discharge** - strong off the charger, weakening as it drains, and sagging
further under the valve's inrush. Below **~21.6 V** (the coil's rated minimum) the fill valve can't
reliably open against full tank pressure.

So the firmware + HUD map the battery gauge to **usable-system capacity, not raw LiPo capacity:**

```
0%  = 21.6 V   (24 V-coil floor; below this the valves stop actuating reliably)
100% = 25.2 V  (6S full charge)
```

The under-volt **cutoff is 21.6 V** (`BATT_CUTOFF_V`). This also keeps the LiPo comfortably above
its own ~19.8 V floor, so it's pack-safe too. (Mismatch note: a 24 V coil and a 6S pack are not a
great match - see §6.)

---

## 4. The driver board (ThermoFlex Mk.1) - what it does and doesn't have

The board is an **SMA-muscle (current-control) driver** repurposed to switch pneumatic solenoids:

- **Power rails: buck → 12 V (gate/logic) + LDO → 5 V (MCU). NO boost, NO 24 V rail.** The solenoid
  loads are switched **directly off the raw battery (VCC)** through the MOSFETs - so the coils see
  whatever the pack is at (sub-24 V most of the time).
- **Drive: low-side N-MOSFETs (IRFS7730) + UCC27517 gate drivers + flyback diodes**, two channels
  (M1/M2 → the FILL/VENT solenoids).
- **Sense: INA301 current-sense amps + 0.5 mΩ shunts** (gain 100 V/V) - i.e. it's **current-control
  capable**, but sized for SMA's tens of amps, so a 0.2 A solenoid is barely resolvable.
- **As programmed:** the firmware drives the coils **on/off (voltage switching)** - the current
  sense is unused. PWM (peak-and-hold) is added in firmware; it can't raise the rail, only chop it.

**Implication:** the board cannot fix the low-voltage pull-in problem (no boost). To give the coils
a solid 24 V regardless of pack charge you need an **external boost/buck-boost** (see §6).

---

## 5. Peak-and-hold PWM (implemented in firmware)

Full rail to pull in, then PWM the coil down to a hold duty once seated:

- `PULLIN_MS` (≈150 ms) at **100% duty** to guarantee the poppet seats, then drop to **`HOLD_PWM`**
  (≈63%). Coil heat ≈ `duty² · V²/R`, so ~63% hold ≈ **0.4× the heat**.
- Telemetry reports the live duty per valve (`fd=`/`vd=`); the HUD shows it as a **DRIVE** readout
  (duty % + estimated coil power `≈ duty² · V²/R`) on the MUSCLE and SUPPLY cards.
- **Set `HOLD_PWM = 255` to disable** (always full rail = original behavior).

**Tuning / cautions (bench-verify):**
- Too-low hold can let a valve **drop out**, or during active high-pressure *flow* only partially
  lift the poppet (slower fill/vent). On this board the coils are already underdriven, so the hold
  is kept conservative; **raise it** if fills feel sluggish or a valve buzzes.
- The benefit here is **heat/power** during long energizations; with the HOLDING operating zone the
  valves are mostly *closed* during a hold, so peak-and-hold mostly helps long vents and the
  pull-in inrush. **With a proper 24 V+ boost rail you can pull in hard and drop hold to ~35%.**

---

## 6. Guidance for the next build

1. **Match the coil voltage to your *minimum* battery-under-load voltage**, not the nominal. A 24 V
   coil wants ≥21.6 V at the coil *during inrush*; a 6S LiPo can't guarantee that. Options:
   - **Best: regulate a fixed solenoid rail.** Boost the 6S pack to **~26 V** (just under the 26.4 V
     coil max). Since 26 V > 25.2 V (full pack), a plain boost works across the *entire* discharge →
     the valves always see full force. ~0.5 A for two valves; a small boost module suffices.
   - **Or pick a lower-voltage coil** (12 V) that the pack comfortably exceeds - but 12 V coils pull
     more current for the same power, so size the MOSFETs/wiring accordingly.
2. **Add the flyback diode** across every coil (inductive turn-off spike kills FETs). Present on
   ThermoFlex; don't omit on a new board.
3. **Use peak-and-hold** once you have a solid rail - pull in at 100%, hold at ~30-40% to cut coil
   heat and power.
4. **Bench-find the real pull-in voltage:** put a bench supply on one coil at your worst-case
   pressure (~90 psi for fill) and walk the voltage down until it stops clicking/opening. Repeat at
   2-3 pressures to map the curve for *your* valves. That's the definitive number; the table in §2
   is only an estimate.

---

## Sources
- Part research + datasheets: ProtoPart `protoparts/tailonz-2v025-08-24v/` (AirTac 2V catalog, STC
  2V025 spec, nameplate DC24V/4.8W/21.6-26.4 V). PR #348.
- ThermoFlex Mk.1 board: BOM + `SPICE_SIM_SUMMARY.md` (LMR51430 buck→12 V, L7805→5 V, 2× INA301,
  2× UCC27517, 4× IRFS7730, no boost).
- Firmware implementation: reference firmware in the private [AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private) repo (team access)
  (battery + solenoid-drive config blocks).
