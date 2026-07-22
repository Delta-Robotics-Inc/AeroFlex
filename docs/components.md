# AeroFlex Components & Sourcing

A working catalog of parts, fittings, thread standards, and pneumatic hardware used to build AeroFlex prototypes and supporting test rigs.

> **Note.** Many of these are exploratory links from R&D. Not all are validated for production. Treat this as a working notebook, not a production BOM.

## Muscle assembly

### Inner tube

- **Latex slingshot tubing** - current choice. Cheap, durable, accepts high cyclic strain. Ages over time.
- **Silicone (future)** - better aging and lower permeability; sourcing hardness/size combos has been hard.
- **Polyurethane (future)** - being evaluated for longevity.

### Braided sleeve

- **PET Techflex Flexo Overexpanded** - current choice. Large radial expansion, easy to source. ([product page](https://www.techflex.com/general-purpose/flexo-overexpanded))
  - **Alt source / full specs:** [WireCare - Flexo Overexpanded](https://www.wirecare.com/product-lines/flexo-overexpanded) (same product, second distributor). PET, **expands ~4× nominal (4:1)**, temp **−70 → 125 °C** (melt 250 °C), nominal diameters **0.25 / 0.31 / 0.38 / 0.50 / 0.75 in**, halogen-free, RoHS, resists common solvents.
- Stiffer fibers (aramid, carbon, fiberglass) would raise force density but the target braid pattern is not readily available off the shelf.

> **Benchmark - buy a finished thin muscle.** [s-muscle](https://s-muscle.stores.jp/) sells the Suzumori thin McKibben by the meter (SM ~$28/m, EM durable ~$112/m). Useful as a performance/price reference and for direct comparison. Full catalog: [`research/s-muscle (Commercial Thin McKibben Muscle).md`](../research/s-muscle%20%28Commercial%20Thin%20McKibben%20Muscle%29.md).

### End fittings (current pairing)

- Barbed fitting on one end
- Push-to-connect on the other end
- Standard pneumatic hose ferrule, hydraulically crimped

This pairing is uncommon and dominates per-unit cost. A standard fitting kit is on the roadmap.

### Heat shrink (end bands)

A short band of **adhesive-lined dual-wall heat shrink** is recovered over the braid + tube at each end, between the sleeve and the ferrule, before crimping. On recovery it draws braid and latex together, the inner adhesive flows between the braid picks (densifies the sleeve + adds a cushion), and under the crimp it protects the braid and latex from the ferrule's sharp edges. See the assembly steps in [`design.md`](design.md).

**Current choice:** adhesive-lined dual-wall polyolefin, 4:1 ratio.

- [Techflex Shrinkflex 4:1 Dual Wall Adhesive (H4A)](https://www.techflex.com/heatshrink-tubing/h4a-adhesive-wall-4-1-heatshrink-tubing) - same supplier as the sleeve; 4:1 grabs over the braid OD.
- [Techflex Shrinkflex 3:1 Dual Wall Adhesive](https://www.techflex.com/heatshrink-tubing/3-1-dual-wall-adhesive-specialty)
- [TE Connectivity dual-wall adhesive heat shrink](https://www.te.com/en/products/heat-shrink-tubing/dual-wall-tubing.html) (ATUM 4:1; ES2000 = more flexible)

**H4A confirmed specs.** Outer wall: cross-linked **polyolefin**. Shrink ratio **4:1**. **Shrink temperature 194 °F (90 °C).** Permanent operating range **−55 °C to 125 °C**. UL 224 VW-1, RoHS. (Prop-65 antimony note = flame retardant in the polyolefin, not the adhesive.)

**Keep heating brief and focused** - latex is heat-sensitive (continuous limit well below 90 °C); localized shrink heat is fine, sustained is not.

> Deeper adhesive-chemistry and end-termination work is active internal R&D
> ([AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Latex%20Adhesive%20%26%20End%20Termination%20R%26D.md), team access).

### Candidate fittings

> The buildable per-muscle list (quantities, prices, batch math) is
> [`manufacturing/muscle-bom.md`](../manufacturing/muscle-bom.md); this
> section is the wider sourcing notebook behind it.

- [NeoFit Acetal Black Stem Barb Connector - 3/8" stem × 1/4" barb](https://www.freshwatersystems.com/products/neofit-acetal-black-stem-barb-connector-3-8-stem-x-1-4-barb?variant=41531142570168)
  - **Design/manufacturing guide (dimensions, fit data):** [`datasheets/Freshwater-NeoFit-Insert-Design-Guide.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Freshwater-NeoFit-Insert-Design-Guide.pdf) ([source](https://assets.freshwatersystems.com/image/upload/s--Qx6lkIKp--/mnkgbxvvoabscnclwqt1.pdf))
- [John Guest Plastic Half Cartridge - 3/8 Gray Double Nitrile O-ring](https://www.freshwatersystems.com/products/john-guest-plastic-half-cartridge-3-8-gray-double-nitrile-o-ring?variant=42407775502520)
- [John Guest Plastic Half Cartridge - 1/4 Gray Double Nitrile O-ring](https://www.freshwatersystems.com/products/john-guest-plastic-half-cartridge-1-4-gray-double-nitrile-o-ring?variant=42407776157880)
- [SMC KQ2 One-Touch fitting (inch-size tube, no connection thread)](https://www.smcusa.com/search?q=KQ2) - connector design idea

## Thread standards

| Thread | Use | Notes |
|---|---|---|
| 1/4" NPT | Preferred for muscle plumbing | Smaller tubing, more flexible. ≤464 psi max. ([example tubing](https://a.co/d/j4KfsvA)) |
| 3/8" NPT | Higher-flow applications | |
| 5/8"-18 UNF or G1/2-14 | Paintball tank interface | Mixed results - verify before ordering |

## Pneumatic infrastructure

### CO₂ / HPA tanks (portable supply)

Carry options for wearable / mobile tests:

- [MOLLE tactical pouch for tank carry (idea)](https://www.amazon.com/R-SASR-Upgraded-Tactical-Drawstring-Hydration/dp/B07RMDX6W1)
- <https://www.amazon.com/gp/product/B01AKDA04W>
- <https://www.amazon.com/gp/product/B000KD7DJS>
- [Larger CO₂ tank idea](https://www.amazon.com/gp/product/B0DT9KZSM7)
- <https://www.amazon.com/gp/product/B07RT9XKNT>

### High-pressure regulators (paintball-derived)

> **Why paintball.** Paintball has spent decades miniaturizing high-pressure, high-flow regulators into thumb-sized inline form factors that handle 800+ psi inputs. They are the smallest set-and-forget regulators on the market at any price. Our wearable-lift prototype used one to step 800 psi CO₂ → 100 psi - the only form factor that fit. The inline geometry also enables the **electronically-variable AeroFlex regulator** concept (replace the spring with a coil/solenoid for closed-loop control while keeping the inline footprint). See [`products/regulator-variable.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/regulator-variable.md) §"Form-factor inspiration."

- [Custom Products V2 Inline Regulator - Silver](https://www.actionvillage.com/Custom-Products-V2-Inline-Regulator-Silver-p/cpv2inlineregulatorsilver.htm) - 3" length, inlet ≤ 900 psi (CO₂/HPA) 1/8" NPT, outlet 0-500 psi, fast recharge.
- [GladiatAir 3000 psi Warriair Regulator](https://paintballshop.com/gladiatair-3000psi-warriair-regulator-high-pressure/)
- [Ninja Paintball regulator manuals](https://www.ninjapaintball.com/manuals)
- [Custom Products V2 Inline Regulator - Red](https://ansgear.com/custom-products-v2-inline-regulator-red/)

**How they work (reference):**
- [ZDS Paintball - MaxFlo regulator animations](https://www.zdspb.com/tech/misc/maxflo.html) and the full [ZDS Paintball tech site](https://www.zdspb.com/)
- [Paintball regulator walkthrough video](https://www.youtube.com/watch?v=GjHbhDEhYLU) - piston, spring, seat, self-regulating mechanism explained

### Automotive CO₂ regulators

- [Snow Performance billet adjustable 0-475 psi w/ gauges (SNO-354G)](https://idspeedshop.com/snow-performance-billet-adjustable-0-475psi-co2-regulator-w-gauges-sno-354g/)
- [Snow Performance dual-outlet adjustable 0-475 psi (SNO-354)](https://idspeedshop.com/snow-performance-dual-outlet-adjustable-0-475-psi-1-8npt-outlet-co2-regulator-sno-354/)
- [Snow Performance dual-outlet fixed 100 psi (SNO-353)](https://idspeedshop.com/snow-performance-dual-outlet-fixed-100-psi-1-8npt-outlet-co2-regulator-sno-353/)
- [Snow Performance billet adjustable 0-475 psi (alt vendor)](https://shop.sohiperformance.com/product/snow-performance-billet-adjustable-0-475psi-co2-regulator-with-gauges-sno-354g)

### Solenoid valves

- [2V025-08 Normally-Closed Electric Solenoid](https://www.amazon.com/Pneumaitc-Normally-Electric-Solenoid-2V025-08/dp/B0815WY9HJ) - 1/4" NPT, 25-116 psi. **24 V coil** (rated 21.6-26.4 V, ~120 Ω, 4.8 W), direct-acting.
  - **Drive/voltage/pressure reference:** [`Solenoid Drive (Voltage, Pressure & Peak-Hold).md`](../research/Solenoid%20Drive%20%28Voltage%2C%20Pressure%20%26%20Peak-Hold%29.md) - why a 24 V coil on a sagging 6S pack goes marginal (max pressure ∝ V²), the 21.6 V floor, peak-and-hold PWM, and how to pick the coil/rail for the next build.

### Proportional / electronic pressure-control valves (closed-loop benchmarks)

Commercial proportional / electronic pressure regulators - the off-the-shelf options (and the products to beat) for closed-loop AeroFlex pressure control. These are the benchmarks behind the [`products/regulator-variable.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/regulator-variable.md) concept.

| Product | Pressure | Key specs | Notes |
|---|---|---|---|
| [iQ Valves - Tesla Proportional Valve](https://www.iqvalves.com/tesla-proportional-no) | 0-100 psig | **No moving parts** (Tesla valve), <20 ms, hysteresis <10%, 3-7 W, 12/24 VDC, FKM/SS, 10M cycles | 2-way normally-open; air/gas/liquid; orifice .032"/.062". Novel valveless design. |
| [Proportion-Air MPV](https://proportionair.com/product/mpv/) | vacuum-150 psi | **±0.005% resolution, ±0.2% accuracy**, 0-10 V / 4-20 mA, 1/8" NPT, variable-orifice (no digital steps), shock/vib immune | Ultra-high-res, manifold-mountable (up to 12). Microfluidics/leak-test grade. |
| [Enfield Technologies - TR regulators](https://www.enfieldtech.com/Solutions/Pressure-Control) | vacuum-145 psi | **Voice-coil direct-acting, <2.5 ms** response, 460 / 1300 slpm flow | Fast + high-flow; the speed benchmark. Also LS-Series systems. |
| Adaract PCV / RSTV (hydraulic) | ~30-3,000 / to 2,650 psi | PCV: 67 g, 4.5 W, 25 ms; RSTV: <50 g, <1 W, "servo perf at proportional price" | High-pressure hydraulic; see the [Adaract vendor writeup](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Adaract%20%E2%80%94%20Hydraulic%20Artificial%20Muscle%20%26%20Fluid%20Power%20%28vendor%29.md) (private). |

**Takeaway:** Enfield is the speed bar (<2.5 ms voice coil), Proportion-Air the resolution bar, iQ Tesla the simplicity/cost play (no moving parts), Adaract the high-pressure/hydraulic option. The AeroFlex variable regulator aims to beat these on **price + compact inline form factor** at AeroFlex's pressure range - see [`products/regulator-variable.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/regulator-variable.md).

### Pressure transducers

- [FUSCH 0-150 psi pressure transducer](https://www.amazon.com/FUSCH-Transducer-Connector-Stainless-Transmitter/dp/B0CRQWHS7H) - 1/8-27 NPT, analog output (map in firmware).

### Misc / adapters / fittings

Catch-all of evaluation parts pulled from R&D shopping lists. Not curated - verify specs before ordering.

- <https://www.amazon.com/gp/product/B084ZDT4VY>
- <https://www.amazon.com/gp/product/B07XCW8B1M>
- <https://www.amazon.com/gp/product/B083DRNQXJ>
- <https://www.amazon.com/gp/product/B086JMZ5Y1>
- <https://www.amazon.com/gp/product/B07SSFWS1R>
- <https://www.amazon.com/gp/product/B07SXRL8YR>
- <https://www.amazon.com/gp/product/B08D5ZDF1Y>
- <https://www.amazon.com/gp/product/B07STVD3RR>
- <https://www.amazon.com/gp/product/B08CKKQL6G>
- <https://www.amazon.com/gp/product/B085NRHHSJ>
- <https://www.amazon.com/gp/product/B07RSLDDBR>
- <https://www.amazon.com/gp/product/B08JLWYJ28>
- <https://www.amazon.com/gp/product/B07S2H9HR6>
- <https://www.amazon.com/gp/product/B08F4ZQKJT>
- <https://www.amazon.com/gp/product/B0D62NR8KF>
- <https://www.amazon.com/gp/product/B07YN8LKFG>
- <https://www.amazon.com/gp/product/B08MLG7S71>
- <https://www.amazon.com/gp/product/B01EIVBYTC>
- <https://a.co/d/e3UHzor>

## Reference videos

- [How MaxFlo regulators work (overview)](https://www.zdspb.com/tech/misc/maxflo.html)
- <https://www.youtube.com/watch?v=Oy_LNHMDtf4>
- <https://www.youtube.com/watch?v=bcJQbouqVAU>
- <https://www.youtube.com/watch?v=0rKMD3i7DMU> - multi-filament high aspect ratio reference
