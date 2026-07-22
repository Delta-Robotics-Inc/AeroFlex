### Variables Affecting the Performance Pneumatic Artificial Muscle (PAM) 
A comprehensive catalog of every variable that affects the efficiency, force output, stroke, durability, and dynamic behavior of a McKibben-style pneumatic artificial muscle. Each variable is described with its physical mechanism, its effect on the muscle's output, and (where known) a quantitative relationship or design rule.

This is the master reference for AeroFlex R&D. When we change one thing and something else breaks, this document tells us why.

---

## 1. Braid Variables

These control how the sleeve converts radial bladder expansion into axial contraction. The braid is the mechanism; everything else is plumbing.

### 1.1 Braid material

**What it is.** The fiber the braided sleeve is made from - PET, nylon, aramid (Kevlar), carbon fiber, fiberglass, UHMWPE (Dyneema/Spectra), stainless steel wire, etc.

**How it affects the muscle.**
- **Stiffness (elastic modulus).** Stiffer fibers (aramid, carbon) resist radial expansion more aggressively → higher force at lower contraction, but reduced stroke. Compliant fibers (PET, nylon) allow more radial expansion → longer stroke but lower peak force.
- **Tensile strength.** Sets the burst pressure ceiling. Weak fibers fail before the bladder does.
- **Friction coefficient.** Different materials have different fiber-on-fiber and fiber-on-bladder friction (see 1.8 and 2.5). PTFE-coated fibers reduce friction; aramid is notoriously "grabby."
- **Fatigue resistance.** Some fibers (PET, nylon) tolerate millions of flex cycles; others (carbon) are brittle under repeated bending at the braid crossover points.
- **Temperature and UV tolerance.** Outdoor or high-temp applications eliminate some materials.
- **Cost and availability.** PET Techflex Overexpanded is the current AeroFlex choice because it's cheap, available, and has large radial expansion. Stiffer fibers would raise force density but the target braid pattern isn't readily available off the shelf.

**Current AeroFlex choice:** PET Techflex Flexo Overexpanded. See [`../design.md`](../docs/design.md) and [`../components.md`](../docs/components.md).

### 1.2 Initial braid angle (θ₀)

**What it is.** The angle of the braid fibers relative to the muscle's longitudinal axis *at rest* (zero pressure, full resting length). Measured in degrees.

**How it affects the muscle.**
- **Stroke.** Smaller initial angles (~15-20°) → larger stroke (more room for the angle to change during contraction). Larger initial angles (>30°) → shorter stroke.
- **Force.** The McKibben force equation includes the term `3cos²θ − 1`. At θ = 0° (fibers parallel to the axis) this term = 2 (maximum force, zero stroke). At θ = 54.7° (the "magic angle") the term = 0 (zero force, maximum expansion). At θ > 54.7° the muscle would *extend* under pressure instead of contracting.
- **The braid angle is not constant.** As the muscle contracts, the braid angle increases. The force curve is therefore nonlinear - force drops as contraction progresses because θ is shifting.

**Design rule.** AeroFlex targets ~18° initial braid angle (matching the Suzumori-Endo multifilament spec). This trades some peak force for usable stroke in the 20-35% range.

**Key reference:** Chou & Hannaford (1996), [`Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf).

### 1.3 Braid geometry / weave pattern

**What it is.** The structural pattern of the braid - how fibers cross over and under each other. Common patterns: diamond braid (1-over-1), regular braid (2-over-2), Hercules braid (3-over-3), triaxial braid (adds axial fibers).

**How it affects the muscle.**
- **Radial expansion freedom.** Open, overexpanded patterns (like the Techflex Overexpanded) allow more radial growth → more stroke. Tight, dense patterns restrict expansion → more force but less stroke.
- **Structural stability.** Denser braids resist buckling at high contraction ratios.
- **Fiber distribution.** Patterns with more crossover points distribute load more evenly; fewer crossover points can create stress concentrations.
- **Torque generation.** Non-symmetric patterns can cause the muscle to twist during contraction, which wastes energy and complicates mounting.

### 1.4 Fiber count / pick count

**What it is.** The number of individual fiber strands in the braid. "Pick count" is a textile term for the number of carrier bobbins on the braider - directly sets fiber density per unit length.

**How it affects the muscle.**
- **Force capacity.** More fibers → more load-bearing cross-section → higher burst pressure and force capacity.
- **Radial expansion.** More fibers per unit length → denser braid → less room for the bladder to expand → less stroke for a given pressure.
- **Friction.** More fibers = more crossover points = more fiber-on-fiber friction = more hysteresis. Trade-off against load capacity.

**Suzumori-Endo thin McKibben spec:** 24 outer fibers per thin muscle, 18° braid angle. See [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md).

### 1.5 Individual fiber diameter

**What it is.** The cross-section diameter of each fiber strand in the braid.

**How it affects the muscle.**
- **Bending stiffness of the braid.** Thicker fibers → stiffer braid (bending stiffness scales with d⁴). Stiffer braid → harder for the bladder to push it out → higher threshold pressure to initiate contraction.
- **Weight.** Thicker fibers add mass without proportional force gain (diminishing returns).
- **Flex fatigue.** Thicker fibers accumulate more strain at bend points and are more susceptible to fatigue cracking (especially in brittle materials like carbon).

### 1.6 Braid coverage / tightness

**What it is.** The percentage of the bladder surface covered by the braid at rest. 100% = fully covered, no gaps visible. Overexpanded braids can be well below 100% when not pressurized.

**How it affects the muscle.**
- **At low coverage (overexpanded).** The braid has room to tighten before it starts resisting expansion. This gives a "free" initial stroke range where the bladder expands easily → lower threshold pressure, softer initial response.
- **At high coverage (tight).** The braid immediately resists expansion → higher threshold pressure, stiffer response, higher force for a given contraction.
- **Uniformity.** Uneven coverage creates local stress concentrations where the bladder can herniate through gaps.

### 1.7 Braid extensibility limit

**What it is.** The maximum radial expansion the braid geometry allows before the fibers "lock" - reaching the angle where they can no longer slide past each other. This is a geometric constraint, not a material strength limit.

**How it affects the muscle.**
- **Maximum contraction ratio.** The muscle cannot contract further than what the braid extensibility allows, regardless of pressure.
- **End-of-stroke stiffening.** As the braid approaches its extensibility limit, the muscle stiffens rapidly - the last few percent of contraction require disproportionately more pressure.

### 1.8 Fiber-on-fiber friction (μ_ff)

**What it is.** The friction coefficient between individual braid fibers at their crossover points as they slide past each other during muscle contraction and extension.

**How it affects the muscle.**
- **Hysteresis.** This is the *dominant* cause of hysteresis in McKibben muscles. The force-displacement curve during inflation is different from the curve during deflation because friction opposes motion in both directions. Research indicates fiber-on-fiber (strand-on-strand) friction contributes **up to 20%** of the total contraction force as a loss term.
- **Energy efficiency.** Every joule lost to fiber friction is a joule that doesn't become mechanical work.
- **Velocity-independent component.** This friction is primarily Coulomb friction (constant magnitude, direction-dependent), not viscous. It doesn't change much with speed.
- **Mitigation.** Lubricants, PTFE coatings on fibers, or choosing inherently slippery fiber materials (UHMWPE) reduce μ_ff. Trade-off: some coatings reduce fiber-on-bladder grip, which can cause the braid to slip.

**Key reference:** Chou & Hannaford (1996), and the Tondu (2012) review of McKibben modeling. Also *Dynamic modeling of McKibben pneumatic artificial muscles for antagonistic actuation*.

### 1.9 Fiber stiffness / elastic modulus

**What it is.** The Young's modulus of the fiber material - how much it stretches under load.

**How it affects the muscle.**
- **Force transmission efficiency.** Higher-modulus fibers transmit more of the bladder's radial expansion into axial force without stretching. Low-modulus fibers absorb some energy elastically, reducing output.
- **Braid angle stability.** Stiff fibers maintain their geometry more precisely under load. Compliant fibers allow the braid angle to drift under sustained pressure, causing creep.
- **Resonance and dynamic response.** Fiber stiffness affects the natural frequency of the muscle's radial oscillation mode - relevant for high-bandwidth applications.

---

## 2. Bladder Variables

The bladder is the pressure vessel. It converts air pressure into radial expansion. Everything the braid does depends on how well the bladder pushes outward.

### 2.1 Bladder material

**What it is.** The elastomeric inner tube - latex, silicone, polyurethane, nitrile, thermoplastic elastomer, or (experimentally) inelastic membranes like nylon film.

**How it affects the muscle.**

| Property | Latex | Silicone | Polyurethane | Inelastic (nylon film) |
|---|---|---|---|---|
| **Elastic modulus** | Very low (soft) | Low-medium | Medium | High (nearly rigid) |
| **Cyclic strain tolerance** | Excellent | Good | Good | Poor - fatigues fast |
| **Aging / UV / ozone** | Poor - degrades | Excellent | Good | Good |
| **Permeability** | High - leaks slowly | Lower | Low | Very low |
| **Energy absorbed stretching** | Low → efficient | Medium | Medium | Nearly zero → very efficient |
| **Hysteresis contribution** | Low-medium | Medium | Medium-high | Very low (but high braid-side hysteresis) |
| **Cost** | Very cheap | Moderate | Moderate | Cheap |
| **Sourcing** | Easy | Hard at target sizes | Moderate | Easy |

**Key insight from research.** Using an inelastic bladder (nylon film) **significantly improves efficiency, force capacity, and contraction range** because nearly zero energy goes into stretching the bladder. However, inelastic bladders **increase hysteresis** because the braid must now do all the work of returning the muscle to rest length - there's no elastic restoring force from the bladder. They also fatigue faster because the membrane buckles and creases during deflation instead of elastically recovering.

**Current AeroFlex choice:** latex slingshot tubing. Silicone on the roadmap for longevity. See [`../design.md`](../docs/design.md), [`../components.md`](../docs/components.md).

**Key reference:** Meller, Bryant, Garcia (2014), *Reconsidering the McKibben muscle: Energetics, operating fluid, and bladder material.*

### 2.2 Bladder wall thickness

**What it is.** The wall thickness of the inner tube, typically measured in mm or mils.

**How it affects the muscle.**
- **Threshold pressure.** A thicker bladder requires more pressure to begin expanding. This is effectively "wasted" pressure that doesn't produce useful contraction - it just inflates the tube.
- **Energy efficiency.** Thicker walls store more elastic energy during inflation, returning some of it during deflation (which helps with restoring force) but reducing net mechanical efficiency. Thinner walls are more efficient at converting pneumatic energy to mechanical work.
- **Durability.** Thicker walls resist puncture, abrasion from the braid, and fatigue failure. **This is the core tension: thinner is more efficient; thicker is more durable.**
- **Radial expansion rate.** Thinner walls expand faster for a given pressure → faster dynamic response.
- **Burst pressure.** Thinner walls fail at lower pressures, all else equal.

**Design rule.** Find the thinnest wall that survives the target cycle life at the target operating pressure. Then add a safety factor.

### 2.3 Bladder elastic modulus / stiffness

**What it is.** The Shore hardness or Young's modulus of the bladder material - how much force it takes to stretch the bladder a given amount.

**How it affects the muscle.**
- **Same direction as thickness.** Stiffer material acts like a thicker wall: higher threshold pressure, less stroke for a given pressure, more energy stored in the bladder.
- **Restoring force.** A stiffer bladder provides a stronger passive restoring force during deflation → faster return to rest length, less need for antagonistic muscles or springs. Trade-off: that restoring force is pressure you're fighting during inflation.
- **Operating window.** Very soft bladders (low Shore A, ~20-30) give the widest operating window (lowest threshold, most responsive). Very stiff bladders (~60-80 Shore A) narrow the window and require higher pressures for the same stroke.

### 2.4 Bladder permeability

**What it is.** The rate at which air molecules diffuse through the bladder wall, even without a hole. All elastomers are slightly permeable to gas.

**How it affects the muscle.**
- **Slow leak.** High permeability means the muscle slowly depressurizes even with all valves closed. The muscle "goes soft" over minutes to hours. Relevant for applications that hold pressure (e.g., maintaining a lifted position).
- **Operating fluid matters.** CO₂ permeates through latex ~5× faster than air (relevant since AeroFlex uses CO₂ paintball tanks). Silicone has lower air permeability than latex.
- **Not the dominant leak source.** In practice, end-fitting leaks and crimp failures dominate over permeation. But for multi-hour holds, it adds up.

### 2.5 Bladder-braid friction (μ_fb)

**What it is.** The friction coefficient between the outer surface of the bladder and the inner surface of the braided sleeve.

**How it affects the muscle.**
- **Energy loss.** The bladder slides against the braid during every contraction and extension cycle. Friction here dissipates energy as heat. Combined with fiber-on-fiber friction, this is the primary cause of the ~20% force loss from the theoretical ideal.
- **Hysteresis contribution.** Higher bladder-braid friction → wider hysteresis loop → less predictable force at a given contraction.
- **Bladder wear.** High friction accelerates bladder surface wear, leading to micro-abrasions that grow into failure points over thousands of cycles.
- **Mitigation.** Lubricate the interface (silicone spray, PTFE lining, talcum powder), choose naturally slippery bladder materials (silicone is better than latex here), or use bladders with a smooth exterior finish.

### 2.6 Bladder fatigue life / aging

**What it is.** How the bladder material degrades over time and cycling.

**How it affects the muscle.**
- **Latex aging.** Latex degrades from UV, ozone, and heat. Becomes stiff, cracks, loses elasticity. Shelf life is months to a few years depending on storage conditions.
- **Cyclic fatigue.** Every inflation cycle strains the bladder. Micro-cracks accumulate at stress concentrations (near end fittings, where the braid presses hardest, where the wall is thinnest).
- **Creep.** Under sustained pressure, the bladder slowly stretches permanently ("set"), increasing the resting diameter and changing the muscle's geometry over its lifetime.
- **Temperature.** High operating temperatures accelerate all degradation modes.

**Validation plan:** See [`../design.md`](../docs/design.md) - Temperature and humidity aging for latex and PET, with documented drift and maintenance intervals.

---

## 3. Geometric Variables

The overall shape of the muscle. These are the dimensions the designer chooses.

### 3.1 Internal diameter (D)

**What it is.** The inner diameter of the bladder at rest, before pressurization.

**How it affects the muscle.**
- **Force.** Force scales with D² (from the force equation: `F ∝ πD²/4`). Doubling the diameter quadruples the force. This is the single strongest lever for force output.
- **Stroke.** Larger diameters give the braid more room to expand radially → potentially larger absolute displacement, though the *percentage* stroke stays roughly the same.
- **Bandwidth.** Larger diameters mean more internal volume → slower to fill → slower response time.
- **Weight.** Larger diameters mean more material → heavier per unit length.

### 3.2 Resting length (L₀)

**What it is.** The length of the muscle at zero pressure, before contraction.

**How it affects the muscle.**
- **Absolute stroke.** Stroke (ΔL) = contraction ratio × L₀. A longer muscle produces more absolute displacement at the same contraction ratio. A 100 mm muscle at 25% stroke → 25 mm displacement. A 300 mm muscle → 75 mm.
- **Force.** Resting length does not directly appear in the idealized force equation. But longer muscles have more distributed friction losses (more braid crossover points) and more dead volume.
- **Buckling.** Very long, slender muscles are more prone to lateral buckling under compression loads.

### 3.3 Aspect ratio (L₀ / D)

**What it is.** The ratio of resting length to diameter. AeroFlex's signature design parameter.

**How it affects the muscle.**
- **Contraction ratio.** Higher aspect ratio → slightly higher stroke percentage. Long, slender muscles beat short, fat ones for displacement. The AeroFlex target is ~50% contraction (currently theoretical).
- **Force.** Lower aspect ratio (fat, short) → higher force for a given pressure (because D is larger). Trade-off against stroke.
- **Packaging.** High-aspect-ratio muscles fit in slender spaces (cable routing, wearables, exoskeletons). Low-aspect-ratio muscles need wide mounting.
- **Multi-filament unlock.** The Suzumori-Endo multifilament architecture works *because* of high aspect ratios - thin, long muscles bundled together. A low-aspect-ratio design doesn't benefit from multi-filament bundling.

**AeroFlex goal:** maximize aspect ratio to push stroke toward 50%. See [`../design.md`](../docs/design.md).

### 3.4 End fitting geometry / dead volume

**What it is.** The shape, size, and internal volume of the end caps (barbed fittings, push-to-connect fittings, crimped ferrules) at both ends of the muscle.

**How it affects the muscle.**
- **Dead volume.** Air inside the end fittings that contributes to the volume the compressor must fill but doesn't produce contraction. Reduces efficiency and slows response time.
- **Pressure rating.** The end cap determines the maximum safe operating pressure - it's usually the weakest point. Crimp quality, seal quality, and fitting material all gate the burst pressure.
- **Active length reduction.** The portion of the muscle inside the end fitting is constrained and can't contract. Effective active length = total length − 2 × fitting engagement length. Short muscles lose a higher percentage of their length to fittings.
- **Localized stress.** The transition from the constrained fitting region to the free muscle body is a stress concentration point. Most failures occur at or near the end fittings.
- **Modeling accuracy.** Models that ignore end-cap geometry can be off by 30-50% on force predictions. Adding correction factors for end-cap shape significantly improves accuracy.

**Current AeroFlex design:** barbed fitting on one end, push-to-connect on the other, with a hydraulically crimped hose ferrule. See [`../design.md`](../docs/design.md) and [`../products/tools.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/tools.md) for crimp quality impacts.

---

## 4. Operating Variables

Things the operator / controller decides at runtime. Not fixed by design (mostly).

### 4.1 Operating pressure (P)

**What it is.** The gauge pressure inside the bladder during operation, in psi or kPa.

**How it affects the muscle.**
- **Force.** Force scales linearly with P (from the force equation: `F ∝ P`). Higher pressure → proportionally more force. This is the primary control input.
- **Stroke.** Higher pressure drives the braid angle further from its initial value → more contraction. But the relationship saturates - eventually the braid reaches its extensibility limit and more pressure doesn't produce more stroke.
- **Efficiency.** There's an optimal operating pressure for each muscle geometry. Below it, the muscle is under-utilized. Above it, you're fighting the braid's extensibility limit and losing energy to friction.
- **Fatigue.** Higher pressure accelerates bladder fatigue, increases fiber stress, and raises the risk of burst failure.

**Typical AeroFlex range:** 30-100 psi (~200-700 kPa). The wearable-lift prototype targets 90-120 psi.

### 4.2 Operating fluid

**What it is.** The medium filling the bladder - compressed air (pneumatic), water (hydraulic), oil, or gas mixtures.

**How it affects the muscle.**

| Property | Pneumatic (air) | Hydraulic (water) |
|---|---|---|
| **Compliance** | High - air compresses → built-in shock absorption, safe near humans | Low - water is incompressible → stiff, fast, precise |
| **Efficiency** | Low - compressing air is thermodynamically wasteful; ~10-25% cycle efficiency | ~2× pneumatic - less energy lost to compression |
| **Bandwidth** | Lower - compressible fluid means slower response | Higher - incompressible fluid transmits pressure instantly |
| **Force bandwidth** | Lower | Higher (higher stiffness = faster force changes) |
| **Weight** | Light (air weighs nothing) | Heavier (water adds mass to the muscle) |
| **Safety** | Inherently safe - air leaks are harmless | Water leaks are messy; oil leaks are worse |
| **Plumbing complexity** | Simpler - exhausts to atmosphere | Closed loop required - needs a return line |

**Key insight from research.** Powering McKibben muscles hydraulically roughly **doubles** the efficiency compared to pneumatic operation. But pneumatic compliance is a *feature* for human-interaction applications (exoskeletons, prosthetics, animatronics) - it's not just a bug.

**AeroFlex choice:** pneumatic (air and CO₂).

### 4.3 Flow rate and valve response

**What it is.** How fast the working fluid enters and leaves the muscle, determined by the valve orifice, supply pressure, and tubing diameter.

**How it affects the muscle.**
- **Contraction speed.** The muscle can't contract faster than the air can fill it. Flow rate sets the ceiling on bandwidth.
- **Extension speed.** Similarly limited by exhaust flow rate. Many muscles contract faster than they extend because exhaust is through a smaller orifice.
- **Pressure transients.** Fast valve opening can cause pressure spikes (water hammer in hydraulic systems, less of an issue in pneumatic). Slow valve opening gives smoother, more controllable response.

**Wearable-lift spec:** 2-4 L/min per muscle for 1-2 s lift time.

### 4.4 Internal volume

**What it is.** The total gas/fluid volume inside the muscle at any point in its stroke.

**How it affects the muscle.**
- **Fill time.** Larger internal volume → more fluid needed → longer time to reach operating pressure at a given flow rate.
- **Energy cost per cycle.** Each cycle requires compressing (pneumatic) or pumping (hydraulic) enough fluid to fill the volume. Larger muscles cost more energy per cycle.
- **Compliance (pneumatic).** More air volume = more compliant muscle. Can be a feature (shock absorption) or a bug (sluggish response).
- **Scales with D² and L.** Volume ∝ π(D/2)² × L. Doubling the diameter quadruples the internal volume (and the fill time).

### 4.5 Flow path resistance

**What it is.** The total pressure drop between the valve and the muscle - set by tubing length, tubing inner diameter, number of fittings, manifold design, and any inline sensors.

**How it affects the muscle.**
- **Effective pressure at muscle.** The pressure the muscle "sees" is the valve output minus the pressure drop across the flow path. Long, thin tubing with many fittings can eat 10-30% of the supply pressure.
- **Bandwidth.** Higher flow path resistance → slower fill and exhaust → slower muscle response.
- **Heat generation.** In pneumatic systems, air flow through restrictions generates heat (Joule-Thomson effect in reverse - not usually significant, but measurable at high flow rates).

### 4.6 Temperature and environment

**What it is.** The ambient temperature, humidity, UV exposure, and chemical environment the muscle operates in.

**How it affects the muscle.**
- **Bladder aging.** Heat + UV + ozone accelerate latex degradation. Silicone is much more resistant.
- **Braid aging.** PET is UV-sensitive. Aramid and carbon are more stable.
- **Air density.** Cold air is denser → more mass per liter → slightly different fill characteristics.
- **Humidity.** Moisture in compressed air can cause corrosion in fittings, mold in latex bladders, and inconsistent pressure readings.
- **Extreme cold.** CO₂ tanks perform poorly in cold weather (lower vapor pressure).

### 4.7 Pre-tension / preload

**What it is.** The mechanical tension applied to the muscle before pressurization - e.g., a spring pulling the muscle to its full resting length, or a dead weight hanging from it.

**How it affects the muscle.**
- **Starting braid angle.** Pre-tension stretches the muscle slightly, reducing the initial braid angle → changes the starting point on the force-contraction curve.
- **Restoring force.** Pre-tension provides a passive return force that helps the muscle extend after deflation - reduces the need for active exhaust or antagonistic muscles.
- **Available stroke.** Pre-tension can slightly increase available stroke by ensuring the muscle starts from its true full-length position (vs. being slightly slack).

### 4.8 Cycle rate / duty cycle

**What it is.** How often the muscle is activated (frequency) and what fraction of each cycle it spends pressurized (duty).

**How it affects the muscle.**
- **Heat buildup.** Friction generates heat. At high cycle rates, the muscle doesn't have time to cool between cycles. Temperature rises → accelerated aging.
- **Fatigue rate.** More cycles = more fatigue damage. The force-cycle-life relationship is the S-N curve of the muscle.
- **Air consumption.** At high cycle rates, pneumatic systems consume air faster → need larger compressors or tanks.

---

## 5. System-Level Variables

Things that emerge from how the muscle is assembled and integrated, not from any single component.

### 5.1 Crimp quality / seal consistency

**What it is.** How well the end fitting is crimped onto the braid and bladder - uniformity of compression, concentricity, absence of gaps.

**How it affects the muscle.**
- **Leak rate.** A bad crimp leaks. Leak rate directly reduces effective operating pressure and wastes compressed air.
- **Burst pressure.** A non-uniform crimp creates stress concentrations that fail at lower pressures than a uniform one.
- **Appearance and trust.** Sloppy crimps look bad and undermine confidence in the product.
- **Tool dependency.** Hex crimpers (2-sided) produce inconsistent crimps. Radial crimpers (full circumference) produce uniform crimps. See [`../products/tools.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/tools.md).

### 5.2 Multi-filament vs. single-sleeve architecture

**What it is.** Whether the muscle is one large braided sleeve (traditional McKibben) or a bundle of many thin muscles sharing a single air supply (Suzumori-Endo multifilament / AeroFlex approach).

**How it affects the muscle.**

| Property | Single sleeve | Multi-filament bundle |
|---|---|---|
| **Compliance during contraction** | Stiffens significantly as it contracts (diameter increases) | Stays compliant - each thin muscle is flexible |
| **Failure mode** | Catastrophic - one failure = muscle dead | Graceful - one fiber fails, bundle continues with minimal leak |
| **Aspect ratio** | Limited by practical diameter range | Can achieve very high aspect ratios (thin + long) |
| **Stroke** | 20-30% typical | Potential for higher stroke at same pressure due to high aspect ratio |
| **Force density** | Good | Similar or better (many thin muscles add up) |
| **Repairability** | Replace the whole muscle | Patch or seal the failed fiber, keep the rest |
| **Manufacturing** | Simple - one tube, one braid, two fittings | More complex - many tubes, shared manifold, bundling process |

**AeroFlex philosophy:** multi-filament, high-aspect-ratio. Directly inspired by Suzumori-Endo. See [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md).

### 5.3 Bundle count (if multi-filament)

**What it is.** The number of individual thin muscles in a multi-filament bundle.

**How it affects the muscle.**
- **Force.** Roughly linear with count - N muscles ≈ N × single-muscle force (minus losses from bundle packing inefficiency).
- **Redundancy.** More muscles = more redundancy = more graceful failure.
- **Bundle diameter.** More muscles = larger bundle cross-section = potentially lower aspect ratio at the bundle level (counteracting the individual-muscle advantage).
- **Air distribution.** More muscles sharing one manifold = more complex distribution = risk of uneven pressurization.

**Suzumori-Endo spec:** ~60 thin muscles per bundle, 310 mm long. See [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md).

### 5.4 Leak rate

**What it is.** The total air loss from the assembled muscle system - through the bladder (permeation), around the end fittings (seal leaks), and through any damaged fibers (multi-filament).

**How it affects the muscle.**
- **Effective pressure.** Any leak reduces the steady-state pressure inside the muscle for a given supply.
- **Air consumption.** Leaks waste compressed air, draining tanks or overworking compressors.
- **Hold capability.** A muscle that leaks can't hold a static load without continuous supply. Critical for applications like wearable lifts.
- **Detection.** The AeroFlex validation plan includes leak testing as step 1 (before force-stroke mapping).

### 5.5 Air compressibility (pneumatic only)

**What it is.** The inherent compressibility of air as a working fluid.

**How it affects the muscle.**
- **Compliance.** Compressed air acts as a spring - the muscle stores energy in the compressed gas and can absorb external shocks without rigid resistance. This is the core safety advantage for human-interaction applications.
- **Efficiency loss.** Compressing air is thermodynamically wasteful. A significant fraction of the input energy goes into heating the air during compression, then dissipates before the muscle uses it. This is why hydraulic McKibben muscles are ~2× more efficient.
- **Position control difficulty.** Because the gas is compressible, the muscle's position at a given pressure depends on the load. This makes open-loop position control imprecise and closed-loop control more complex.

---

## 6. Performance Outputs (What the Variables Produce)

These are the measurable outcomes. Every variable above feeds into one or more of these.

| Output | What it is | Primary drivers |
|---|---|---|
| **Contraction ratio (%)** | ΔL / L₀ × 100 | Aspect ratio, braid angle, braid extensibility, operating pressure, bladder stiffness |
| **Force (N or lbf)** | Axial pulling force | P, D², braid angle (3cos²θ−1), minus friction losses |
| **Bandwidth (Hz)** | How fast the muscle can complete one full contraction-extension cycle | Internal volume, flow rate, valve speed, fluid compressibility |
| **Hysteresis (N or %)** | Force difference between inflation and deflation paths at the same contraction | Fiber-on-fiber friction (~dominant), bladder-braid friction, bladder viscoelasticity |
| **Energy efficiency (%)** | Mechanical work out / fluid energy in | Bladder thickness/stiffness, operating fluid, friction, dead volume, air compressibility |
| **Fatigue life (cycles)** | Cycles to X% force/stroke loss | Bladder material, operating pressure, cycle rate, temperature, crimp quality, fiber fatigue |
| **Compliance (N/mm)** | Resistance to external displacement | Air compressibility, bladder stiffness, braid stiffness, operating pressure |
| **Leak rate (mL/min)** | Air loss at operating pressure | Bladder permeability, crimp quality, end-fitting seal, fiber damage |
| **Buckling tendency** | Whether the muscle bows laterally under load | Aspect ratio, operating pressure, braid stiffness, external constraints |

---

## 7. Variables Not Yet Explored

Ideas for investigation, not yet confirmed in AeroFlex testing.

- **Accordion-folded bladders.** Folding the membrane on itself (like bellows) reportedly reduces hysteresis by mitigating material strain during inflation. Trade-off with manufacturing complexity.
- **Variable-angle braids.** A braid whose angle changes along the muscle's length (tapered or segmented). Could optimize the force-stroke curve for specific applications.
- **Hybrid fluid systems.** Air for compliance + liquid for thermal management (similar to the ThermoFlex liquid-cooling concept applied to pneumatics).
- **Active braid fibers.** Fibers that change stiffness or length on command (SMA fibers, electroactive polymers) - turning the braid from a passive mechanism into an active one.
- **Embedded sensing fibers.** Conductive fibers in the braid for pressure / contraction sensing without external hardware (Suzumori-Endo smart McKibben approach). See [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md).

---

## References

- Chou & Hannaford (1996), *Measurement and Modeling of McKibben Pneumatic Artificial Muscles*. [`Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf)
- Tondu & Lopez (2000), *Modeling and Control of McKibben Artificial Muscle Robot Actuators*. [`McKibben_Robot_Muscle.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/McKibben_Robot_Muscle.pdf)
- Tondu (2012), *Modelling of the McKibben artificial muscle: A review*. [SAGE](https://journals.sagepub.com/doi/10.1177/1045389X11435435)
- Meller, Bryant, Garcia (2014), *Reconsidering the McKibben muscle: Energetics, operating fluid, and bladder material*. [SAGE](https://journals.sagepub.com/doi/10.1177/1045389X14549872)
- Kurumaya, Nabae, Endo, Suzumori (2017), *Design of Thin McKibben Muscle and Multifilament Structure*. [`Thin McKibben muscle and multifilament structure.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Thin%20McKibben%20muscle%20and%20multifilament%20structure.pdf)
- MDPI Actuators (2025), *Recent Developments in Pneumatic Artificial Muscle Actuators*. [MDPI](https://www.mdpi.com/2076-0825/14/12/582)
- Soft Robotics Toolkit, *Pneumatic Artificial Muscles*. [softroboticstoolkit.com](https://softroboticstoolkit.com/book/export/html/168891)
