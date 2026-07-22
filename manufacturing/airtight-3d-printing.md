# How to Make 3D Printed Parts Air-Tight

Last updated: 2026-06-09

How to design, print, and finish an FDM/FFF part - specifically a **pneumatic/gas manifold** ([`../products/manifold-standard.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/manifold-standard.md)) - so that it holds pressure without leaking. This is a layered process: get as far as you can with **print settings + geometry** (the foundation), then add finishing steps (annealing, vapor smoothing, coating/impregnation) only as needed. The goal is the *fewest steps and man-hours* that reliably pass a leak test for your working pressure.

![Sliced cross-section of a 3D-printed pneumatic connector block in the slicer preview, showing the thick wall loops and dense infill that make the part airtight](../assets/3d-printed-internal-view.png)

*Inside an airtight print: wall loops carry the seal, so walls are sized
from interlayer strength and loop count - not bulk material strength.*

Every numeric recommendation is traceable to a source in §13. Where the evidence is weak or sources disagree, that is called out explicitly rather than smoothed over.

> [!NOTE]
> **This is a living document.** The **[Results Library](#12-results-library) (§12)** at the end is where you log what actually worked: material, settings, finish, test pressure, pass/fail. Master table + a detail block per build + a copy-paste template. That's the section to edit as we learn.

> [!IMPORTANT]
> **The single most important finding:** no amount of print settings makes a thin-wall FDM part reliably gas-tight much above ~2 bar (≈30 psi) on its own. Everyone who actually pressure-tests (Prusa, CPSdrone, "German Engineer," CNC Kitchen) converges on the same answer: good settings get you 80-90% of the way, and a **penetrating impregnant** (Dichtol AM Hydro) or epoxy closes the rest. For a gas manifold, treat impregnation as the *expected final step*, not an optional one. The biggest settings-only lever is **brick layers** (§5.4).

---

## 1. Scope and the honest verdict on each method

This SOP covers four method families, applied in order. Each section gives the honest verdict so you don't waste man-hours on a step that won't help.

| Method                                  | What it actually does                                                | Verdict for an air-tight manifold                                                                                                                                      |
| --------------------------------------- | -------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **1. Print settings + geometry** (§4-5) | Reduces the inter-bead / inter-layer voids that *are* the leak paths | **Foundation. Mandatory.** Gets you watertight and low-pressure airtight. **Brick layers** is the standout.                                                            |
| **2. Annealing** (§6)                   | Stress relief + heat resistance. For PLA only, also crystallinity.   | **Does NOT seal leaks** in PETG/ABS/ASA and can *open* them via warping. Use only for heat resistance, or use *encased re-melt* (§6.4) if true layer fusion is needed. |
| **3. Acetone vapor smoothing** (§7)     | Seals surface + near-surface (~0.1-0.3 mm) porosity on ABS/ASA       | Good **second choice** for ABS/ASA. Seals the skin, not a through-leaking wall. Risk: clogs small manifold bores. **Not for PETG** (not acetone-soluble).              |
| **4. Coatings / impregnation** (§8)     | Fills/seals remaining pores; impregnant reaches internal channels    | **The reliable finisher.** Dichtol AM Hydro (primary) or vacuum impregnation. Epoxy for external skin only - it can't seal internal bores.                             |

A tempting plan - print settings + anneal PETG first; if that fails, vapor-smooth ABS/ASA; then coatings - is sound *except* that annealing is not a sealing step. The recommended path is therefore: **PETG with optimized settings + brick layers → leak test → Dichtol AM Hydro impregnation if it doesn't pass.** Annealing is kept in the process only where heat resistance is needed. See §10 for the end-to-end procedures.

---

## 2. Safety (read before any pressure work)

> [!WARNING]
> **Pneumatic pressure stores lethal energy - this is the most dangerous part of the whole process.** Compressed gas holds roughly **2,700× more energy per unit volume than water** at the same pressure. A 3D-printed part that ruptures under gas pressure does not crack quietly - it explodes, throwing shrapnel and a blast wave in milliseconds.
> - **Coatings and good prints make a part *leak-tight*. They do NOT make it a *rated pressure vessel*.** Never use a sealed FDM print to store high-pressure gas (e.g. propane, compressed air tanks). Keep it to modest pneumatic line/working pressures and derate generously.
> - **Do all high-pressure validation HYDRAULICALLY (water-filled), not pneumatically** (§9.5). Water is near-incompressible - a hydraulic failure just dribbles.
> - **Design for burst ≥ 4× working pressure.** Proof-test to 1.5-2× working, hydraulically, behind a barricade, with nobody in the line of fire.

> [!WARNING]
> **Acetone vapor smoothing (§7) - flammable and explosive.**
> - Acetone flash point is **−20 °C (−4 °F)** - it ignites at room temperature. Explosive range in air is **~2.5%-13%**. Vapor is **heavier than air** and pools at floor level.
> - **No open flame, no heat guns, no pilot lights (water heaters/furnaces), no sparking switches/motors within 3 m (10 ft).** Never heat acetone or seal the chamber. Use only cold vapor.
> - Ventilate outdoors or in a fume hood with low-level exhaust. Wear an **organic-vapor respirator** (an N95/dust mask does nothing against acetone), nitrile/neoprene gloves (not latex), and splash goggles. Keep a Class B extinguisher in reach. Acetone waste and soaked towels are hazardous waste - not down the drain, not in the trash.

> [!WARNING]
> **ABS/ASA heat & fumes (annealing §6, printing).** Heated ABS/ASA releases **styrene and acrylonitrile** (styrene is a probable carcinogen). Anneal/print with ventilation or local exhaust. **Never use a food oven** for ABS/ASA - dedicate a cheap toaster/lab oven. Use an electric convection oven, never gas. Monitor continuously; plastic can scorch or ignite.

> [!NOTE]
> **Epoxy / impregnant safety.** Two-part epoxies and solvent sealers: nitrile gloves, ventilation, eye protection per the product SDS. **Dichtol AM Hydro is water-based, VOC-free, and non-hazmat** - the easy case. The old solvent-based Dichtol WFT #1532 is flammable/hazmat - avoid it; use AM Hydro.

---

## 3. Why FDM parts leak (the mechanism)

You can't seal a part well without knowing where the leaks come from. Peer-reviewed work (Tao et al. 2021 void review; Gordeev et al. 2018; Leeder et al. 2025 µCT) identifies the leak paths, ranked by how often they're the culprit:

1. **The Z-seam** - the vertical scar where every layer starts/stops. The #1 leak path. Each layer's seam can stack into a continuous "perforating pore." Fixed by randomizing the seam, scarf seams, brick layers, or vase mode.
2. **Perimeter↔infill and perimeter↔perimeter boundaries** - Prusa identified this as PETG's specific failure mode. The wall itself is fine; the leak runs along the contact line between shells, or between the innermost shell and the solid infill. Fixed by high infill/wall overlap and more perimeters.
3. **Inter-bead / inter-layer voids** - triangular gaps between rounded extruded roads, and gaps between layers from incomplete polymer interdiffusion. Worse with high layer height, low temperature, and high cooling. Fixed by lower layers, hotter nozzle, low fan, slight over-extrusion, brick layers.
4. **Top-layer pinholes** - too few top solid layers, or under-ironed top surface, leaves gaps over the infill. Fixed by 6-7 top layers + ironing.

> [!TIP]
> **The two numbers that matter most.** Across multiple independent studies the leak rate collapses to zero at: **extrusion multiplier / flow ≈ 0.98-1.05** (Gordeev measured k=0.98 → *zero* air leak; k=0.85 → 24 mL/s) and **layer height ≤ 0.1-0.15 mm** for the walls of the pressurized channel (Leeder µCT; Stano air-tight PneuNets). Get those two right before touching anything else.

---

## 4. Design rules (do this in CAD, before slicing)

Leak resistance is designed in, not added later. These rules also make every later step easier.

- **Use cylindrical / curved bodies, not rectangular boxes.** Internal pressure pushes outward in all directions; a cylinder carries it as pure hoop tension, a flat wall bows and cracks. Thin-wall hoop stress: σ = P·D / (2·t). Gordeev's impermeability ranking was cylinder > cube > pyramid > sphere > cone.
- **Wall thickness: ≥ 4-5 extruded lines, and ≥ 1.6 mm minimum; 2-3 mm for a pressure manifold.** Stano's air-tight pneumatic parts needed ≥4-5 adjacent lines *regardless* of absolute thickness; Prusa recommends 2-3 mm walls for pressure. Make the wall an **exact whole-number multiple of the line width** so the slicer fills it with whole beads and leaves no thin gap-fill strip down the middle (gap-fill zones are a classic leak path). Example: 0.6 mm lines → design 3.0 or 3.6 mm walls.
- **Fillet all internal corners.** Sharp corners are crack-initiation stress risers *and* force the nozzle to decelerate, causing an under-extrusion gap (= leak) at the corner.
- **Size the wall from the *interlayer* (Z) strength, not the bulk strength.** PETG bulk tensile ≈ 38-44 MPa, but its layer-adhesion strength is only ≈ 20-29 MPa - design to the weak number. Apply a safety factor ≥ 3-4 on yield for static pressure.
- **Do NOT rely on printed threads - they strip and don't seal.** This is universal expert consensus. Instead use:
  - **Brass heat-set inserts** for fastener bosses (tapered cavity, ≥2 mm wall around/below the insert).
  - **Tapped metal threads** (print a solid boss, then drill + tap).
  - **Press-in push-to-connect pneumatic fittings**, seated in a tapped/inserted boss.
  - **O-ring face/port seals** for the actual gas seal - O-rings are "the best, easiest, most proven" seal (Prusa). Print the gland oversize-solid and machine the groove to standard dimensions, or design to a standard gland. **3D-printed gaskets do not work.**
- **Oversize internal bores to allow for any coating film.** Epoxy adds ~0.05 mm per coat (≈ +0.1-0.2 mm on a diameter over two coats); Dichtol's dry film is ~7 µm (negligible). For any bore under ~6 mm that you intend to coat, prefer a wicking impregnant over a film, and/or oversize the bore.
- **Add a drain/vent port at the low point of each internal channel** so impregnant and slosh-coatings drain fully without pooling and clogging.

---

## 5. Method 1 - Print settings (the foundation)

This is mandatory for every part. Two tuned profiles follow: **PETG** (primary) and **ABS/ASA** (secondary). The settings target the leak mechanisms in §3.

### 5.1 PETG air-tight profile (primary)

| Setting | Value | Why |
|---|---|---|
| Nozzle size | **0.6 mm** preferred (0.4 mm acceptable) | Bigger bead = better squish, fewer seams, more thermal mass per bead |
| Layer height | **0.15 mm** (≤0.20) | Lower = denser, fewer voids. Optimum per CNC Kitchen + Prusa. Use ≤0.1 mm for channel walls if leaks persist |
| Perimeters / walls | **5-6** (≥2.5 mm) | PETG is a poor sealer; needs walls. Material choice stops mattering at ≥6 |
| **Stagger perimeters (brick layers)** | **ON** (§5.4) | Single biggest settings-only gain |
| Wall line width | **0.5-0.6 mm** (widen inner walls) | Wider beads pack tighter; fewer seams |
| Flow / extrusion multiplier | **102-105%** (after baseline flow calibration) | k≈0.98-1.05 → zero leak (Gordeev). Don't exceed ~110% |
| Linear / Pressure Advance | **OFF** for seal-critical | LA drops pressure at seam ends, leaving gaps (Prusa) |
| Infill pattern / density | **Gyroid, 60-100%** (solid in pressure zones) | Isotropic; if walls meet in the middle, infill barely matters |
| Infill/wall overlap | **30-45%** | Kills the #1 PETG leak boundary (perimeter↔infill) |
| Nozzle temp | **245-250 °C** | Peak interlayer strength for PETG (CNC Kitchen: +78% vs 200 °C) |
| Bed temp | **80-90 °C** | |
| Wall order | **Inner → Outer** | Outer wall lays against printed support |
| Print speed (walls/infill) | **25-40 mm/s** | Slow = more dwell, better fusion |
| Cooling fan | **20-30%** (0% first layers) | PETG hates high cooling; it's the #1 cause of porous PETG walls |
| Top / bottom layers | **6 / 6** | Pinhole prevention |
| Seam | **Scarf (outer + inner) or Random** | Never align the seam over a pressure boundary |
| Ironing | **ON** for top + O-ring/sealing faces | Closes top pinholes; smooth face for O-ring contact |

### 5.2 ABS / ASA air-tight profile (secondary)

Same logic; the differences are temperature, cooling, and the **mandatory enclosure**.

| Setting | Value | Why |
|---|---|---|
| **Enclosure** | **Required - hot, draft-free** | Non-negotiable; drafts cause delamination = leaks |
| Nozzle / layer height | 0.6 mm / **0.15 mm** (≤0.20) | As PETG |
| Perimeters / walls | **4-6** | ABS/ASA seal better than PETG (Prusa min = 2 vs 4) |
| **Stagger perimeters (brick layers)** | **ON** | Validated on ASA: **zero mass gain at 4 bar** |
| Flow | **102-105%** | As PETG |
| Linear/Pressure Advance | OFF for seal-critical | |
| Infill / overlap | Gyroid 60-100% / 30-45% | |
| Nozzle temp | **250-260 °C** | Top of range for fusion |
| Bed temp | **95-110 °C** | |
| Cooling fan | **0% (OFF)** | Any cooling → delamination/leaks |
| Top/bottom, seam, ironing | 6/6, scarf or random, ON | As PETG |

### 5.3 Notes on the contested settings (so you can defend the choices)

- **Layer height direction:** many blogs claim *thicker* layers seal better ("fewer lines"). The measured data (CNC Kitchen, Prusa, Leeder µCT) shows the **opposite** - thinner = denser = fewer voids. The blogs are wrong; leaks come from boundaries, not from layer count.
- **Flow:** 102-110% is consensus; the occasional "150% flow" advice is an outlier that causes blobs and dimensional loss - don't.
- **PETG vs ABS as a sealer:** Prusa's *thin-wall* tests actually rank ABS/ASA as the *better* intrinsic sealer (needs only 2 perimeters vs PETG's 4). With ≥6 perimeters the gap disappears, so "PETG first" is fine - it's also the better intrinsic gas *barrier* polymer - but be aware ABS/ASA has the acetone-smoothing escape hatch that PETG lacks.
- **Linear Advance off:** proven helpful for sealing by Prusa's guide; modern well-calibrated PA may be fine, but off is the safe move for seal-critical prints.

### 5.4 Brick layers / staggered perimeters - do not skip this

This is the highest-leverage free setting discovered recently. It staggers each perimeter shell by half a layer height so the walls interlock like masonry, **breaking the continuous horizontal interlayer seam** that runs straight through a normal wall.

- **Measured result:** an ASA hull (3 mm wall) with brick layers took on only 3 ml water at 2 bar (10× less than the best normal hull) and had **zero measurable mass gain at 4 bar (~60 psi)** - matching epoxy-coated parts, with settings alone.
- **How to enable:** **OrcaSlicer → "Stagger Perimeters"** (recent/nightly builds), or the **Geek Detour brick-layers post-processing script** for PrusaSlicer/Orca/Bambu.
- Make this the centerpiece of the print. It directly attacks leak path #1 and #3 from §3.

---

## 6. Method 2 - Annealing (honest verdict: not a sealing step)

> [!WARNING]
> **Annealing does not seal leaks in PETG/ABS/ASA - and can open them.** This is the single biggest "common wisdom is wrong" point in this SOP. If your plan was to anneal PETG to make it airtight, the evidence says that won't work and may hurt. Here's why, and what to do instead.

### 6.1 Why low-temp annealing doesn't seal these materials

- **Layers do not re-fuse below melt.** CNC Kitchen's controlled tests: annealed PLA interlayer test hooks failed at the *same* 42 kg as untreated and "all cracked right between the layers." Annealing relieves stress and (for PLA only) raises crystallinity/heat resistance - it does **not** heal the inter-bead voids that cause leaks.
- **PETG, ABS, and ASA are amorphous.** PETG is glycol-modified specifically so it *doesn't* crystallize. So the PLA crystallinity mechanism is unavailable to them; annealing offers only stress relief.
- **For amorphous PETG, annealing can *degrade* strength** (a material-extrusion study found up to ~22% strength / ~28% modulus loss at 110-150 °C) and **warps the part** (up to ~10% dimensional change; XY shrinks, Z grows, unpredictably). Prusa flatly lists **ABS and ASA as "unsuitable for annealing."** Warping a sealing face or an O-ring groove is a direct way to *create* a leak.
- **No source directly leak-tests annealed vs un-annealed parts and shows a sealing benefit.** Prusa's own watertight/airtight guide never mentions annealing - it relies on walls, O-rings, and epoxy. The airtightness link for annealing is inferred and weak; treat it as unproven.

### 6.2 When to anneal anyway

Only for **heat resistance** (the manifold will run hot) or **dimensional stress relief**. Not as a leak fix. If you anneal, do it **before** any coating step (coating then heating would re-soften and warp the part under the cured film), and **measure a test coupon per-axis** to compensate for shrink.

### 6.3 Conservative anneal recipes (if you must)

| Material | Tg | Conservative anneal | Notes |
|---|---|---|---|
| PETG | ~80 °C | **65-70 °C, 30-60 min**, cool inside the oven | Just below Tg; minimizes warp. **Avoid 70-90 °C free-standing** - documented degradation |
| ABS | ~105 °C | ~100-105 °C if attempted, encased | Prusa: "unsuitable" - warps, ~no gain. Prefer vapor smoothing instead |
| ASA | ~100 °C | ~85-95 °C if attempted, encased | As ABS |

Process notes: electric **convection** oven only; independent oven thermometer (built-in thermostats swing ±10-20 °C, enough to melt near Tg); 100% infill before heat; place in preheated oven and **cool to room temp inside, door shut** (thermal shock cracks/warps). Expect 1-3% shrink on PETG.

### 6.4 The one heat process that DOES fuse layers: encased re-melt near Tm

If you genuinely need maximum interlayer fusion (not just airtightness), the only heat process shown to heal layer boundaries is **re-melting the part near its melt temperature while fully encased in support medium**:

- **Plaster of Paris encasement:** PETG embedded in dried plaster, ~200 °C, ~3 h → interlayer strength roughly **tripled**, tensile 30 → 41 MPa, **no warping**. Plaster crumbles off afterward. Labor-intensive (~36 h plaster drying).
- **Fine powdered-salt encasement:** compacted *fine* salt (not coarse kosher/table salt, which won't compact) supports the part for near-melt re-fusion; dimensional change <1%; fractures come out "perfectly homogenic" with no visible layer lines.

This is overkill for most manifolds and changes dimensions enough to require validation, but it's the honest answer to "can I actually weld the layers together with heat" - yes, but only by re-melting under support, not by annealing.

---

## 7. Method 3 - Acetone vapor smoothing (ABS / ASA only)

A sound second choice for ABS/ASA. **Not applicable to PETG** (PETG is not acetone-soluble; the solvents that work on it - MEK, ethyl acetate, DCM - are far more hazardous, and PETG is normally not vapor-smoothed at all).

### 7.1 What it does and doesn't do

Acetone vapor condenses on the surface, dissolves the outermost polymer, surface tension pulls it into the layer valleys, and it re-solidifies into a continuous glossy skin. **It seals surface and near-surface porosity (~0.1-0.3 mm deep) - it does not re-flow a 2 mm wall through-thickness.** So:

- If the wall is already near-solid (good settings, ≥2 mm, no through-wall under-extrusion), vapor smoothing caps the surface porosity and the part commonly passes a leak test. Industrial systems (AMT, Protolabs) guarantee airtight/leak-proof results this way, including sealed internal cavities.
- If the wall leaks through its full thickness, vapor smoothing will *not* reliably save it.
- **Verdict: a real near-surface sealer and a good second choice for ABS/ASA - but leak-test every unit, and mind the bore-clogging risk below.**

### 7.2 Cold-vapor recipe (use cold only - never heat acetone)

| Parameter | Recommendation |
|---|---|
| Method | **Cold vapor only.** Heated vapor is faster but pushes vapor toward the explosive range fast - don't |
| Acetone | 99%+ pure, **10-50 mL on paper towels lining the chamber walls** (not pooled on the floor) |
| Container | Glass jar or PP/metal tub, several× the part size; **lid resting loose with a vent gap** (never sealed) |
| Part support | **Suspend from the lid by a wire hook** (best - even top/bottom), or raise ≥10 mm on an inert platform. Never touches liquid/towels |
| Temperature | Room temp (20-25 °C) |
| Time | Small ≤50 mm: **10-20 min** · Medium 50-150 mm: **20-45 min** · Large: 45-120 min |
| Monitoring | Visual check every 2-5 min; **pull at uniform gloss, before edges/bores blur** |
| Cure before use | Handle at 2-4 h; **leak-test at ≥24 h (ideally 48-72 h)** - residual acetone leaves the skin soft and gives a false seal reading |

**ASA differences:** more acetone-resistant - expect a longer dwell and a subtler (less mirror) gloss; dial in per spool. ASA is the better pick if the manifold sees sun/UV.

### 7.3 The manifold-specific caveat: small bores

Softened plastic flows inward and can **round, shrink, or clog small internal bores**, and you can't see inside to stop it. Mitigations: design walls ≥2 mm; **mask/plug critical bores and O-ring faces** before smoothing; oversize small passages; **verify bores with a pin gauge or flow test after** smoothing. Sub-1 mm internal passages are the danger zone. Note also that over-exposure *reduces* strength (immersion can drop UTS up to ~45%); brief, controlled cold vapor is roughly neutral and improves Z-bonding.

### 7.4 Scalability

Active labor is low (~10-20 min/part incl. handling and inspection) but wall-clock is long (15-60 min vapor + 24 h+ cure) and DIY cold vapor needs babysitting. You can batch multiple suspended parts per chamber. If volume grows, automated systems (AMT PostPro, Zortrax Apoller, DyeMansion) run sealed timed cycles with near-zero marginal labor per part - the recommended upgrade path.

---

## 8. Method 4 - Coatings, sealants & impregnation (the reliable finisher)

For a manifold with internal channels, a **penetrating/wicking impregnant beats a film coating**, because it reaches internal bores and adds almost no dimensional thickness. A surface film (epoxy/spray) **cannot seal internal channels** - this is the documented failure mode shared by every brush/dip/spray coating.

### 8.1 Primary recommendation: DIAMANT Dichtol AM Hydro

> [!NOTE]
> **The "Germany won't ship it" problem is solved.** The current product, **DIAMANT dichtol AM Hydro**, is water-based, solvent-free, VOC-free, non-hazmat, and is sold on **Amazon US**; there is a US entity (DIAMANT Polymers Inc, Cincinnati OH). Avoid the older solvent-based Dichtol WFT #1532 (that's the flammable/hazmat one that's hard to ship).

- **What:** a water-thin (3-6 mPa·s), capillary-active polymer that wicks into pores and polymerizes inside the layer gaps. Seals pore range **0-0.2 mm**, dry film ~7 µm (won't clog bores), temperature resistance to **130 °C**, 5-yr shelf life. Proven on PLA, ABS, ASA, PA. Real-world: CPSdrone's fully waterproof underwater drone used AM Hydro.
- **Application - including internal channels:**
  - *Inject:* fill the channel, 5-min dwell, pour out excess. **This is the manifold internal-channel method.**
  - *Dip:* submerge ~10 min, drain fully.
  - *Brush:* 4× at 1-min intervals, keep wet ≥5 min (external).
- **Cost:** ~$75-80/L (~$30/250 mL). Low per-part cost; the bath is reusable.
- **Limitations:** seals pores ≤0.2 mm only - it relies on decent print settings first (it finishes a good print, it doesn't rescue a bad one). Vendor doesn't publish a pressure rating; proven fine for typical pneumatic line pressures when walls are sound. **Not food/potable-water rated.**

> [!IMPORTANT]
> **It's a penetrant, not a film - this is why it won't clog manifold channels.** Dichtol's dry film is **~7 µm**. On a 4-6 mm gas channel that is negligible - it wicks *into* the wall and seals the pores rather than building a coating on the bore. So you can **submerge the whole manifold and drain it** and the internal cavities stay clear and full-bore. The "submersion will seal my channels shut" worry applies to *film* coatings (epoxy, CA) and to vapor smoothing, **not** to a penetrant. No bore-oversizing needed for Dichtol.

#### Working time, dwell, and cure (read before first use)

- **No pot-life clock.** It's a one-part, water-based fluid - it does **not** gel in the container like a two-part epoxy. In the bath it stays liquid essentially indefinitely (sealed shelf life ~5 yr) and the **bath is reusable** (strain and recap). Take your time; there's no penalty for a slow process.
- **Dwell / how long submerged:** dip ~**10 min**; inject/flood a channel ~**5 min** then pour out. Longer doesn't hurt - dwell only gives capillary action time to draw fluid into the pores; it is not a timer you must beat. Under vacuum-assist, hold until pore-bubbling stops, release, then sit a few minutes.
- **It cures by air/evaporation - it needs to be OUT of the bath, drained, and exposed to air.** The water carrier must leave for the polymer to set, so it does **not** harden while submerged or inside a sealed pool (that's exactly why the bath stays reusable). In the pores it cures fine because the films are micron-thin and the carrier wicks/evaporates out.
- **Why draining matters (cure, not clog):** pooled residue in a blind cavity cures slowly and badly because the water can't escape, leaving a damp uncured spot. **Drain thoroughly, rotate, and blow channels clear** so the part actually cures - the thin film won't clog, but trapped liquid won't set.
- **Cure schedule (after removing + draining):** surface dry ~**60 min**; full cure ~**24 h** at ~20 °C / ~65 % RH; rough rule **~1 h per mm of penetration depth**. Apply below ~40 °C surface temp.
- **Do NOT cure under vacuum.** Vacuum boils the water carrier off violently (foam-over). Vacuum is only the penetration stroke (§8.2); cure happens in open air afterward.

### 8.2 Vacuum impregnation (best for thicker walls / higher pressure)

The industrial gold standard, doable at home with a vacuum chamber. **Recommended primary finisher for a manifold** when the bare print doesn't pass.

**Why it beats a plain dip:** an FDM part is ~98-99% dense; the missing 1-2% is the interconnected micro-void network that *is* the leak path. A surface dip can't fill it because the **trapped air inside the pores blocks the sealant**. Vacuum works in two strokes:
1. **Vacuum** evacuates the air trapped inside the pores.
2. **Release** the vacuum, and atmospheric pressure (14.7 psi on the now-empty pores) drives thin sealant deep inside. It cures locked in the porosity, adding **zero external dimension** - ideal for precision manifolds.

**Wet method (submerge-then-vacuum) - use this.** The part stays submerged throughout; vacuum pulls air out through the liquid (you'll see it bubble out of the part), release drives sealant straight into the vacated pores. Best penetration. (The dry "vacuum-then-dunk" variant is weaker - skip it if you can submerge.)

#### Sealant choice for vacuum impregnation

| Sealant | Vacuum behavior | Notes |
|---|---|---|
| **Dichtol AM Hydro** | water-based → **foams/outgasses hard** under deep vacuum | Best penetration + non-hazmat + won't clog bores (penetrant). Pull vacuum **in stages** or it boils over. Air-cures (§8.1). **Default choice.** |
| Thin epoxy (low-viscosity, **45+ min pot life**) | degasses cleanly, low vapor pressure | For higher-pressure / thicker walls. **Builds a film → clog risk in small bores;** drain + rotate, oversize bores. Total chamber time must stay under pot life or it gels in the bath. |
| Methacrylate (Loctite Resinol RTC) | the industrial impregnation resin | Only if NSF-61 / potable-water rating needed; needs ~90 °C hot-water cure. |

#### Procedure (with a vacuum chamber)

1. **Prep.** Part fully dry. Usually leave channels open to flood (full submersion is the point).
2. **Submerge** the part in a container of sealant inside the chamber. **Weight it down** - thin fluid floats light parts. Keep the bath shallow in a deep container to leave headroom for foam.
3. **Pull vacuum** to ~28-29 inHg (a few torr). **With water-based Dichtol, ramp the vacuum in stages** - it foams hard as pore water boils off; throttle so it doesn't overflow. Epoxy is calmer.
4. **Hold** until bubbling from the part nearly stops - typically **5-15 min**. That bubbling *is* the trapped pore-air leaving.
5. **Release vacuum slowly** - this is the impregnation stroke (atmosphere drives sealant into the vacated pores). Let it sit submerged ~**5-15 min** to fully wick in.
6. *(Optional pressure stroke)* if you can also positively pressurize (paint-pot at 30-60 psi), pushing pressure after the vacuum forces sealant deeper - a big jump for higher-pressure parts.
7. **Remove, drain, wipe.** Drain channels fully, rotate, and **blow low-pressure air through each passage** so nothing pools and so the part can cure (§8.1 - pooled penetrant won't set).
8. **Cure in open air** (NOT under vacuum). Dichtol per §8.1; epoxy per its schedule.
9. **Leak test** Tier 1 → Tier 2 (§11).

> [!WARNING]
> **First-try failure: foam-over.** Water-based Dichtol erupts under fast/deep vacuum. Use a deep container, a small charge, and a staged pull. Keep the chamber floor clean. Don't over-pull solvent/CA sealants either (you can boil off their own volatiles); epoxy is safe (low vapor pressure).

To scale or outsource, **Godfrey & Wing** (Cleveland OH) offers vacuum-impregnation as a paid service.

### 8.2a Sealing internal channels without clogging - penetrant vs. slush

Two clean strategies for a manifold whose internal cavities must stay full-bore:

- **Penetrant route (recommended - Dichtol).** Because the dry film is ~7 µm, **submerge or inject + dwell + drain** leaves bores clear automatically. No bore-oversizing, no selective coating. Seals the channel walls, the wall through-thickness, and the exterior in one shot. Vacuum-assist for depth (§8.2). This sidesteps the clogging problem entirely and is the right call for a compressed-air manifold.
- **Slush / rotational-casting route (only if a *film barrier* is needed inside - e.g. for an aggressive medium epoxy must resist).** This is the slip-mold technique: oversize internal bores ~0.2 mm in CAD → pour a small charge of thin, long-pot-life epoxy in → cap ports and **rotate/tumble to wet all internal walls** → **dump the excess back before it gels** → **keep rotating through the whole gel window** so it can't sag or pool at a low point → **blow low-pressure air through each channel while wet** to clear any film bridging a small bore and even the coat. Thin coats, repeat rather than one thick pass.

> [!TIP]
> **For a compressed-air manifold, prefer the penetrant route.** An interior epoxy film can clog a passage, and a flake that later breaks loose travels downstream into your pneumatics - a real failure mode. A penetrant-impregnated wall (good print + brick layers + Dichtol) seals shop air without any of that risk. Reserve the slush/film method for genuinely aggressive media the bare plastic can't resist.

### 8.3 Epoxy coatings (external skin and flanges only - NOT internal bores)

| Product | Use | Pressure / temp | Notes |
|---|---|---|---|
| **Loctite Hysol E-20HP** | Brush, external | **Airtight to 65 psi**, ≥ FDM temp | Best-documented pressure number for brush epoxy on FDM; "internal channels cannot be sealed" |
| **XTC-3D (Smooth-On)** | Brush/dip, external skin + finish | < ~93 °C | Self-levels; **clogs small bores if dipped** - oversize bores |
| **West System** | Marine encapsulation | Excellent moisture barrier | Slow, thick, more man-hours |

**Forum-validated thin-coat technique** (for flanges/exterior): sand 80-100 grit, wipe with acetone, brush **two thin coats** (~0.05 mm each, 6-12 h apart) of ~45-min-pot-life epoxy → held 8 bar external water for 5 days, zero leak. Keep epoxy off threads and precision features.

**Internal-channel slosh method (only if epoxy must touch a bore):** pour a small charge of thin epoxy in, **rotate continuously** to coat all walls, **drain fully before it gels**, and keep tumbling until tack-free so nothing pools in the bore. Prefer a wicking impregnant (§8.1) over this whenever possible.

### 8.4 What NOT to rely on

**Plasti Dip, Flex Seal, rubberized sprays, conformal sprays** - documented to leak through print lines under pressure; fine for splash/weatherproofing, not for a pressurized manifold. **Sodium silicate / water glass** and **thin CA glue** - CA wicks and is fine for small-part touch-ups but is brittle and degrades with moisture; water glass is for castings, not flexible plastic pressure parts. **Smith's CPES** penetrating epoxy is wood-validated and solventy - fallback only.

> [!NOTE]
> **If food/potable-water contact is ever required:** only **Loctite Resinol RTC** (a methacrylate vacuum-impregnation resin) among these is **NSF/ANSI 61 certified** for potable water. XTC-3D and Dichtol are not food-rated - do not claim food-safe.

---

## 9. Method comparison - effort vs. result

| Method | Active man-hrs/part | Wall-clock | Reaches internal bores? | Seals to roughly | Best for |
|---|---|---|---|---|---|
| Print settings + brick layers | 0 (just slicing) | print time | n/a (it's the wall) | ~2-4 bar / 30-60 psi | **Everything - the foundation** |
| Annealing | low + measuring | hours | n/a | **does not seal** | heat resistance only |
| Acetone vapor (ABS/ASA) | ~10-20 min | 15-60 min + 24 h cure | yes (surface of cavities) | near-surface seal | ABS/ASA second pass |
| **Dichtol AM Hydro** | **~5-10 min** (dip/inject + drain) | 60 min dry + 24 h cure | **yes (inject/dip)** | pores ≤0.2 mm; field-proven gas-tight | **low-effort finisher, manifolds** |
| DIY vacuum impregnation | ~20-30 min | + cure | yes | deep pore fill | thick walls / higher pressure |
| Brush epoxy (Hysol/XTC) | ~15-30 min | + cure | **no (external only)** | 65 psi external | flanges, external skin |

**Lowest-man-hour reliable recipe for a gas manifold: optimized PETG print + brick layers → leak test → Dichtol AM Hydro dip/inject if needed.** That's one tuned profile plus one ~10-minute dip, and it's the path the evidence most supports.

---

## 10. End-to-end procedures

### 10.1 Recommended path - PETG (primary)

1. **Design** per §4 (cylindrical body, ≥2.5 mm walls as a whole multiple of line width, filleted corners, metal/insert/O-ring ports, oversized bores, drain port).
2. **Slice** with the §5.1 PETG profile. **Enable brick layers (§5.4).**
3. **Print.** Inspect for visible defects, blobs, gaps at the seam.
4. **Leak test - Tier 1 bubble** (§11). If it passes at working pressure, you may be done.
5. **If it leaks - seal with Dichtol AM Hydro** (penetrant; ~7 µm film won't clog channels):
   - *Simple:* inject/dip → **5-10 min dwell** (no pot-life clock - longer is fine) → **remove, drain, blow channels clear**.
   - *Vacuum-assist (you have a chamber - preferred for depth, §8.2):* submerge → pull vacuum **in stages** (Dichtol foams hard) → hold until pore-bubbling stops (5-15 min) → **release slowly**, soak 5-15 min → remove, drain, blow clear.
   - **Cure in open air, NOT under vacuum:** surface dry ~60 min, full cure ~24 h (~1 h/mm). Drain well - trapped liquid won't set.
6. **Re-test - Tier 2 pressure decay** at working pressure (§11.2).
7. **(Only if it runs hot)** anneal for heat resistance *before* coating, not after - but note this reorders steps 5-7; anneal between 3 and 5, then measure (§6).
8. **First article only:** Tier 3 hydraulic proof test (§11.3). Log everything in §12.

### 10.2 Alternate path - ABS/ASA (when acetone smoothing is wanted, or for UV/heat)

1. Design per §4.
2. Slice with the §5.2 ABS/ASA profile, **brick layers ON**, enclosure required.
3. Print.
4. Tier 1 bubble test.
5. If it leaks: **acetone vapor smooth** (§7) - mask bores/O-ring faces first - *or* go straight to Dichtol AM Hydro (more reliable for through-leaks and internal channels).
6. Cure ≥24 h, verify bores, Tier 2 pressure decay.
7. First article: Tier 3 hydraulic proof. Log in §12.

---

## 11. Leak testing & verification

Three tiers, cheap → rigorous. Run Tier 1 on every part, Tier 2 to qualify, Tier 3 once per design (first article) - hydraulically.

### 11.1 Tier 1 - Bubble screen (every part, ~5 min, LOW pressure)
Cap all ports but one, apply **10-15 psi air** (≤30 psi max), submerge in water, watch 30-60 s. Bubble streams pinpoint the leak location. Cross-check fittings/threads by spraying **soapy water** at working pressure. **PASS:** no continuous bubble stream. Keep it low-pressure - you're holding a pressurized part by hand near your face.

### 11.2 Tier 2 - Pressure decay (qualification, ~20 min)
1. **Master-plug baseline first:** cap the manifold with known-good blanks at every port, decay-test the rig - any drop is in fittings/rig, not the part. Subtract this.
2. Pressurize to **working pressure**, **stabilize 60-120 s** (let adiabatic heating settle - skipping this gives false leaks), isolate, log gauge/transducer for **10 min**.
3. Convert to a volume-independent leak rate: **Leak rate (SCCM) = (Δp/Δt) × (V/14.7)**, with Δp in psi, Δt in min, V in cm³.
4. **PASS (small <100 cm³ manifold):** ≤ 1 psi drop / 10 min, or ≤ 1 SCCM (tighten to ≤0.1 SCCM for critical use). Test in a temperature-stable area - a 1 °C swing can masquerade as a leak.

*Optional:* **vacuum decay** (seal, pull vacuum, watch for pressure rise) is ~10× more sensitive and less temperature-sensitive, but only validates tightness, not strength.

### 11.3 Tier 3 - Proof test, HYDRAULIC (first article / design validation only)

> [!WARNING]
> **Hydraulic only - never pneumatic at these pressures.** Fill the part **completely with water and bleed ALL air** (trapped air = stored energy). Pressurize with a hand hydro-test pump or a water-fed pressure-washer pump + transducer. **Barricade the part, pressurize remotely / from behind cover, fit an inline relief valve set ≤105% of test pressure, and never stand in line with it.** Ramp in steps (e.g. 50%, then +10%) with holds.
> **PASS:** hold **1.5-2× working pressure for 10-15 min** with no weeping and no permanent deformation. Burst-test a sacrificial unit to confirm **burst ≥ 4× working**.

### 11.4 Isolating where a leak is
Master-plug baseline (rig vs part) → soap each port at working pressure (fitting vs body) → submerge pressurized (seam vs port boss) → plug all galleries but one and test each individually. Body leaks track a layer line or seam (fix: more walls/flow, brick layers, impregnate); port leaks track threads/O-ring face (fix: thread sealant/O-ring, iron the sealing face).

---

## 12. Results Library

Log every build here. The point is to converge on the minimum process that passes for each material/pressure combination, with real data.

### Master table

| Date | Part | Material | Nozzle/layer | Walls | Brick layers | Flow | Finish step(s) | Test tier & pressure | Result | Notes |
|---|---|---|---|---|---|---|---|---|---|---|
| _(none yet)_ | | | | | | | | | | |

### Per-build template (copy for each build)

```
#### [Part name] - [date]
- Material / brand:
- Profile: nozzle __ mm, layer __ mm, walls __, brick layers Y/N, flow __%, nozzle __°C, bed __°C, fan __%
- Seam / overlap / ironing:
- Finish: (none / Dichtol AM Hydro dip __ min / vacuum impreg / acetone vapor __ min / epoxy __ coats / anneal __°C __min)
- Working pressure target: __ psi
- Tier 1 bubble: pass/fail @ __ psi - leak location:
- Tier 2 decay: __ psi drop / __ min  → __ SCCM  → pass/fail
- Tier 3 hydraulic proof (first article): held __× working for __ min - pass/fail; burst (sacrificial): __ psi
- Verdict / what to change next time:
```

---

## 13. References

**Print settings & geometry**
- Prusa - Watertight 3D printing [Part 1](https://blog.prusa3d.com/watertight-3d-printing-pt1-vases-cups-and-other-open-models_48949/) (material ranking) · [Part 2](https://blog.prusa3d.com/watertight-3d-printing-part-2_53638/) (closed/pressure models)
- Prusa forum - [high-pressure watertight test (5-8 bar, exact settings)](https://forum.prusa3d.com/forum/english-forum-general-discussion-announcements-and-releases/watertight-prints-for-high-pressure-environments/) · [2-perimeter / Linear-Advance-off guide](https://forum.prusa3d.com/forum/original-prusa-i3-mk3s-mk3-general-discussion-announcements-and-releases/guide-how-to-get-water-and-airtight-prints-on-the-first-try-with-just-2-perimeters-and-the-default-0-4mm-nozzle/)
- CNC Kitchen - [extrusion temp vs layer adhesion](https://www.cnckitchen.com/blog/the-influence-of-extrusion-temperature-on-layer-adhesion) · [layer height vs strength](https://www.cnckitchen.com/blog/the-influence-of-layer-height-on-the-strength-of-fdm-3d-prints) · [brick layers](https://www.cnckitchen.com/blog/brick-layers-make-3d-prints-stronger)
- Brick layers - [Hackaday.io waterproof project (4-bar / zero-mass-gain data)](https://hackaday.io/project/204613-brick-layers-making-3d-prints-super-waterproof/details) · [Hackaday: brick layers for everyone](https://hackaday.com/2025/03/17/3d-printed-brick-layers-for-everyone/) · [scarf seams](https://hackaday.com/2024/03/11/reducing-seams-in-fdm-prints-with-scarf-joint-seams/)
- Threads/inserts - [CNC Kitchen heat-set inserts](https://www.cnckitchen.com/blog/threaded-inserts-for-3d-prints-cheap-vs-expensive) · [Protolabs threading & inserts](https://www.protolabs.com/resources/blog/threading-and-inserts-for-3d-printing/)

**Academic - voids, bonding, leak paths**
- Tao et al. 2021, *A review on voids of 3D printed parts by FFF*, J. Mater. Res. Technol. 15:4860-4879, [DOI 10.1016/j.jmrt.2021.10.108](https://www.sciencedirect.com/science/article/pii/S2238785421012448)
- Gordeev, Galushko, Ananikov 2018, *Elimination of microscopic structural defects in FDM* (flow k=0.98 → zero leak), PLOS ONE 13(6):e0198370, [DOI 10.1371/journal.pone.0198370](https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0198370)
- Leeder, Rankin, Nightingale 2025, *µCT imaging of leak pathways for leak-free 3D-printed fluidics*, ACS Appl. Polym. Mater. 7(21):14130-14137, [PMC](https://pmc.ncbi.nlm.nih.gov/articles/PMC12624528/)
- Stano, Arleo, Percoco 2020, *Airtight monolithic PneuNets* (≥1.6 mm wall, 0-7 bar test), Micromachines 11(5):485, [PMC](https://pmc.ncbi.nlm.nih.gov/articles/PMC7281577/)
- Aliheidari et al. 2017, *Fracture resistance of FDM polymers* (temp → bond), Polymer Testing, [DOI 10.1016/j.polymertesting.2017.01.016](https://www.sciencedirect.com/science/article/abs/pii/S0142941817300065)

**Annealing**
- CNC Kitchen - [annealing PLA Pt.1 (no layer-adhesion gain)](https://www.cnckitchen.com/blog/better-performing-3d-prints-with-annealing-but-part-1-pla) · [plaster re-melt (3× strength)](https://www.cnckitchen.com/blog/r85hx5mwi0vxk0gwdb7ko4rfj1g5y2) · [salt re-melt](https://www.cnckitchen.com/blog/testing-the-strength-of-3d-prints-re-melted-in-salt)
- [Prusa - annealing guide (ABS/ASA "unsuitable")](https://blog.prusa3d.com/how-to-improve-your-3d-prints-with-annealing_31088/) · [Polymaker annealing wiki](https://wiki.polymaker.com/printing-tips/post-processing/annealing) · [Sovol annealing PLA/PETG](https://www.sovol3d.com/blogs/news/annealing-3d-printing-pla-petg)

**Vapor smoothing**
- [Smith3D full recipe + safety](https://www.smith3d.com/complete-guide-to-3d-print-smoothing-acetone-vapor-bath-safety-techniques/) · [Clever Creations cold-vapor method](https://clevercreations.org/smoothing-abs-acetone-vapor-bath-brush/) · [Xometry mechanism/limits](https://www.xometry.com/resources/3d-printing/acetone-vapor-smoothing/) · [EngineerDog strength/penetration](https://engineerdog.com/2015/05/04/effect-of-acetone-vapor-polishing-on-3d-printed-abs-parts/)
- Industrial: [AMT PostPro (airtight sealing claims)](https://amtechnologies.com/products/vapor-smoothing/) · [Protolabs vapor smoothing (manifolds)](https://www.protolabs.com/services/3d-printing/vapor-smoothing/)
- Safety: [NIOSH acetone pocket guide](https://www.cdc.gov/niosh/npg/npgd0004.html) · [Fire Engineering - acetone LEL/vapor density](https://www.fireengineering.com/firefighting/acetone/)

**Coatings & impregnation**
- Dichtol AM Hydro - [TDS #2589](https://3d.nice-cdn.com/upload/file/2589_diamant-technical-data-sheet-dichtol-am-hydro.pdf) · [3djake spec/price](https://www.3djake.com/diamant-polymer/dichtol-am-hydro) · [Amazon US](https://www.amazon.com/DIAMANT-Polymer-impregnating-Manufacturing-Solvent-Free/dp/B0DWFYCQJG) · [3dprint.com writeup](https://3dprint.com/314277/gas-and-watertight-3d-prints-with-diamant-sealant/)
- Vacuum impregnation - [Godfrey & Wing guide](https://www.godfreywing.com/blog/the-ultimate-guide-to-sealing-3d-printed-parts/) · [DIY degassing/vacuum](https://hackaday.com/2019/12/19/degassing-epoxy-resin-on-the-very-cheap/)
- Epoxy on FDM (65 psi, internal-channel limit) - [Prototyping Solutions](https://prototypingsolutions.com/sealing-fdm-parts/) · [XTC-3D TDS](https://www.smooth-on.com/products/xtc-3d/)
- Resinol RTC (NSF-61) - [Henkel](https://www.henkel-adhesives.com/vn/en/product/industrial-sealants/loctite_is_resinolrtc0.html)
- CPSdrone underwater drone (Dichtol) - [DIAMANT writeup](https://diamant-polymer.de/en/news/publications/youtuber-cpsdrone-praesentieren-eine-vollstaendig-wasserdichte-3d-gedruckte-unterwasserdrohne-mit-dichtol-am-hydro/) · German Engineer gas-tight - [Hackaday](https://hackaday.com/2024/06/08/gas-tight-fdm-3d-printing-is-within-your-grasp/)

**Leak testing & pressure safety**
- [EIGA pressure-test guideline (stored-energy / TNT equivalence)](https://www.eiga.eu/uploads/documents/DOC254.pdf) · [TotalShield pneumatic-test safety](https://totalshield.com/blog/the-pneumatic-pressure-testing-handbook-part-3-pneumatic-testing-safety/) · [Titan: hydrostatic vs pneumatic](https://titanresearch.ca/hydrostatic-pressure-test-vs-pneumatic-pressure-testing/)
- [Cincinnati Test - decay phases/criteria](https://www.cincinnati-test.com/blog/leak-rate-required-pressure-decay-testing) · [Zaxis leak-rate formula](https://zaxisinc.com/resources/what-is-a-leak-test/leak-rate-calculator/) · [Vac-Eng vacuum vs pressure decay](https://vac-eng.com/vacuum-decay-vs-pressure-decay-testing/) · [PV Eng burst/proof factors](https://www.pveng.com/general-burst-test-requirements/)
- Hobbyist pressure-test videos: [Space Cowboy "Water Tight High Pressure Fuel Tank"](https://www.youtube.com/watch?v=-fBXHXKO8M0) · [pressure vessel to failure](https://www.youtube.com/watch?v=Fk9oaCQPRMg)

> [!NOTE]
> **Source caveats (for the open-source version)**
> - **Annealing-for-airtightness is unproven** - no source directly leak-tests annealed vs un-annealed parts and shows benefit; the SOP treats it as a heat-resistance step, not a seal.
> - **FDM-specific gas-permeability coefficients are scarce.** For a *pressurized* manifold, leakage is dominated by mechanical voids (Gordeev/Leeder/Stano), not molecular diffusion - the PETG > ABS > PLA *barrier* ranking is from bulk-polymer science, stated as such.
> - A couple of secondary blog/journal figures (paywalled abstracts) are indicative, not definitive - verify before quoting exact percentages in a public release.
