# Embedded-Braid Construction - How Festo Co-Forms Tube and Braid

How to build a pneumatic muscle where the braid/fiber reinforcement is **bonded into the tube wall** instead of sliding loose over the outside of it. This is the construction Festo uses for the Fluidic Muscle (MAS / DMSP), and it is the "endpoint" flagged in [`../design.md`](../docs/design.md): *tube and braid co-formed as a single part for high durability.*

This document is the manufacturing-method companion to [`PAM Design Variables.md`](PAM%20Design%20Variables.md), which catalogs the physics. Here the question is narrower: **how do you physically get the braid into the wall, and what does that buy you?**

---

## 1. Two architectures, one mechanism

Every braided PAM uses the same mechanism - a helical fiber lattice converts radial bladder expansion into axial contraction (the `3cos²θ − 1` term; see [`PAM Design Variables.md` §1.2](PAM%20Design%20Variables.md)). What differs is **how the fiber lattice is attached to the pressure membrane.**

| | **Separate-sleeve McKibben** (classic / current AeroFlex) | **Embedded-braid fluidic muscle** (Festo MAS/DMSP) |
|---|---|---|
| **Bladder** | Elastomer tube (latex, silicone) | Elastomer membrane (chloroprene/rubber) |
| **Fiber lattice** | Braided sleeve slid **over** the tube, free to slide | Fiber grid **vulcanized into** the membrane wall |
| **Fiber-fiber contact** | Yes - fibers cross and rub at every pick | Festo's later design **separates** fibers with elastomer so they never touch |
| **Fiber-bladder sliding** | Yes - sleeve slides against tube surface | None - fibers are encapsulated, move *with* the rubber |
| **Sealing + reinforcement** | Two separate jobs (tube seals, sleeve reinforces) | One part does both |
| **Ends** | Clamp/crimp both layers onto a fitting | Pressed/clamped head pieces grip the integrated wall |
| **Hysteresis** | High - dominated by fiber-on-fiber + bladder-braid friction (~20-30% loss; [§1.8, §2.5](PAM%20Design%20Variables.md)) | Low - the dominant friction sources are designed out |
| **Life** | Sleeve abrades the bladder over cycles | No relative sliding → far longer fatigue life |
| **Repairability / modularity** | High - cut to length from a spool, crimp on site | Low - finished length is fixed at manufacture |
| **Manufacturing** | Trivial (commodity parts, hand assembly) | Hard (molding/vulcanizing tooling, cured per part) |

The trade is blunt: **embedding eliminates the two biggest loss/wear mechanisms in a McKibben muscle, at the cost of making the muscle a molded part instead of an assembly.**

---

## 2. The taxonomy: braided / pleated / netted / embedded

Trojanová, Hosovský & Čakurda (2023) classify braided-type PAMs into four construction subgroups ([`Research Papers/Evaluation of Machine Learning-Based Parsimonious Models for Static Modeling of Fluidic Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Evaluation%20of%20Machine%20Learning-Based%20Parsimonious%20Models%20for%20Static%20Modeling%20of%20Fluidic%20Muscles.pdf), *Mathematics* 11(1):149):

- **Braided** - separate woven sleeve over a bladder (classic McKibben, 1953).
- **Pleated** - membrane folded into axial pleats that unfold; no fiber friction at all (Daerden/Lefeber).
- **Netted** - open net over a balloon (the "vegetable-net + balloon + cable-tie" demo).
- **Embedded** - fibers cast/vulcanized *into* the membrane wall. The paper notes these are "the result of design, especially in recent years," built from **silicone rubber, polyethylene tubes, or silicon substrates containing embedded Kevlar fibers.**

The paper also credits the original fluid-driven muscle to **Garasiev (1930s)**, who is described as having invented "braided/netted **or embedded** membranes" - so embedding is not new in principle; it is just harder to make. Festo's "Actuating means / fluidic muscle" (Bergemann, Lorenz, Thallemer, 1999) is listed as the canonical embedded commercial product.

A Festo fluidic muscle is summarized in that paper as: *"a tensile action element formed by a rubber tube and an insert made of aramid fibers, hermetically sealed."* The **insert is inside the wall**, not a sleeve on top.

---

## 3. How Festo actually does it (the patents)

### 3.1 US 6,349,746 B1 - "Actuating means" (Festo; Bergemann, Lorenz, Thallemer)

Priority 1999, expired 2020. **This is the core embedded-construction reference.** Local note: this patent is item *"Actuating means, fluidic muscle, 1999"* in the taxonomy table above.

**Structure** - three integrated parts, all sharing one material:

1. **Hose body (5)** - rubber-elastic/vulcanized elastomer. Does two jobs at once: seals the pressurized interior **and** acts as the embedding matrix for the fibers.
2. **Strand structure (6)** - two coaxial groups of textile strands (18, 19) running in **opposite helical directions.** Key nuance: within each group the strands run parallel and **do not cross over each other** - they are *not plaited/braided*. The two groups form the crossover lattice by being layered, not woven.
3. **Spacing material (22)** - *the elastomer itself*, between the two strand groups, holding them a constant distance apart so they never contact or rub.

**The integration method (this is the "how"):**

> "vulcanizing several layers of such material together using intermediate layers of such material between the individual strand groups."

So the wall is a **vulcanized lay-up**, cross-section (FIG. 3) from inside out:

```
interior pressure
│
├─ inner elastomer layer  ← contains inner strand group (18), helix direction A
├─ elastomer spacing layer
├─ outer elastomer layer  ← contains outer strand group (19), helix direction B
└─ outer elastomer protective coating
```

Each strand is **completely surrounded by hose material** ("preferably completely surrounded"), so:
- no fiber-on-fiber friction (groups separated by rubber),
- no fiber-on-bladder sliding (fibers bonded into the rubber, strain with it),
- the elastomer distributes tensile load along each fiber and resists the fibers cutting through the wall.

This is *why* the design explicitly rejects the plaited/braided sleeve: plaiting is what creates the friction and wear. The patent's stated innovation is the **wave-free, fully-stretched, non-crossing coaxial fiber layers separated by elastomer.**

**End fittings** - two-part clamped head pieces:
- Inner part (12) with a **conical holding section (14)** tapering toward the tube.
- Outer part (13) screwed on **like a union nut**, acting as a clamping ring.
- The tube end is spread radially over the cone and clamped between cone and nut → simultaneously a **fluid-tight** seal and a **tension-resistant** anchor for the embedded strands.
- Threaded holes (15) let it bolt up "like a fluid power drive cylinder."

### 3.2 Classic commercial DMSP/MAS membrane

The widely-cited description of the production Festo muscle (e.g. the IJME teaching article, [paper library](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/tree/main/papers) external link in §7): the membrane is built by **wrapping a synthetic/natural rubber tube with a man-made fiber (e.g. aramid/Kevlar) at a predetermined angle, giving the fiber wrapping a protective rubber coating, and attaching metal fittings at each end.** The fibers form a **rhombic (rhomboidal) grid** embedded in the chloroprene wall; pressing the membrane radially deforms the rhombi and shortens the muscle.

Note the two Festo variants differ: the production DMSP uses an embedded **rhombic braided/woven grid**; the US 6,349,746 patent describes a refinement using **non-crossing coaxial layers** to remove even the residual fiber crossover friction. Both are "embedded." For a DIY build, the rhombic-grid + rubber-overcoat route (§4.1) is the realistic target; the fully-separated coaxial lay-up is a factory process.

**Production specs** (Festo DMSP family, for sizing reference):
- Nominal diameters: **5, 10, 20, 40 mm**.
- Max contraction: **~25% of nominal length** (≈3% pre-stretch, useful stroke ~25%).
- Operating pressure: up to ~6 bar (DMSP) / 8 bar; max force scales with diameter - roughly **5→100 N, 10→~630 N, 20→~1500 N, 40→~6000 N** at rated pressure.
- Force is highest at the start of contraction and falls as contraction increases (nonlinear, [`PAM Design Variables.md` §1.2](PAM%20Design%20Variables.md)).
- No stiction, sealed against dirt/dust, very long cycle life - all consequences of the embedded wall.

### 3.2a Helix vs. braid - and does embedding cost contraction?

Two questions that come up immediately. Both answers are reassuring.

**Festo didn't abandon the braid *geometry* - only the *interlacing*.** The wall still has two opposed helical fiber families crossing at an angle, forming the same rhombic lattice as a braid; the kinematics are identical (angle θ swings toward the 54.7° neutral, the `3cos²θ − 1` law holds). What changed is **topology**: a real braid is *interwoven* (each fiber weaves over-under its neighbors); Festo's is *coaxially layered* (inner helix, elastomer spacer, outer helix - never interlaced). Same lattice, not woven.

**Why layered, not woven** - Festo's stated innovation is the "wave-free, fully stretched" fiber:
1. **No fiber-on-fiber friction** - a woven braid rubs at every crossover on every cycle (the dominant hysteresis/wear source, [`PAM Design Variables.md` §1.8](PAM%20Design%20Variables.md)); layered helices separated by elastomer never touch.
2. **No crimp/waviness** - weaving forces each fiber to undulate over-under; under tension that waviness must straighten before the fiber loads (lost motion + a flex-fatigue site at every knuckle). A straight geodesic helix loads instantly and fully → stiffer transmission, longer life. (This is also what lets stiff/brittle fibers survive - see [`Embedded-Braid Fabrication (Vulcanized & Silicone Paths).md` §4](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Embedded-Braid%20Fabrication%20%28Vulcanized%20%26%20Silicone%20Paths%29.md).)
3. **Cleaner encapsulation** - a flat helix is easy to fully surround with rubber; woven knuckles trap rubber-poor voids and stress concentrations.
4. **Manufacturability** - you braid a *sleeve*; you can't braid *into* a wall, but you can wind helical layers and vulcanize. The embedded process itself favors layered helices.

**Does embedding kill contraction? No - it's roughly neutral.** Festo DMSP maxes ~25%, the same ballpark as a typical braided McKibben (~20-30%). Contraction is set by **initial fiber angle θ₀, the 54.7° ceiling, and aspect ratio** ([§1.2, §3.3](PAM%20Design%20Variables.md)) - *not* by whether the lattice floats or is bonded. Embedding adds only a small penalty (the matrix must shear to let θ change → slightly higher threshold pressure). The big stroke numbers come from high aspect ratio + multifilament, which is independent of embedding - so you can embed *and* keep high stroke if the geometry stays slender. **One caveat:** if the fiber is *over-bonded into a thick wall* it can stop scissoring and the muscle extends instead of contracting - see [`Embedded-Braid Fabrication (Vulcanized & Silicone Paths).md` §6](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Embedded-Braid%20Fabrication%20%28Vulcanized%20%26%20Silicone%20Paths%29.md).

### 3.3 Contrast - US 2011/0067563 A1 - "Extensile Fluidic Muscle Actuator" (Univ. Maryland / Innovital; Woods, Wereley, Kothera, Boyer)

Included as the **counter-example**: a high-end research FMA that is explicitly **not** embedded. It keeps the classic split - a resilient elastomer **bladder** with a **separate braided sleeve surrounding it** - and **swages** both layers onto machined end fittings (aluminum/titanium/FRP). Friction is managed by *coating* (PTFE, graphite, dry-film lube) rather than by embedding. Its novelty is unrelated to the wall: a **pushrod + offset end-fitting geometry converts the muscle's contraction into net extension.** Useful to show that even sophisticated FMAs often stay with the sleeve architecture because it is so much easier to build - and then fight friction chemically.

---

## 4. Construction methods to embed braid into a tube wall

Ordered from most DIY-feasible to full factory process.

### 4.1 Braid-then-overcoat (dip / paint / pour) - **most DIY-feasible**
The IJME-described Festo route, scaled down:
1. Start with a cured elastomer tube (silicone or latex).
2. Slide the braided sleeve over it at the target angle; tension it so it seats tight.
3. **Overcoat the braid with uncured elastomer** - dip in liquid silicone (e.g. a thin Sil-Poxy / Dragon-Skin-thinned mix or a brushable RTV), or pour in a tube mold. The coating wicks through the braid openings and bonds to the inner tube, encapsulating the fibers.
4. Cure. The fibers are now locked between the original tube and the new outer skin - no sliding sleeve.

Pros: uses commodity braid, no winding rig. Cons: bond quality between cured inner tube and new silicone is the failure point (needs a primer/uncured-to-cured bond or a co-cure); fiber spacing isn't controlled (fibers still touch - closer to the rhombic DMSP than to the separated-coaxial patent).

### 4.2 Two-stage / cast-in-place molding
1. Cast (or extrude) the inner elastomer layer on a mandrel.
2. Lay or wind the fiber lattice onto it at the target angle.
3. Cast the outer elastomer layer over the fibers in a closed tube mold so the fiber is sandwiched mid-wall.
4. Cure; remove mandrel.

This is the controllable version of 4.1 and the practical interpretation of the Festo vulcanized lay-up for a small shop using RTV silicone instead of vulcanized rubber. Fiber spacing/angle can be held by the winding step. Bonding is better because both elastomer layers can co-cure.

### 4.3 Wind-and-coat on a mandrel
1. Coat a mandrel with a release + a thin elastomer base layer.
2. **Filament-wind** the fibers directly at the chosen helix angle (two passes, opposite directions) - this reproduces the coaxial-layer idea of US 6,349,746 and lets you insert an elastomer spacing layer between the two wind directions.
3. Over-coat, cure, de-mandrel.

Closest small-scale analog to the Festo patent's separated coaxial construction. Needs a winding fixture but gives the lowest-friction wall.

### 4.4 Vulcanized rubber lay-up (the Festo factory process)
Uncured rubber sheet/sleeve + wound aramid + intermediate rubber spacing layers + outer rubber, assembled on a mandrel and **vulcanized under heat/pressure** so the whole wall cross-links into one part. This is what US 6,349,746 claims. Requires vulcanizing tooling, mold pressure, and rubber compounding - not realistic without rubber-process equipment, but it is the durability/performance ceiling.

### 4.5 Molded-then-bundled (bio-inspired, for multi-filament)
From Liu et al. (2021), *iScience* - relevant to AeroFlex's multi-filament direction:
1. Cast a thin elastomer tube (Dragon Skin 20) in a 3D-printed mold, both ends sealed.
2. Sheath each tube in a nylon mesh (cable-tie one end, heat-sinter the other) → a "muscle fiber unit" (MFU).
3. **Embed multiple MFUs in a second, softer silicone matrix** by molding (e.g. 5-10 MFUs laid in a mold, matrix poured around them) - controlling 3D fiber/pennation angle to mimic real muscle.
This is *two levels of embedding*: braid in/around each fiber, fibers in a matrix. It points at how a co-formed AeroFlex bundle could be made as one molded part.

---

## 5. Why embedding wins (and what it costs)

**What it removes** - directly maps to the loss terms in [`PAM Design Variables.md`](PAM%20Design%20Variables.md):
- **Fiber-on-fiber friction (§1.8)** - the dominant hysteresis source; gone when fibers are separated by elastomer (Festo patent) or at least bonded so they can't slide independently.
- **Bladder-braid friction (§2.5)** - gone; the fiber moves *with* the rubber, no relative sliding.
- **Bladder abrasion / wear (§2.6)** - gone; the sleeve no longer saws against the tube every cycle → the long Festo life.
- **Slip / sleeve migration** - fibers are anchored in the wall, so coverage and angle stay uniform.

**What it costs:**
- **Manufacturability** - from a $10 cut-and-crimp assembly ([`../design.md`](../docs/design.md)) to a molded/cured part with tooling.
- **Modularity** - kills the "spool of sleeved tubing, cut to length, crimp on site" supply model in [`../design.md`](../docs/design.md). Embedded muscles are made-to-length.
- **Repairability** - a single molded wall fails as a unit; you can't re-sleeve it. (Contrast the multi-filament graceful-failure argument in [`PAM Design Variables.md` §5.2](PAM%20Design%20Variables.md).)
- **Restoring force / stiffness** - bonding the fibers to the membrane stiffens the wall; bench-test whether passive return is still adequate or needs antagonist/preload ([§4.7](PAM%20Design%20Variables.md)).
- **Bond reliability** - for the DIY routes (4.1-4.2), elastomer-to-elastomer bond and fiber encapsulation become the new dominant failure mode, replacing crimp/seal failures.

---

## 6. Implications for AeroFlex

- **Current AeroFlex is firmly separate-sleeve** (latex tube + overexpanded PET sleeve + crimped ferrule; [`../design.md`](../docs/design.md)). That is the right call for fast, cheap iteration and the spool/cut-to-length supply story.
- **Embedded is the durability/efficiency endpoint**, already named in [`../design.md`](../docs/design.md). It is the path to Festo-class hysteresis and life - relevant if AeroFlex ever needs precise force control or high cycle counts (where the ~20-30% friction loss and bladder abrasion become the limiters).
- **Realistic first experiment:** method **4.1 (braid-then-overcoat)** on a short silicone muscle - slide PET/aramid braid over silicone tube, brush/dip an RTV overcoat, cure. Compare its hysteresis loop and cycle-to-failure against the standard crimped muscle in the [`../design.md`](../docs/design.md) validation plan (force-stroke mapping + fatigue). This is the cheapest way to measure what embedding actually buys on *our* geometry.
- **Multi-filament angle:** method **4.5** (mold each thin fiber, embed the bundle in a soft matrix) is the embedded analog of the Suzumori-Endo multifilament approach AeroFlex already targets ([`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md), [`PAM Design Variables.md` §5.2](PAM%20Design%20Variables.md)). A co-formed bundle could combine high stroke *and* low hysteresis.
- **Open unknowns to test:** (1) silicone-to-silicone overcoat bond strength at pressure; (2) whether an embedded wall still provides enough passive restoring force; (3) achievable/repeatable braid angle without a winding rig; (4) end-fitting strategy when there's no loose sleeve to crimp - the Festo cone + union-nut clamp (§3.1) is the model.

---

## 7. References

### Local PDFs (in the private [paper library](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/tree/main/papers))

| File | Reference | Relevance |
|---|---|---|
| [`Evaluation of Machine Learning-Based Parsimonious Models for Static Modeling of Fluidic Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Evaluation%20of%20Machine%20Learning-Based%20Parsimonious%20Models%20for%20Static%20Modeling%20of%20Fluidic%20Muscles.pdf) | **Trojanová, M., Hosovský, A., Čakurda, T.** (2023). *Mathematics*, 11(1):149. [DOI](https://doi.org/10.3390/math11010149) | Braided/pleated/netted/**embedded** taxonomy; Festo muscle defined as rubber tube + embedded aramid insert; ML static force models for DMSP sizes. |
| [`Analysis of the Antagonistic Arrangement of Pneumatic Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Analysis%20of%20the%20Antagonistic%20Arrangement%20of%20Pneumatic%20Muscles.pdf) | **Tuleja, P., Jánoš, R., Semjon, J., Sukop, M., Marcinko, P.** (2023). *Actuators*, 12(5):204. [DOI](https://doi.org/10.3390/act12050204) | Antagonistic (biceps/triceps) pairing of fluidic muscles modeled on the human arm. |
| [`3D Reticulated Actuator Inspired by Plant Up-Righting Movement.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/3D%20Reticulated%20Actuator%20Inspired%20by%20Plant%20Up-Righting%20Movement.pdf) | **Masselter, T., Speck, O., Speck, T.** (2021). *Biomimetics*, 6(2):33. [DOI](https://doi.org/10.3390/biomimetics6020033) | Plant cortical fiber nets over tubes; the 54.7° fiber-angle threshold for contract-vs-extend; names the Festo fluidic muscle as the technical analog. |
| [`Bioinspired actuators.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Bioinspired%20actuators.pdf) | **Liu, C., Wang, Y., Qian, Z., et al.** (2021). *iScience* (HimiSK). | Molded muscle-fiber-units (Dragon Skin + nylon mesh) embedded in a silicone matrix at programmed pennation angles - method §4.5. |

### Patents

- **US 6,349,746 B1** - *Actuating means* (Festo; Bergemann, Lorenz, Thallemer; priority 1999, expired 2020). The embedded coaxial-strand vulcanized-wall construction. <https://patents.google.com/patent/US6349746B1/en>
- **US 2011/0067563 A1 / US 8,904,919 B2** - *Extensile Fluidic Muscle Actuator* (Univ. Maryland & Innovital; Woods, Wereley, Kothera, Boyer; priority 2006). Counter-example: separate sleeve + swage + pushrod-to-extension. <https://patents.google.com/patent/US20110067563A1/en>

### External / web

- **Pack, R. T. et al.** *The Fluid Muscle: A New Pneumatic Actuator* - IJME teaching article describing the Festo MAS construction (rubber tube + Kevlar wrap + rubber overcoat + metal fittings). <https://ijme.us/issues/spring%202002/articles/fluid%20muscle.dco.htm>
- **Festo Fluidic Muscle DMSP/MAS** technical documentation (specs, pressed connectors, diameters, contraction). <https://www.festo.com/media/catalog/202851_documentation.pdf>
- **"A Review on the Development of Pneumatic Artificial Muscle Actuators: Force Model and Application"** - *Actuators* 11(10):288 (2022); PMC8456066. Survey of PAM types, manufacturing, force models. <https://pmc.ncbi.nlm.nih.gov/articles/PMC8456066/> · [MDPI](https://www.mdpi.com/2076-0825/11/10/288)

### Related repo docs

- [`PAM Design Variables.md`](PAM%20Design%20Variables.md) - physics of every variable (friction/hysteresis terms this construction targets).
- [`../design.md`](../docs/design.md) - current AeroFlex separate-sleeve build and validation plan.
- [`../components.md`](../docs/components.md) - current materials/BOM.
- [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md) - multi-filament thin-McKibben lineage.
</content>
</invoke>
