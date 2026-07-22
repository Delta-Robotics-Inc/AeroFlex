# Variables Chart - PAM Performance Radar

A scoring system for pneumatic artificial muscle configurations. Each muscle design produces a shape on a radar chart. Different applications want different shapes. The goal: identify the best possible muscle for a given job, and the single "best overall" muscle that maximizes everything we care about.

> **Future web visualization.** This data is designed to power a spider/radar chart on the AeroFlex website where visitors can adjust variables and watch the polygon reshape in real time. Each axis is a performance metric (0-10). The internal polygon shape represents how a specific configuration performs.

---

## Performance Axes (0-10 Scale)

Eight axes. Each scored 0-10 with defined anchor points so scores are repeatable and comparable across configurations.

### 1. Stroke (contraction ratio)

How much the muscle shortens as a percentage of its resting length.

| Score | Contraction % | What it means |
|---|---|---|
| 0 | 0% | Dead muscle |
| 2 | 10% | Marginal - barely useful for most applications |
| 4 | 20% | Below average McKibben |
| 5 | 25% | Industry average (Chou & Hannaford, FESTO) |
| 6 | 30% | Good - upper range of standard McKibben |
| 7 | 35% | Excellent - requires optimized geometry |
| 8 | 40% | Exceptional - multi-filament / high-aspect-ratio territory |
| 10 | 50%+ | AeroFlex theoretical target - not yet demonstrated in production |

### 2. Force (peak pulling force at rated pressure)

Absolute force output. Size-dependent - a bigger muscle always wins here.

| Score | Force | Reference |
|---|---|---|
| 0 | < 1 N | Negligible |
| 2 | 10 N (~2.2 lbf) | Small thin McKibben, ~3 mm OD |
| 4 | 50 N (~11 lbf) | Single AeroFlex muscle, moderate pressure |
| 5 | 100 N (~22 lbf) | Benchmark for hobby-scale builds |
| 6 | 225 N (~50 lbf) | Wearable-lift per-muscle target |
| 7 | 500 N (~112 lbf) | Multi-filament bundle, high pressure |
| 8 | 1000 N (~225 lbf) | AeroFlex ~200 lbf demo range |
| 10 | 7000 N+ (~1575 lbf) | Suzumori hydraulic high-power (5 MPa, 15 mm OD) |

### 3. Force Density (force per unit weight)

The "could I rock-climb with it" metric. How much force you get per gram of muscle mass.

| Score | N/g | What it means |
|---|---|---|
| 0 | < 0.5 | Heavy, weak - industrial cylinder territory |
| 3 | 2 | Standard single-sleeve McKibben |
| 5 | 5 | Good for wearables |
| 7 | 15 | Multi-filament thin McKibben (Suzumori ~15 kgf from 2.5 mm muscle) |
| 10 | 40+ | Approaching biological muscle power density (~40 W/kg peak) |

### 4. Efficiency (mechanical work out / fluid energy in)

How much of the compressed air's energy becomes useful pulling work per full cycle.

| Score | Efficiency % | What it means                                                     |
| ----- | ------------ | ----------------------------------------------------------------- |
| 0     | < 5%         | Catastrophically wasteful                                         |
| 2     | 10%          | Typical unoptimized pneumatic McKibben                            |
| 4     | 15-20%       | Optimized pneumatic, good bladder                                 |
| 5     | 25%          | Upper bound for well-designed pneumatic                           |
| 7     | 35-40%       | Hydraulic McKibben (~2× pneumatic)                                |
| 10    | 50%+         | Theoretical limit - inelastic bladder + hydraulic + zero friction |

### 5. Bandwidth (cycle rate)

How fast the muscle can complete a full contraction → extension cycle.

| Score | Hz | Cycle time | What it means |
|---|---|---|---|
| 0 | < 0.1 | > 10 s | Too slow for anything dynamic |
| 3 | 0.5 | 2 s | Slow actuation - OK for lifts, grippers |
| 5 | 2 | 500 ms | Moderate - adequate for walking-pace exoskeletons |
| 7 | 5 | 200 ms | Fast - robotic manipulation range |
| 10 | 10+ | < 100 ms | Rapid - approaching servo motor speeds |

### 6. Durability (cycle life)

How many full contraction cycles before force or stroke degrades by >10%.

| Score | Cycles | What it means |
|---|---|---|
| 0 | < 100 | Prototype-only |
| 2 | 1,000 | Short-term demos, single-event use |
| 4 | 10,000 | Light-duty products, seasonal use |
| 5 | 50,000 | Moderate industrial duty |
| 7 | 100,000 | Heavy daily use (8 hrs/day for months) |
| 8 | 500,000 | Professional / industrial workhorse |
| 10 | 1,000,000+ | "Rock climbing every weekend for years" territory |

### 7. Compactness (packaging density)

How small the muscle (or bundle) is relative to its force class. Inversely proportional to cross-sectional area per newton.

| Score | What it looks like |
|---|---|
| 0 | Fat industrial pneumatic cylinder |
| 3 | Standard 20-40 mm OD single-sleeve McKibben |
| 5 | Standard 10-15 mm OD McKibben |
| 7 | Thin multi-filament bundle matching a human muscle's cross-section for its force |
| 10 | 2-5 mm OD thin McKibben (Suzumori-Endo scale), fits inside a finger |

### 8. Compliance (backdrivability / safety)

How well the muscle absorbs external forces without rigid resistance. The "won't hurt a human" factor.

| Score | What it means |
|---|---|
| 0 | Rigid - hydraulic cylinder, zero give |
| 3 | Stiff - high-pressure hydraulic McKibben |
| 5 | Moderate - standard pneumatic McKibben at working pressure |
| 7 | Compliant - low-pressure pneumatic, thin muscles |
| 10 | Extremely soft - depressurized or very-low-pressure thin bundles; fully backdrivable |

---

## Configuration Profiles

Pre-scored profiles for common muscle configurations. These are the polygons on the radar chart.

### Profile A - Standard single-sleeve McKibben (baseline)

The "textbook" McKibben. 20 mm OD, latex bladder, PET braid, 60 psi, single sleeve.

| Axis | Score |
|---|---|
| Stroke | 5 |
| Force | 5 |
| Force Density | 3 |
| Efficiency | 3 |
| Bandwidth | 4 |
| Durability | 5 |
| Compactness | 3 |
| Compliance | 6 |

**Shape:** average everywhere. No standout. No disaster.

### Profile B - AeroFlex multi-filament (current design target)

High-aspect-ratio thin McKibben bundle, PET overexpanded braid, 18° angle, latex bladder, ~80-100 psi, multi-filament.

| Axis | Score |
|---|---|
| Stroke | 7 |
| Force | 7 |
| Force Density | 6 |
| Efficiency | 4 |
| Bandwidth | 5 |
| Durability | 5 |
| Compactness | 7 |
| Compliance | 7 |

**Shape:** biased toward stroke + compactness + compliance. The AeroFlex thesis.

### Profile C - AeroFlex optimized (dream muscle)

Everything from Profile B, plus: silicone bladder (longevity), stiffer braid fibers (aramid or carbon), thinner walls, custom connectors, multi-filament with 60+ strands, ~100 psi.

| Axis | Score |
|---|---|
| Stroke | 8 |
| Force | 8 |
| Force Density | 8 |
| Efficiency | 5 |
| Bandwidth | 6 |
| Durability | 7 |
| Compactness | 8 |
| Compliance | 6 |

**Shape:** high everywhere except efficiency (pneumatic's inherent ceiling) and compliance (slightly reduced by stiffer braid). **This is Kevin's target muscle.**

### Profile D - Hydraulic high-power (Suzumori-Bridgestone)

15 mm OD, 5 MPa, hydraulic fluid, 30% contraction, 7 kN force.

| Axis | Score |
|---|---|
| Stroke | 6 |
| Force | 10 |
| Force Density | 9 |
| Efficiency | 7 |
| Bandwidth | 7 |
| Durability | 6 |
| Compactness | 7 |
| Compliance | 2 |

**Shape:** extreme force + efficiency + bandwidth, crushed compliance. Not safe near humans without force limiting.

### Profile E - Suzumori thin McKibben (2-5 mm OD)

Single thin muscle (not bundled). ~0.5 MPa, 20-25% contraction, ~15 kgf from 2.5 mm.

| Axis | Score |
|---|---|
| Stroke | 5 |
| Force | 2 |
| Force Density | 7 |
| Efficiency | 3 |
| Bandwidth | 7 |
| Durability | 6 |
| Compactness | 10 |
| Compliance | 9 |

**Shape:** extreme compactness + compliance. Low absolute force (it's tiny). Bundle 60 of them and force jumps to 7+, compactness drops to 7.

### Profile F - FESTO Fluidic Muscle (commercial benchmark)

Industrial-grade, integrated bladder+braid, ~6 bar, 20-25% contraction.

| Axis | Score |
|---|---|
| Stroke | 5 |
| Force | 6 |
| Force Density | 4 |
| Efficiency | 4 |
| Bandwidth | 5 |
| Durability | 8 |
| Compactness | 4 |
| Compliance | 5 |

**Shape:** durability is the standout. FESTO optimizes for industrial reliability, not peak performance.

---

## Trade-Off Matrix

When you turn one dial, other dials move. This matrix maps the couplings.

### Variable → Performance Axis Impact

| Variable change | Stroke | Force | Force Density | Efficiency | Bandwidth | Durability | Compactness | Compliance |
|---|---|---|---|---|---|---|---|---|
| **↓ Braid angle (e.g. 30° → 18°)** | ↑↑ | ↓ | - | - | - | - | - | - |
| **↑ Braid angle (e.g. 18° → 30°)** | ↓↓ | ↑ | - | - | - | - | - | - |
| **Stiffer braid material (PET → aramid)** | ↓ | ↑↑ | ↑ | ↑ | - | ↓ (flex fatigue) | - | ↓ |
| **Thinner bladder** | ↑ | - | ↑ | ↑↑ | ↑ | ↓↓ | - | ↑ |
| **Thicker bladder** | ↓ | - | ↓ | ↓ | ↓ | ↑↑ | - | ↓ |
| **Inelastic bladder (nylon film)** | ↑ | ↑ | ↑ | ↑↑ | - | ↓↓ | - | ↓ |
| **↑ Diameter** | - | ↑↑ (D²) | ↓ | - | ↓↓ (volume) | - | ↓↓ | - |
| **↓ Diameter** | - | ↓↓ | ↑ | - | ↑↑ | - | ↑↑ | ↑ |
| **↑ Aspect ratio (longer, thinner)** | ↑↑ | - | - | - | ↓ (more volume) | - (if no buckling) | ↑ | ↑ |
| **↑ Pressure** | ↑ (to saturation) | ↑↑ | ↑ | ↓ (diminishing returns) | - | ↓ | - | ↓ |
| **Multi-filament (vs single)** | ↑ | - (sum of strands) | ↑ | - | - | ↑↑ (graceful failure) | ↑ | ↑↑ |
| **↑ Fiber count / denser braid** | ↓ | ↑ | - | ↓ (more friction) | - | ↑ | - | ↓ |
| **Hydraulic (vs pneumatic)** | - | ↑ | ↑ | ↑↑ (~2×) | ↑↑ | - | - | ↓↓↓ |
| **Silicone bladder (vs latex)** | - | - | - | - | - | ↑↑ | - | - |
| **PTFE-coated fibers (reduce μ_ff)** | ↑ | - | - | ↑ | - | ↑ | - | - |
| **Better crimp (radial vs hex)** | - | - | - | ↑ | - | ↑↑ | - | - |

**Legend:** ↑↑ = strong improvement, ↑ = moderate improvement, ↓ = moderate worsening, ↓↓ = strong worsening, - = negligible effect.

---

## Application-Specific Target Profiles

What the ideal radar chart shape looks like for each application. Scores are *targets*, not current AeroFlex performance.

### Exoskeleton / Wearable Lift

Priority: **Force → Stroke → Durability → Compactness → Compliance**

| Axis | Target | Why |
|---|---|---|
| Stroke | 8 | Need 2-3 ft of lift → long muscles with high contraction |
| Force | 8 | Must lift 200 lb body weight |
| Force Density | 8 | Wearable → every gram matters |
| Efficiency | 5 | Battery-powered; can't afford waste, but pneumatic ceiling is real |
| Bandwidth | 5 | Walking pace, not sprinting - 2 Hz is enough |
| Durability | 8 | Daily use, years of service - "rock climbing every weekend" |
| Compactness | 8 | Must fit inside/alongside clothing |
| Compliance | 7 | Near humans → must be safe + shock-absorbing |

**Configuration path:** Multi-filament, high-aspect-ratio, 18° braid, silicone bladder, moderate-stiff braid (aramid?), 80-100 psi, custom small-diameter connectors.

### Animatronics / SFX

Priority: **Compliance → Bandwidth → Compactness → Stroke**

| Axis | Target | Why |
|---|---|---|
| Stroke | 6 | Limb range of motion, not max displacement |
| Force | 5 | Moving props, not lifting humans |
| Force Density | 6 | Must hide inside a costume or rig |
| Efficiency | 3 | Compressor is off-stage; efficiency is secondary |
| Bandwidth | 7 | Lifelike motion requires fast, smooth cycles |
| Durability | 6 | Show runs (weeks to months), not decades |
| Compactness | 8 | Must fit inside an animatronic body |
| Compliance | 9 | Silent, safe near performers and audience, organic motion |

**Configuration path:** Multi-filament, thin, low pressure (~30-50 psi), PET braid (cheap, flexible), latex or silicone bladder. Prioritize silence and smoothness over raw power.

### Prosthetic Hand

Priority: **Force Density → Bandwidth → Compactness → Durability**

| Axis | Target | Why |
|---|---|---|
| Stroke | 6 | Finger curl range - doesn't need 50% contraction |
| Force | 6 | Grip strength - ~50-100 N for functional grasp |
| Force Density | 9 | Must fit inside a hand-sized envelope |
| Efficiency | 5 | Battery-powered wearable |
| Bandwidth | 8 | Fast finger movements - 5+ Hz |
| Durability | 9 | Daily use, years |
| Compactness | 10 | Must fit inside a prosthetic finger |
| Compliance | 8 | Safe near human tissue, compliant grasp |

**Configuration path:** Suzumori-thin (2-5 mm OD), multi-filament bundles per finger, high-bandwidth valves, silicone bladder. This is the hardest application - everything has to be excellent.

### Soft Gripper

Priority: **Compliance → Stroke → Compactness**

| Axis | Target | Why |
|---|---|---|
| Stroke | 7 | Gripping requires significant curl |
| Force | 4 | Grasping, not crushing |
| Force Density | 5 | Desktop-sized, not wearable |
| Efficiency | 3 | Tethered to bench compressor |
| Bandwidth | 6 | Pick-and-place speed |
| Durability | 6 | Lab/industrial duty |
| Compactness | 7 | Small end-effector |
| Compliance | 10 | The entire point - conforms to object shape |

### Industrial Actuator

Priority: **Force → Durability → Efficiency → Bandwidth**

| Axis | Target | Why |
|---|---|---|
| Stroke | 5 | Specific stroke range, not maximum |
| Force | 9 | Heavy loads |
| Force Density | 5 | Size is less constrained |
| Efficiency | 7 | Running 24/7 - efficiency = money |
| Bandwidth | 7 | Production-line speed |
| Durability | 10 | Millions of cycles, zero downtime |
| Compactness | 4 | Room to be big |
| Compliance | 5 | Nice to have, not critical |

**Configuration path:** Hydraulic McKibben (Bridgestone-style), thick durable bladder, dense braid, high pressure, industrial fittings. FESTO Fluidic Muscle is the current benchmark here.

### Underwater Robot

Priority: **Force Density → Durability → Compliance**

| Axis | Target | Why |
|---|---|---|
| Stroke | 6 | Fin/limb range of motion |
| Force | 7 | Propulsion against water resistance |
| Force Density | 8 | Submersible weight budget |
| Efficiency | 6 | Battery-limited; can't waste energy |
| Bandwidth | 7 | Fin oscillation speed |
| Durability | 8 | Long mission duration, saltwater environment |
| Compactness | 7 | Hydrodynamic packaging |
| Compliance | 8 | Biomimetic locomotion requires it |

**Configuration path:** Hydraulic (water as working fluid - doubles efficiency, improves cooling, eliminates buoyancy issues from air), silicone bladder (saltwater-resistant), corrosion-resistant braid (UHMWPE or stainless), sealed end fittings.

---

## The Best Possible Muscle (Kevin's Target)

**Priorities stated:** max stroke + max force, secondary durability + compactness + force density ("rock climbing with it").

### Target shape

| Axis | Target | Score |
|---|---|---|
| Stroke | Highest possible | 9 |
| Force | Highest possible | 9 |
| Force Density | Highest force in smallest form factor | 8 |
| Efficiency | Acceptable | 5 |
| Bandwidth | Moderate (wearable-pace) | 5 |
| Durability | "Rock climbing every weekend" | 8 |
| Compactness | Wearable-scale | 8 |
| Compliance | Safe near humans | 7 |

### What has to be true to hit those numbers

| Design choice | Why | Score impact |
|---|---|---|
| **Multi-filament, not single-sleeve** | Only way to get both high stroke (individual thin muscles) AND high force (sum of the bundle) | Stroke ↑, Force ↑, Compliance ↑, Durability ↑ |
| **High aspect ratio (thin + long per fiber)** | Maximizes contraction ratio toward the 40-50% range | Stroke ↑↑ |
| **18° initial braid angle** | Sweet spot for stroke vs. force trade-off | Stroke ↑, Force acceptable |
| **Stiffer braid material (aramid or carbon)** | Raises force density per fiber - each fiber pulls harder | Force ↑, Force Density ↑ |
| **Overexpanded pattern** | Allows large radial expansion → full stroke range even with stiffer fibers | Stroke preserved |
| **Silicone bladder** | Latex ages too fast for "years of weekends." Silicone handles UV, ozone, fatigue. | Durability ↑↑ |
| **Thin bladder wall** | Reduces threshold pressure, improves efficiency | Efficiency ↑, Stroke ↑ |
| **Custom small-diameter connectors** | Enables thin-muscle construction without fitting-size bottleneck | Compactness ↑↑ |
| **80-100 psi operating pressure** | Enough for high force without burning through durability | Force ↑, Durability manageable |
| **PTFE-coated or lubricated fiber interfaces** | Reduces the ~20% friction loss | Efficiency ↑, Durability ↑ |
| **Radial crimp tooling** | Consistent seals → fewer leaks → more usable pressure at the muscle | Durability ↑, Efficiency ↑ |
| **Closed-loop re-pressurization** | Captures exhaust → re-compresses. Required for sustained wearable use. | Efficiency ↑↑ for runtime |

### What can't be solved

- **Pneumatic efficiency ceiling.** Air compressibility wastes energy. You can optimize to ~25%, but not to 50% without switching to hydraulic. Hydraulic kills compliance. Accept 5 on efficiency or accept 3 on compliance.
- **Stroke × force tension.** You *can* have both high stroke and high force - but only through multi-filament bundling. A single muscle always trades one for the other.
- **Durability × thin bladder.** Thin walls are more efficient but die faster. Silicone + careful wall thickness selection is the mitigation, not the elimination.

### The AeroFlex answer

The multi-filament, high-aspect-ratio architecture **is** the answer to "how do you get both stroke and force." It's why AeroFlex exists. Every individual fiber is thin (high stroke), and the bundle sums their forces (high force). The bundle stays compliant (each fiber flexes independently), fails gracefully (one fiber breaks, the rest work), and packages well (slender rope, not fat cylinder).

The remaining gaps between Profile C (dream muscle) and the theoretical maximum are:
1. **Bladder material** - silicone solves aging, but we haven't sourced the right size/hardness yet.
2. **Braid material** - PET works but aramid or carbon would raise force density. Need custom braid patterns at those materials.
3. **Connectors** - custom injection-molded small-diameter pass-through barbs unlock the thinnest muscles. Currently bottlenecked at ~1/4".
4. **Friction reduction** - PTFE-coated fibers or lubricated interfaces would recover ~10-15% of the force currently lost to friction.

---

## Radar Chart Data (machine-readable)

For the eventual web visualization. JSON-style for easy parsing.

```json
{
  "axes": ["Stroke", "Force", "ForceDensity", "Efficiency", "Bandwidth", "Durability", "Compactness", "Compliance"],
  "profiles": {
    "Standard McKibben (baseline)": [5, 5, 3, 3, 4, 5, 3, 6],
    "AeroFlex current target": [7, 7, 6, 4, 5, 5, 7, 7],
    "AeroFlex dream muscle": [8, 8, 8, 5, 6, 7, 8, 6],
    "Hydraulic high-power": [6, 10, 9, 7, 7, 6, 7, 2],
    "Suzumori thin (single)": [5, 2, 7, 3, 7, 6, 10, 9],
    "FESTO Fluidic Muscle": [5, 6, 4, 4, 5, 8, 4, 5]
  },
  "applicationTargets": {
    "Exoskeleton (wearable lift)": [8, 8, 8, 5, 5, 8, 8, 7],
    "Animatronics": [6, 5, 6, 3, 7, 6, 8, 9],
    "Prosthetic Hand": [6, 6, 9, 5, 8, 9, 10, 8],
    "Soft Gripper": [7, 4, 5, 3, 6, 6, 7, 10],
    "Industrial": [5, 9, 5, 7, 7, 10, 4, 5],
    "Underwater Robot": [6, 7, 8, 6, 7, 8, 7, 8],
    "Kevin Dream Muscle": [9, 9, 8, 5, 5, 8, 8, 7]
  }
}
```

---

## Next steps

- [ ] Validate scores against bench data as AeroFlex muscles get characterized on the test bench.
- [ ] Build the interactive spider chart (likely D3.js or Chart.js radar chart) for the website.
- [ ] Let users input their application priorities → auto-generate the "ideal configuration" recommendations.
- [ ] Add a "configuration builder" - select braid material / bladder / diameter / pressure → auto-score the profile and overlay it on the radar chart.
- [ ] Tie the scores to the AeroFlex Simulator and Configurator products.

---

## References

- Variable definitions from [`PAM Design Variables.md`](PAM%20Design%20Variables.md) (PAM Variables catalog in this folder)
- Force equation and theory from [`../theory.md`](../docs/theory.md)
- Suzumori-Endo specs from [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md)
- Design targets from [`../design.md`](../docs/design.md)
- Application specs from the wearable-lift project docs (private [AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private) repo)
- Meller et al. (2014), *Reconsidering the McKibben muscle: Energetics, operating fluid, and bladder material*
- MDPI Actuators (2025), *Recent Developments in Pneumatic Artificial Muscle Actuators*
