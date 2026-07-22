# Suzumori-Endo Robotics Laboratory

The Suzumori-Endo Robotics Laboratory at the Tokyo Institute of Technology (now part of [Science Tokyo](https://www.titech.ac.jp/), after the 2024 merger with Tokyo Medical and Dental University) is one of the most influential research labs in the world on pneumatic artificial muscles. Their **multi-filament thin McKibben muscle** architecture is a direct ancestor of the AeroFlex design philosophy - bundling small-diameter, high-aspect-ratio braided muscles to get force density, flexibility, and graceful failure modes that conventional single-sleeve McKibbens can't reach.

The lab sits in the Department of Mechanical Engineering, School of Engineering, and traces its lineage back to the **Suzumori Lab** that opened in 2014 when Prof. Suzumori joined Tokyo Tech from Okayama University. It has since become the joint Suzumori-Endo lab, reflecting Prof. Gen Endo's parallel work on tendon-driven and quadruped robotics.

## People

- **Prof. Koichi Suzumori** - Principal investigator. PhD from Yokohama National University. Joined Toshiba R&D in 1984, professor at Okayama University 2001-2014, Tokyo Tech from 2014. Widely cited (>8,000 citations across 800+ papers) as one of the pioneers of practical pneumatic artificial muscles.
- **Prof. Gen Endo** - Co-PI. Quadruped robots, tendon-driven mechanisms, TITAN series.
- **Assoc. Prof. Hiroyuki Nabae** - Soft actuator design, control, materials. Co-author on most of the thin-McKibben work.
- **Assoc. Prof. Shuichi Wakimoto** (Okayama) - Co-developer of the thin McKibben and smart McKibben technologies; co-founder of *s-muscle*.
- **Shunichi Kurumaya** - First author on the seminal "Design of thin McKibben muscle and multifilament structure" paper (2017).

## Core Technology - Thin McKibben Muscles & Multifilament Bundles

The lab's signature contribution is taking the classical McKibben pneumatic muscle (typically 10-40 mm outer diameter) and shrinking it to a **2-5 mm thin muscle** that can be woven, bundled, or sewn into textiles. The thin muscle stays compliant during contraction (a fat single-sleeve McKibben stiffens significantly) and a *bundle* of them behaves like a fascicle of biological muscle fibers.

### Spec snapshot (thin McKibben, s-muscle commercial samples)

| Parameter | Value |
| --- | --- |
| Outer diameter | 2-5 mm (vs 10-40 mm conventional) |
| Operating pressure | up to 0.5 MPa (~73 psi) |
| Contraction ratio | 20-25% |
| Max contraction force | ~30 kgf per 1 cm² of cross-section |
| Example: 2.5 mm muscle | ~15 kgf force |

### Multifilament muscle architecture

A typical multifilament bundle contains ~60 thin McKibben muscles, 310 mm long, sharing a single air supply tube with tendons terminated at each end and the whole bundle protected by heat-shrink sleeving. Individual muscles are designed with an **18° braiding angle** and **24 outer fibers**. If one strand fails, the bundle keeps working - the damaged muscle leaks minimally and can be patched and re-sealed. This graceful-failure behavior is what gives the architecture its biomimetic credibility: real muscles are made of redundant fibers too.

This is the architecture that directly informed AeroFlex's multi-filament, high-aspect-ratio approach - see [[design]] and the thin-McKibben paper at [[Thin McKibben muscle and multifilament structure]].

## Major Research Themes

- **Pneumatic artificial muscles** - thin McKibben, smart McKibben (with embedded conductive sensing fibers), reverse / back-stretchable McKibben, hydraulic high-power McKibben.
- **Soft robotics** - actuators, soft grippers, soft surgical tools.
- **Hydraulic tough robotics** - disaster-response robots that need motor-class force densities in soft, compliant form factors.
- **Musculoskeletal robots** - biologically faithful skeletons actuated entirely by bundled muscles (humanoid, canine, lower-limb).
- **Wearable robots & physical support** - power suits, orthoses, rehab devices for elderly care and post-stroke recovery.
- **Active textiles** - fabrics that contract on demand by weaving thin muscles directly into the weave.
- **Micro-robotics** - pneumatic actuators at sub-cm scale.

## Design Philosophy - "E-kagen" Robots

Prof. Suzumori repeatedly argues for what he calls **"E-kagen" robots** - Japanese for *roughly good enough*. The premise: instead of stacking 50 precise motors to get 6 DOF, mimic biological systems with many compliant, imprecise actuators that average out into useful, safe motion. This is the philosophical opposite of industrial robotics and is what makes muscle-driven robots feel different - they stroke, they yield, they handle surprises without bricking themselves or hurting the person nearby. It's also the reason multi-filament makes sense: each individual fiber is sloppy, but the bundle is reliable.

## Notable Projects

- **Musculoskeletal Robot Driven by Multifilament Muscles** - the lab's flagship demo. A full skeletal robot actuated entirely by bundled thin McKibben muscles. Won the **2016 Ghost in the Shell *Realize Project* Grand Prize** (Prosthesis/Robotics section), awarded March 25, 2017 at AnimeJapan. Awardees: Suzumori, Kurumaya, Morita.
- **Musculoskeletal Robot Dog** - quadruped with a flexible "hammock-like" shoulder structure modeled on actual canine anatomy, driven by thin McKibben muscles. Featured in IEEE Spectrum's *Video Friday* (Dec 2025).
- **Giacometti Arm** - a 20-meter-long, 20-DOF robot arm weighing only 940 g, built from helium-filled balloon segments actuated by thin pneumatic muscles. Compresses to ~20 cm; one person can carry it. Used for inspection of unreachable spaces (disaster sites, building interiors).
- **Long-Legged Hexapod Giacometti Robot** - same balloon-body principle in a six-legged platform.
- **TITAN-XIII** - sprawling-type quadruped, tendon-driven, walks in all directions via trot gait. (Prof. Endo's lineage.)
- **Hydraulic High-Power Artificial Muscle (with Bridgestone)** - developed under Japan's Cabinet Office **Tough Robotics Challenge** (ImPACT program, FY2014-FY2018, PM Satoshi Tadokoro). 15 mm OD, operates at 5 MPa (vs 0.3-0.6 MPa for conventional), delivers **7 kN (≈700 kgf)** contraction force at 30% contraction. 5-10× strength-to-weight of conventional motors and hydraulic cylinders. Targeted at impact drilling, concrete chipping, disaster response.
- **Active textiles** - fabrics woven from thin McKibbens; demonstrated in Hiramitsu et al. (IEEE Soft Robotics 2019) and the "Active Textile Braided in Three Strands" work.
- **Soft Robotic Heart** (2025) - a soft pump that mimics the myocardial band structure of the human heart.
- **Pig Tongue Soft Robot** (2025) - replicates the intrinsic muscle architecture of a mammalian tongue.
- **Vine-like Soft Grippers** (2025) - bio-inspired wrapping manipulation.
- **Wearable rehab orthoses** - finger exoskeleton for post-stroke spasticity (with Wakimoto et al.).
- **Power suits & support corsets** - commercialized via s-muscle for caregiving and manufacturing assistance.

## Commercialization - s-muscle Co., Ltd.

Founded **April 1, 2016** as a venture company spun out jointly from Tokyo Tech (Suzumori) and Okayama University (Wakimoto), with **Ikeda Seichusho Co.** and **Koganei Corporation**. Began shipping thin-muscle samples to manufacturers and research labs in July 2016; opened internet sales and lower-cost variants the following fiscal year. Targets nursing/caregiver suits, humanoids, ultra-lightweight robotics, and wearable supporters.

They sell the thin muscle **by continuous length (1/5/10 m)** - SM (prototyping) and EM (high-durability) grades - plus a B1 intro kit. Site <https://www.s-muscle.com/>, shop <https://s-muscle.stores.jp/>. **Full catalog, pricing, specs, and applications scraped into [[s-muscle - Commercial Thin McKibben Muscle]]** ([`../s-muscle (Commercial Thin McKibben Muscle).md`](s-muscle%20%28Commercial%20Thin%20McKibben%20Muscle%29.md)).

## Why AeroFlex Cares

The Suzumori-Endo lab's work is the closest published precedent for what AeroFlex is trying to be:

- **Bundle small muscles instead of one big one.** Higher aspect ratios increase stroke. Failure is graceful, not catastrophic. The bundle stays flexible. The multifilament idea in AeroFlex's [[design]] comes from here.
- **Biological fidelity over mechanical precision.** "E-kagen" is the right framing for wearables and human-interaction work (which is exactly what our wearable-lift work is going after).
- **Active textiles** point at a long-term form factor - weaving AeroFlex muscles directly into clothing rather than mounting them on rigid frames.
- **Hydraulic high-power variant** is a useful reference for what a high-pressure AeroFlex muscle could look like once we move beyond off-the-shelf textiles.
- **Sensing fibers** (smart McKibben with conductive fiber for pressure sensing) suggest a path for integrating sensing into AeroFlex without adding parts.

## Key Papers

These are the citations worth tracking. PDFs that are already in this folder are linked directly; the others are on ScienceDirect / Springer / IEEE.

- **Kurumaya, S., Nabae, H., Endo, G., & Suzumori, K.** (2017). *Design of Thin McKibben Muscle and Multifilament Structure*. **Sensors and Actuators A: Physical**, 261, 66-74. [DOI](https://doi.org/10.1016/j.sna.2017.04.047). Local copy: [[Thin McKibben muscle and multifilament structure]]. **This is the cornerstone paper.**
- **Kurumaya, S., Nabae, H., Endo, G., & Suzumori, K.** (2016). *Musculoskeletal lower-limb robot driven by multifilament muscles*. **ROBOMECH Journal**, 3(1), 18. [Open access](https://robomechjournal.springeropen.com/articles/10.1186/s40648-016-0061-3). Local copy: [[Musculoskeletal lower-limb robot multifilament]].
- **Takeichi, M., Suzumori, K., Endo, G., & Nabae, H.** (2017). *Development of a 20-m-long Giacometti arm with balloon body based on kinematic model with air resistance*. IROS 2017, pp. 2710-2716. Local copy: [[Giacometti arm 20m balloon body]].
- **Hiramitsu, T., Suzumori, K., Nabae, H., & Endo, G.** (2019). *Experimental Evaluation of Cloth-like Mechanisms Made of Artificial Muscles*. *J. Japan Society for Design Engineering*, 54(4), 245-252. Local copy: [[Cloth-like Mechanisms of Artificial Muscles (Hiramitsu JSDE)]]. (The closely-related IEEE RoboSoft 2019 paper is paywalled - see [[AeroFlex/research/README]] for the link.)
- **Suzumori et al.** (2022). *Smart textiles using fluid-driven artificial muscle fibers*. *Scientific Reports*. Open access. Local copy: [[Smart textiles fluid-driven artificial muscle fibers]].
- **Wakimoto, S., Misumi, J., & Suzumori, K.** (2016). *New concept and fundamental experiments of a smart pneumatic artificial muscle with a conductive fiber*. Pressure-sensing via the resistance of one fiber in the braid. Paywalled - see [[AeroFlex/research/README]] for links.
- **Kurumaya, S., Nabae, H., Endo, G., & Suzumori, K.** (2019). *Active Textile Braided in Three Strands with Thin McKibben Muscle*. *Soft Robotics*, 6(2), 250-262. Paywalled - see [[AeroFlex/research/README]] for links.
- **Suzumori, K., Wakimoto, S., et al.** - body of work on hydraulic high-pressure McKibben (Bridgestone collaboration, Tough Robotics Challenge).
- **Ueda, D., Suzumori, K., Nabae, H., et al.** (2025). *Soft Robotic Heart Formed with a Myocardial Band for Cardiac Functions*.
- **Kobayashi, R., Nabae, H., Endo, G., & Suzumori, K.** (2025). *Soft Linear Actuator Utilizing Electrically Vibrating Threads*.
- **Tanaka, S., Kobayashi, R., Nabae, H., & Suzumori, K.** (2025). *Time-Lag Generation Mechanical Valve for Enhancing Time Response of Back-Stretchable McKibben Muscles*.
- **Ishikawa, Y., Nabae, H., Gunji, M., & Suzumori, K.** (2025). *Pig tongue soft robot mimicking intrinsic tongue muscle structure*.
- **Kodama, H., Endo, G., & Suzumori, K.** (2025). *Verification of the Effect of Design Parameters on the Radius of Curvature of Vine-Like, Power Soft Gripper*.

## Online resources

- **Lab website (current):** <http://www.robotics.mech.e.titech.ac.jp/home.html>
- **Lab website (older Suzumori lab):** <http://www-robot.mes.titech.ac.jp/> (originally hosted lab pages; some links now redirect)
- **Tokyo Tech feature profile:** <https://www.titech.ac.jp/english/public-relations/prospective-students/first-step/suzumori-lab>
- **YouTube channel:** [@suzumoriendoroboticslabora1991](https://www.youtube.com/@suzumoriendoroboticslabora1991) - best single feed for video demos.
  - [Musculoskeletal Robot Driven by Multifilament Muscles](https://www.youtube.com/watch?v=0ZBD2tcKOU4)
  - [Dog Musculoskeletal Robot](https://www.youtube.com/watch?v=0np8RafBgqA)
  - [Active Textile made of Thin McKibben Muscles](https://www.youtube.com/watch?v=PYSqkEhVe6k)
- **s-muscle (commercial spinoff):** see Tokyo Tech announcement at <https://www.titech.ac.jp/english/news/2016/035340>
- **ResearchGate profile (Suzumori):** <https://www.researchgate.net/profile/Koichi-Suzumori>
- **Press / coverage:**
  - [Tokyo Tech - venture company announcement (2016)](https://www.titech.ac.jp/english/news/2016/035340)
  - [Tokyo Tech - Ghost in the Shell Realize Project award (2017)](https://www.titech.ac.jp/english/news/2017/038436)
  - [Tokyo Tech - Bridgestone hydraulic muscle (2017)](https://www.titech.ac.jp/english/news/2017/037286)
  - [JSME Medal for New Technology (2021)](https://educ.titech.ac.jp/mech/eng/news/2021_04/060616.html)
  - [IEEE Spectrum - Musculoskeletal Robot Dog (Dec 2025)](https://spectrum.ieee.org/musculoskeletal-robot-dog)
  - [Bridgestone - Tough Robotics Challenge (2017)](https://www.bridgestone.com/corporate/news/2017012601.html)
  - [Interesting Engineering - canine-inspired robot](https://interestingengineering.com/ai-robotics/japan-canine-inspired-robot)

## Related notes in this repo

- [[design]] - AeroFlex prototype writeup; mentions the high-aspect-ratio multifilament approach this lab pioneered.
- [[theory]] - citations to Chou & Hannaford and Tondu & Lopez (the older modeling foundations the Suzumori lab built on).
- [[Thin McKibben muscle and multifilament structure]] - the 2017 paper itself (PDF).
