# Research

Reference material on McKibben-style and braided pneumatic artificial muscles - modeling, design, sensing, multi-filament architectures, active textiles, and applications. Cited from [`../theory.md`](../docs/theory.md) and [`../design.md`](../docs/design.md).

For background on the Suzumori-Endo lab (origin of the multi-filament thin-McKibben architecture that inspired AeroFlex), see [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md).

The lab's commercial thin muscle (sold by the meter) is catalogued in [`s-muscle (Commercial Thin McKibben Muscle).md`](s-muscle%20%28Commercial%20Thin%20McKibben%20Muscle%29.md) - the closest off-the-shelf benchmark for AeroFlex's long-term thin-muscle goal.

For the **hydraulic** force-density benchmark, see the [Adaract vendor writeup](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Adaract%20%E2%80%94%20Hydraulic%20Artificial%20Muscle%20%26%20Fluid%20Power%20%28vendor%29.md) (private) - a 3.5 mm hydraulic muscle at 70 lbf, plus compact HPUs and proportional/servo valves. Datasheets in [`../datasheets/`](../datasheets/).

## Synthesis docs

- [`PAM Design Variables.md`](PAM%20Design%20Variables.md) - every variable that affects PAM performance and why.
- [`Embedded-Braid Construction (Festo Fluidic Muscle).md`](Embedded-Braid%20Construction%20%28Festo%20Fluidic%20Muscle%29.md) - how to co-form braid *into* the tube wall (Festo-style), the patents behind it, helix-vs-braid, and DIY-feasible methods. The construction counterpart to the variables catalog.
- Embedded-braid fabrication methods - active internal R&D, moved to
  [AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Embedded-Braid%20Fabrication%20%28Vulcanized%20%26%20Silicone%20Paths%29.md) (team access).
- [`Force Estimation from Pressure & Length.md`](Force%20Estimation%20from%20Pressure%20%26%20Length.md) - inferring muscle force without a load cell: the force = f(pressure, length) model, what sensor to add, the hysteresis caveat, a calibration recipe, and how it drops into a telemetry HUD as a derived channel.

See [`../manufacturing/`](../manufacturing/) for how these feed the AeroFlex manufacturing process.

## Paper library

The paper PDFs themselves live in the **private** [AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private) repo (publisher-copyrighted, so they can't be redistributed here). File links below go there and need repo access; everyone else can use the citation links (DOI / publisher / open-access) in each row.

### Foundational modeling

| File | Reference |
|---|---|
| [`Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf) | Chou & Hannaford (1996). *Measurement and Modeling of McKibben Pneumatic Artificial Muscles*. *IEEE Trans. Robotics & Automation*. [DOI](https://doi.org/10.1109/70.481753). The standard citation. |
| [`McKibben_Robot_Muscle.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/McKibben_Robot_Muscle.pdf) | Tondu & Lopez (2000). *Modeling and Control of McKibben Artificial Muscle Robot Actuators*. *IEEE Control Systems Magazine*. [DOI](https://doi.org/10.1109/37.833638). |
| [`Static Modeling of Braided Pneumatic Muscle Actuator.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Static%20Modeling%20of%20Braided%20Pneumatic%20Muscle%20Actuator.pdf) | *Static Modeling of Braided Pneumatic Muscle Actuator: An Amended Force Model*. *AIP Conf. Proc.* 2584 (2022). [DOI](https://doi.org/10.1063/5.0127788). Static force-pressure-stroke model. |
| [`Pneumatic-Muscle Actuator.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Pneumatic-Muscle%20Actuator.pdf) | General actuator design and analysis. |
| [`Pneumatic Artificial Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Pneumatic%20Artificial%20Muscles.pdf) | Daerden & Lefeber (2002). *Pneumatic Artificial Muscles: actuators for robotics and automation*. *Eur. J. Mech. Env. Eng.* [PDF](https://web.archive.org/web/2024/https://lucy.vub.ac.be/publications/Daerden_Lefeber_EJMEE.pdf). The classic PAM survey. |
| [`BRAIDED PNEUMATIC MUSCLE ACTUATORS.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/BRAIDED%20PNEUMATIC%20MUSCLE%20ACTUATORS.pdf) | Caldwell, Medrano-Cerda & Goodwin (1992). *Braided Pneumatic Muscle Actuators*. IFAC SICICA. [ScienceDirect](https://www.sciencedirect.com/science/article/pii/S1474667017493542). |

### Sensing & control

| File | Reference |
|---|---|
| [`Smart Braid Air Muscles that Measure Force and Displacement.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Smart%20Braid%20Air%20Muscles%20that%20Measure%20Force%20and%20Displacement.pdf) | Felt & Remy (2014). *Smart Braid: Air Muscles that Measure Force and Displacement*. IEEE/RSJ IROS. [IEEE Xplore](https://ieeexplore.ieee.org/abstract/document/6942949/). |
| [`Contraction Sensing with Smart Braid McKibben Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Contraction%20Sensing%20with%20Smart%20Braid%20McKibben%20Muscles.pdf) | Felt, Chin & Remy (2016). *Contraction Sensing with Smart Braid McKibben Muscles*. *IEEE/ASME Trans. Mechatronics*. [DOI](https://doi.org/10.1109/TMECH.2015.2493782). Inductance-based Smart Braid contraction sensing. |
| [`Pulse Modulation in Braided Pneumatic Actuators Mimics Real.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Pulse%20Modulation%20in%20Braided%20Pneumatic%20Actuators%20Mimics%20Real.pdf) | Elzein & Hunt (2024). *Pulse Modulation in Braided Pneumatic Actuators Mimics Contractile Behavior of Biological Muscles*. PSU Research Symposium. [PDXScholar](https://pdxscholar.library.pdx.edu/studentsymposium/2024/posters/57/). PWM control of braided PAMs. |

### Materials

| File | Reference |
|---|---|
| [`Soft Material for Soft Actuators.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Soft%20Material%20for%20Soft%20Actuators.pdf) | Miriyev, Stack & Lipson (2017). *Soft material for soft actuators*. *Nature Communications*. [DOI](https://doi.org/10.1038/s41467-017-00685-3). |

### Festo Fluidic Muscle & embedded-braid construction

See the synthesis doc [`Embedded-Braid Construction (Festo Fluidic Muscle).md`](Embedded-Braid%20Construction%20%28Festo%20Fluidic%20Muscle%29.md) for how these tie together.

| File | Reference |
|---|---|
| [`Evaluation of Machine Learning-Based Parsimonious Models for Static Modeling of Fluidic Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Evaluation%20of%20Machine%20Learning-Based%20Parsimonious%20Models%20for%20Static%20Modeling%20of%20Fluidic%20Muscles.pdf) | **Trojanová, Hosovský, Čakurda** (2023). *Mathematics* 11(1):149. [DOI](https://doi.org/10.3390/math11010149). Braided/pleated/netted/embedded taxonomy; ML static force models for Festo DMSP sizes. |
| [`Analysis of the Antagonistic Arrangement of Pneumatic Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Analysis%20of%20the%20Antagonistic%20Arrangement%20of%20Pneumatic%20Muscles.pdf) | **Tuleja et al.** (2023). *Actuators* 12(5):204. [DOI](https://doi.org/10.3390/act12050204). Antagonistic muscle pairing modeled on the human arm. |
| [`3D Reticulated Actuator Inspired by Plant Up-Righting Movement.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/3D%20Reticulated%20Actuator%20Inspired%20by%20Plant%20Up-Righting%20Movement.pdf) | **Masselter, Speck, Speck** (2021). *Biomimetics* 6(2):33. [DOI](https://doi.org/10.3390/biomimetics6020033). Plant cortical fiber-net actuators; 54.7° contract-vs-extend threshold. |
| [`Bioinspired actuators.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Bioinspired%20actuators.pdf) | **Liu et al.** (2021). *iScience* (HimiSK). Molded muscle-fiber-units embedded in a silicone matrix at programmed pennation angles. |

### Fiber-reinforced fabrication (Path B - cast silicone + embedded fiber)

For the build method, see [`Embedded-Braid Fabrication (Vulcanized & Silicone Paths).md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Embedded-Braid%20Fabrication%20%28Vulcanized%20%26%20Silicone%20Paths%29.md).

| File | Reference |
|---|---|
| [`Soft fiber-reinforced pneumatic actuator design.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Soft%20fiber-reinforced%20pneumatic%20actuator%20design.pdf) | **Polygerinos et al.** *Soft Fiber-Reinforced Pneumatic Actuator Design and Fabrication.* [Springer](https://link.springer.com/chapter/10.1007/978-3-030-23807-0_9). Foundational cast + wind + overcoat method. |
| [`Automatic design of fiber-reinforced soft actuators.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Automatic%20design%20of%20%EF%AC%81ber-reinforced%20soft%20actuators.pdf) | **Connolly, Polygerinos, Walsh, Bertoldi** (2017). *PNAS* 114(1):51-56. [Open access](https://www.pnas.org/doi/10.1073/pnas.1615140114). Fiber-angle → motion map (extend/twist/contract). |
| [`Modeling and Fabrication of Soft Actuators Based on Fiber-Reinforced Elastomeric Enclosures.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling%20and%20Fabrication%20of%20Soft%20Actuators%20Based%20on%20Fiber-Reinforced%20Elastomeric%20Enclosures.pdf) | *Actuators* 10(6):127 (2021). [MDPI](https://www.mdpi.com/2076-0825/10/6/127). Model + fabrication of fiber-reinforced elastomer actuators. |
| [`Smart Pneumatic Artificial Muscle Actuator.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Smart%20Pneumatic%20Artificial%20Muscle%20Actuator.pdf) | **Park et al. (CMU).** *Smart PAM with Embedded Microfluidic Sensing.* [PDF](http://www.cs.cmu.edu/~ylpark/publications/Park_Sensors13.pdf). Kevlar cast helically into silicone - an embedded-fiber muscle that **contracts**. |

### Suzumori-Endo Lab - thin McKibben & multifilament

| File | Reference |
|---|---|
| [`Thin McKibben muscle and multifilament structure.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Thin%20McKibben%20muscle%20and%20multifilament%20structure.pdf) | **Kurumaya, S., Nabae, H., Endo, G., Suzumori, K.** (2017). *Design of Thin McKibben Muscle and Multifilament Structure*. *Sensors and Actuators A: Physical*, 261, 66-74. [DOI](https://doi.org/10.1016/j.sna.2017.04.047). **The cornerstone paper for the multi-filament approach.** |
| [`Musculoskeletal lower-limb robot multifilament.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Musculoskeletal%20lower-limb%20robot%20multifilament.pdf) | **Kurumaya, S., Nabae, H., Endo, G., Suzumori, K.** (2016). *Musculoskeletal lower-limb robot driven by multifilament muscles*. *ROBOMECH Journal*, 3(1), 18. [Open access](https://robomechjournal.springeropen.com/articles/10.1186/s40648-016-0061-3). |
| [`Giacometti arm 20m balloon body.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Giacometti%20arm%2020m%20balloon%20body.pdf) | **Takeichi, M., Suzumori, K., Endo, G., Nabae, H.** (2017). *Development of a 20-m-long Giacometti arm with balloon body based on kinematic model with air resistance*. IROS 2017, pp. 2710-2716. [DOI](https://doi.org/10.1109/IROS.2017.8206097). |
| [`Cloth-like Mechanisms of Artificial Muscles (Hiramitsu JSDE).pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Cloth-like%20Mechanisms%20of%20Artificial%20Muscles%20%28Hiramitsu%20JSDE%29.pdf) | **Hiramitsu, T., Suzumori, K., Nabae, H., Endo, G.** (2019). *Experimental Evaluation of Cloth-like Mechanisms Made of Artificial Muscles*. *J. Japan Society for Design Engineering*, 54(4), 245-252. [J-STAGE](https://www.jstage.jst.go.jp/article/jjsde/54/4/54_2018.2823/_article/-char/en). Active-textile theme. |
| [`Smart textiles fluid-driven artificial muscle fibers.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Smart%20textiles%20fluid-driven%20artificial%20muscle%20fibers.pdf) | **Phan et al.** (UNSW, 2022). *Smart textiles using fluid-driven artificial muscle fibers*. *Scientific Reports*, open access. [DOI](https://doi.org/10.1038/s41598-022-15369-2). (Not a Suzumori-Endo paper - kept here for the active-textile theme.) |

## External / paywalled references

Couldn't fetch direct PDFs for these (paywalled or behind authentication). Links are kept here so they stay reachable.

### Suzumori-Endo lab - sensing & smart McKibben

- **Wakimoto, S., Misumi, J., Suzumori, K.** (2016). *New concept and fundamental experiments of a smart pneumatic artificial muscle with a conductive fiber*. McKibben muscle with one fiber in the sleeve replaced by a conductive material, used for pressure sensing via resistance.
  - [Okayama University Pure record](https://okayama.elsevierpure.com/en/publications/new-concept-and-fundamental-experiments-of-a-smart-pneumatic-arti)
  - [IEEE Xplore](https://ieeexplore.ieee.org/document/7419123) - *Experimental investigation of conductive fibers for a smart pneumatic artificial muscle* (related work, same authors)

### Suzumori-Endo lab - active textiles

- **Kurumaya, S., Nabae, H., Endo, G., Suzumori, K.** (2019). *Active Textile Braided in Three Strands with Thin McKibben Muscle*. *Soft Robotics*, 6(2), 250-262.
  - [PubMed](https://pubmed.ncbi.nlm.nih.gov/30995198/) · [Mary Ann Liebert](https://www.liebertpub.com/doi/10.1089/soro.2018.0076)
- **Hiramitsu, T., Suzumori, K., Nabae, H., Endo, G.** (2019). *Experimental Evaluation of Textile Mechanisms Made of Artificial Muscles*. IEEE RoboSoft 2019.
  - [IEEE Xplore](https://ieeexplore.ieee.org/document/8722802) · [Semantic Scholar](https://www.semanticscholar.org/paper/Experimental-Evaluation-of-Textile-Mechanisms-Made-Hiramitsu-Suzumori/d2d68a565495814188d796b9477c2d9ac7fe1fc6)
- **Hiramitsu et al.** *Active textile: woven-cloth-like mechanisms consist of thin McKibben actuators*. *Advanced Robotics*, 37(7), 2023.
  - [Taylor & Francis](https://www.tandfonline.com/doi/abs/10.1080/01691864.2022.2156813)

### Suzumori-Endo lab - high-power hydraulic McKibben

- **Suzumori, K., Sakurai, R. et al.** Tough Robotics Challenge hydraulic McKibben (5 MPa, 7 kN, 30% contraction). Multiple proceedings / journal publications from the FY2014-2018 program.
  - [Tokyo Tech news (2017)](https://www.titech.ac.jp/english/news/2017/037286)
  - [Bridgestone press (2017)](https://www.bridgestone.com/corporate/news/2017012601.html)
  - [RoboticsTomorrow coverage](https://www.roboticstomorrow.com/article/2017/01/development-of-a-hydraulic-drive-high-power-artificial-muscle-/9433)

### Suzumori-Endo lab - robots driven by thin McKibben

- **Suzumori, K., Endo, G., et al.** *Long-Legged Hexapod Giacometti Robot Using Thin Soft McKibben Actuator*.
  - [ResearchGate](https://www.researchgate.net/publication/318811111_Long-Legged_Hexapod_Giacometti_Robot_Using_Thin_Soft_McKibben_Actuator)
- **TITAN-XIII** - sprawling-type quadruped, tendon-driven. Multiple papers; lab summary at the [Tokyo Tech mech eng news](https://educ.titech.ac.jp/mech/eng/news/2021_04/060616.html).

### Suzumori-Endo lab - recent (2025)

These came out of the lab in January-February 2025. Mostly paywalled in IEEE / Elsevier / Springer.

- **Ueda, D., Suzumori, K., Nabae, H., et al.** (Feb 2025). *Soft Robotic Heart Formed with a Myocardial Band for Cardiac Functions*.
- **Kobayashi, R., Nabae, H., Endo, G., Suzumori, K.** (Jan 2025). *Soft Linear Actuator Utilizing Electrically Vibrating Threads*.
- **Tanaka, S., Kobayashi, R., Nabae, H., Suzumori, K.** (Jan 2025). *Time-Lag Generation Mechanical Valve for Enhancing Time Response of Back-Stretchable McKibben Muscles*.
- **Ishikawa, Y., Nabae, H., Gunji, M., Suzumori, K.** (Jan 2025). *Pig tongue soft robot mimicking intrinsic tongue muscle structure*.
- **Kodama, H., Endo, G., Suzumori, K.** (Jan 2025). *Verification of the Effect of Design Parameters on the Radius of Curvature of Vine-Like, Power Soft Gripper*.
- **IEEE Spectrum** - *Musculoskeletal Robot Dog* (Dec 2025 Video Friday): <https://spectrum.ieee.org/musculoskeletal-robot-dog>

### Survey / review papers (other authors)

- *A Review and Comparison of Linear Pneumatic Artificial Muscles*. International Journal of Precision Engineering and Manufacturing-Green Technology. [Springer](https://link.springer.com/article/10.1007/s40684-023-00531-6).
- *A Review on the Development of Pneumatic Artificial Muscle Actuators: Force Model and Application*. *Actuators* 2022. [MDPI](https://www.mdpi.com/2076-0825/11/10/288).
- *Design of linear pneumatic artificial muscles guided by biomechanics of human skeletal muscle for wearable application: a review*. *Bio-Design and Manufacturing*. [Springer](https://link.springer.com/article/10.1631/bdm.2400389).
- *A Novel Soft Pneumatic Artificial Muscle with High-Contraction Ratio*. *Soft Robotics*. [Mary Ann Liebert](https://www.liebertpub.com/doi/10.1089/soro.2017.0114).
- *Miniaturized and untethered McKibben muscles based on photothermal-induced gas-liquid transformation*. *Nature Communications* (open access). [Nature](https://www.nature.com/articles/s41467-024-45540-4).
- *New twist on artificial muscles* (twisted polymer yarns). *PNAS*. [PNAS PDF](https://www.pnas.org/doi/pdf/10.1073/pnas.1605273113).

### Author profiles & lab portals

- **Koichi Suzumori** - [ResearchGate](https://www.researchgate.net/profile/Koichi-Suzumori) · [dblp](https://dblp.org/pid/13/3867.html)
- **Suzumori-Endo Robotics Laboratory** - [official site](https://www.robotics.mech.e.titech.ac.jp/suzumori/) · [YouTube](https://www.youtube.com/@suzumoriendoroboticslabora1991)
- **Tokyo Tech profile of Suzumori** - <https://www.titech.ac.jp/english/public-relations/prospective-students/first-step/suzumori-lab>
