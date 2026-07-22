# AeroFlex Theory

Working notes on the physics that govern a McKibben pneumatic muscle: how pressure translates into pulling force, how braid geometry sets stroke length, and the practical limits engineers run into in the real world.

## Force from pressure

The idealized contraction force **F** of a McKibben muscle is:

$$F = P \cdot \frac{\pi D^2}{4} \,(3\cos^2\theta - 1)$$

| Symbol | Meaning | Units |
|---|---|---|
| F | Contraction (pulling) force | N or lbf |
| P | Internal pressure | Pa or psi |
| D | Internal bladder diameter | m or in |
| θ | Braid angle relative to the muscle's axis | degrees |

### Intuition

- Internal pressure inflates the inner bladder.
- The braid converts radial expansion into axial contraction.
- Higher pressure → higher force, up to a mechanical limit set by braid geometry.

### Worked example

For D = 1 in, θ = 20°, P = 60 psi:

- cos(20°) ≈ 0.94
- 3 cos²(20°) − 1 ≈ 3(0.8836) − 1 ≈ 1.6508
- F ≈ 60 psi × 0.7854 in² × 1.6508 ≈ **77.8 lbf**

This is the *theoretical maximum*. Real muscles deliver less due to:

- Braid friction
- Elastomer stiffness
- End fitting & connection losses
- Internal friction from bladder deformation

### Force-stroke tradeoff

- More stroke → less peak force.
- More peak force → less stroke.
- Typical operating pressure: **30-100 psi** (~200-700 kPa).
- Typical force range: a few lbf to several hundred lbf depending on size.

## Stroke length

### Typical contraction ratio

- **Most-reported range:** 25-30% of relaxed length.
- **Broader practical range:** 20-35%.

### Drivers

| Driver | Effect |
|---|---|
| Initial braid angle | Smaller angles (~15-20°) → larger stroke. Larger angles (>30°) → shorter stroke, higher force. |
| Elastomer stiffness | Stiffer bladder → less effective stroke. |
| Braid stiffness / weave density | Stiffer braid resists expansion → trades stroke for force capacity. |
| Operating pressure | Higher pressure → larger stroke, up to saturation. |
| Aspect ratio (length / diameter) | Long, slender muscles → slightly higher stroke %. |

### Reference values

| Source | Typical stroke | Notes |
|---|---|---|
| Chou & Hannaford (1996) | ~25% | Widely cited standard reference |
| Tondu & Lopez (2000) | 20-35% | Influential modeling/control review |
| FESTO Fluidic Muscle datasheets | 20-25% | Commercial actuators |
| Shadow Robot Company | ~25% | Practical robotics value |

### Design recommendation

For exoskeletons, prosthetics, and general robotics, target a **25-30%** design stroke - balances stroke vs. force capacity vs. durability.

### Example

Initial length 100 mm at 25% stroke → contracted length 75 mm, ΔL = 25 mm.

## Reference papers

Full PDFs are in [`research/`](../research/). Key sources:

- **Chou & Hannaford (1996)** - *Measurement and Modeling of McKibben Pneumatic Artificial Muscles*. See [`research/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Modeling_of_McKibben_Pneumatic_Artificial_Muscles.pdf).
- **Tondu & Lopez (2000)** - *Modeling and Control of McKibben Artificial Muscle Robot Actuators*. See [`research/McKibben_Robot_Muscle.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/McKibben_Robot_Muscle.pdf). Also on [ResearchGate](https://www.researchgate.net/publication/3206658_Modeling_and_Control_of_McKibben_Artificial_Muscle_Robot_Actuators).
- **FESTO Fluidic Muscle datasheets** - commercial reference, [DMSP catalog PDF](https://www.festo.com/media/catalog/202851_documentation.pdf).
- **Shadow Robot Company** - [shadowrobot.com](https://www.shadowrobot.com/).
