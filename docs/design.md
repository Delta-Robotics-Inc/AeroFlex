# AeroFlex Prototype - Pneumatic Muscle

## Abstract

AeroFlex is a modular McKibben-style pneumatic muscle built from off-the-shelf parts. It exists because early ThermoFlex (SMA) trials needed a faster, cheaper path to full-scale application tests. The design emphasizes high aspect ratio, multi-filament geometry for longer stroke, quick iteration, and low part cost. It trades an air supply and plumbing for speed of learning.

## Motivation

Early SMA experiments were supply-limited and slow to iterate. Performance without braid and liquid cooling could not hit application targets. McKibben muscles are well documented, inexpensive, and fast to assemble. They let us prototype end-effectors at scale while SMA development continues. Tutorials and commodity parts reduce risk and cost.

## Design overview

AeroFlex uses a latex inner tube and an overexpanded PET braid to form the contracting sleeve. One end terminates on a barbed fitting, the other on a push-to-connect fitting. At each end, a short band of **adhesive-lined heat shrink** is recovered over the braid and tube before crimping; a hose ferrule is then crimped over that stack onto the barbed stem, creating a strong, airtight interference seal. The geometry follows high aspect ratio, multi-filament guidance to extend stroke beyond classic 20-30% limits seen in single-sleeve McKibben actuators ([demo video](https://www.youtube.com/watch?v=0rKMD3i7DMU)).

- **Tube.** Latex slingshot tubing. Cheap and durable. Silicone would be better for aging and permeability, but the needed hardness and size range were hard to source.
- **Sleeve.** PET Techflex Flexo Overexpanded for large radial expansion and easy sourcing ([product page](https://www.techflex.com/general-purpose/flexo-overexpanded)). Stiffer fibers (aramid, carbon, fiberglass) would raise force density, but the target braid pattern is not readily available off the shelf.
- **End fittings.** Barbed on one end and push-to-connect on the other. This pairing is uncommon, which drives cost.
- **Heat shrink (end bands).** Adhesive-lined dual-wall heat shrink at each end. On recovery it draws the braid and latex tight together, and the inner adhesive flows in between the braid picks - locking the sleeve denser and adding a cushioning layer that protects the braid and latex during crimping. See selection guidance in [`components.md`](components.md).
- **Crimp.** Standard pneumatic hose ferrule. A hydraulic crimp compresses braid, heat-shrink, and tube into the barbs and sets the seal.

All components are off-the-shelf. Total part cost is about $10 USD per 12 in muscle at current volumes. The fittings dominate cost. Size range is limited by available tube and sleeve SKUs. Custom runs with manufacturers would lower cost and widen diameters.

## Assembly process

The full validated hand-build sequence (cut → insert → heat-shrink end bands → IPA-seat the barb → crimp → leak-test) lives in [`manufacturing/muscle-assembly.md`](../manufacturing/muscle-assembly.md), with the per-muscle BOM and the rationale for each step. In short: the adhesive-lined heat-shrink bands densify the braid and cushion the crimp at the end fittings - the main failure zone ([`research/PAM Design Variables.md` §3.4, §5.1](../research/PAM%20Design%20Variables.md)).

## Performance characteristics

- **Stroke.** Classic McKibben muscles average 20-30% stroke. Multi-filament, high aspect ratio layouts increase practical stroke within pressure and buckling limits.
- **Force.** Proportional to pressure, effective braid angle, and active length. Stiffer braids shift the curve toward higher force at lower contraction.
- **Bandwidth.** Set by valve flow, internal volume, and compliance. Small diameters respond faster.
- **Compliance.** Intrinsically safe and backdrivable. Good for human interaction.

PET overexpanded sleeving tolerates large radial strain at modest cost. Latex inner tubes accept high cyclic strain but will age. Silicone upgrades remain on the roadmap.

## Controls and pneumatics

SMC Pneumatics regulators and valves are used for variable pressure control and repeatability. The present layout supports open-loop pressure control and simple closed-loop schemes with inline pressure transducers. A compact aluminum manifold can consolidate regulators, checks, exhausts, and sensors into a single block. For portable tests, a CO₂ paintball tank is a practical high-pressure source - small, energy-dense, easy to refill.

See [`components.md`](components.md) for the parts list.

## Manufacturability and scaling

Assembly is simple. Cut tube and sleeve to length, insert barbed hardware, slide ferrule, crimp, and leak-check. Cycle the muscle to settle the braid. For field use and education, a "spool" supply chain is attractive: ship continuous lengths of sleeved tubing on reels; users cut to length and crimp fittings on site, like wire spools. Festo's integrated products show the endpoint - tube and braid co-formed as a single part for high durability. See [`research/Embedded-Braid Construction (Festo Fluidic Muscle).md`](../research/Embedded-Braid%20Construction%20%28Festo%20Fluidic%20Muscle%29.md) for how that's built and DIY-feasible methods.

## Advantages

Rapid builds. Very low part count. Commodity sourcing. High stroke in a long, slender package. Natural compliance. Quiet compared to geartrains. Good platform to learn application-level constraints before committing to custom SMA geometry.

## Limitations

Requires compressed gas. Plumbing adds bulk. Stroke and force curves depend on braid angle and diameter. Latex ages. Off-the-shelf textiles cap ultimate force density. These are acceptable tradeoffs for a fast prototype vehicle.

## Validation plan

1. **Leak and burst tests.** Pressure test to rated limits with safety factor. Log failure modes.
2. **Force-stroke mapping.** Measure axial force versus contraction at discrete pressures. Build a family of curves for control.
3. **Bandwidth tests.** Step pressure, record transient response at different lengths and diameters.
4. **Fatigue.** Cycle at representative duty. Track force, stroke, and leak rate over time.
5. **Environmental.** Temperature and humidity aging for latex and PET. Document drift and maintenance intervals.
6. **Controls.** Compare manual regulators, SMC electro-pneumatic units, and PWM valve strategies. Evaluate a compact manifold prototype.

## Costs and supply

Per-unit at current volumes is near $10 USD for a 12 in muscle. Custom fittings are the cost lever. With manufacturer partnerships, cost drops and sizes expand. A standard fitting kit would remove the current rare barbed plus push-to-connect pairing.

## Future work

The design is updated over time as we learn - see [`manufacturing/`](../manufacturing/) for the current build process.

- Replace PET with higher modulus braid to raise force density
- Evaluate silicone or polyurethane inner tubes for longevity
- Design an integrated manifold with pressure sensing and quick-connects
- Add displacement sensing
- Explore multi-filament bundles
