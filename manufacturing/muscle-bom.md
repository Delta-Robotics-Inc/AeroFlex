# Muscle Bill of Materials

Everything you need to buy to build the current off-the-shelf AeroFlex muscle.
The build sequence that uses these parts is
[`muscle-assembly.md`](muscle-assembly.md); the design rationale is in
[`../docs/design.md`](../docs/design.md) and the wider parts notebook in
[`../docs/components.md`](../docs/components.md).

Prices last verified July 2026. The sourcing notes at the bottom flag the
parts whose availability moves.

> Some links below are Amazon affiliate links: as an Amazon Associate,
> Delta Robotics earns from qualifying purchases, at no extra cost to you.

## Per-muscle parts

Each muscle has two ends. Each end gets a stem-barb connector and a crimped
ferrule; the barb seats inside the latex tube and the 3/8" stem plugs into a
push-to-connect socket. The sockets themselves (John Guest half-cartridges)
belong to the manifold/supply build, not the muscle - see
[`../docs/components.md`](../docs/components.md) for those.

Tube and sleeve are bought by length, so muscle length sets the variable
cost. First choice links are one-cart Amazon; the alternatives are usually
cheaper per unit if you do not mind multiple suppliers.

| Qty | Part | Spec | First choice (Amazon) | Alternatives |
|---|---|---|---|---|
| 2 | Stem-barb connector | 3/8" stem x 1/4" barb, acetal (NeoFit) | [$11.23/10-pack (~$1.12/ea)](https://amzn.to/45fFL8x) | [FreshWater $1.32](https://www.freshwatersystems.com/products/neofit-acetal-black-stem-barb-connector-3-8-stem-x-1-4-barb), [LIQUIfit $1.59](https://www.usplastic.com/catalog/item.aspx?itemid=75180&catid=915), [John Guest $1.66](https://www.freshwatersystems.com/products/john-guest-stem-barb-connector-3-8-od-stem-x-1-4-id-barb) - see [sourcing notes](#stem-barb-connector-sourcing) |
| 2 | Ferrule, crimp-on | 0.450" ID x 0.562" long (Interstate F0769) | [$34.20/50-pack (~$0.68/ea)](https://amzn.to/4yxJCLB) | [McMaster 6703K12, $11.12/50 (~$0.22/ea)](https://www.mcmaster.com/6703K12/) |
| 2 bands | Heat shrink, adhesive-lined | 1/2", marine grade 3:1 (XHF, 55 ft roll) | [$29.99 (~$0.55/ft)](https://a.co/d/09wSf8p6) | Spec-exact Techflex H4A 4:1 dual-wall: [WireCare 4 ft stick, $8.88](https://www.wirecare.com/products/h4a0-50cl-shrinkflex-4-1-dual-wall-adhesive-heatshrink-tubing-1-2-4ft-stick-clear); selection notes in [`../docs/components.md`](../docs/components.md) |
| per ft | Latex inner tube | 3/8" OD x 1/4" ID (Frienda, 100 ft) | [$24.99 (~$0.25/ft)](https://amzn.to/4bBdL2K) | Other Amazon sellers; search "3/8 OD 1/4 ID latex rubber tubing" |
| per ft | Braided sleeve | PET, 3/8" (see note on weave) | [Alex Tech 100 ft, $15.99 (~$0.16/ft)](https://amzn.to/3ROnnR1) | Spec-exact overexpanded weave: [Techflex Flexo Overexpanded at WireCare, $0.30/ft](https://www.wirecare.com/products/Flexo-PET-Overexpanded-38-White-95127?unit=125-ft) |
| - | Isopropyl alcohol | 99% IPA, assembly lube + latex degreaser | [128 oz, $34.95](https://amzn.to/3T3lnox) | Any pharmacy/hardware store (small bottles are fine) |

## Cost per muscle

```
Cost per muscle = fittings (fixed) + (tube + sleeve) x length in feet
```

Fittings run about **$3.60 per muscle** (Amazon 10-pack barbs plus Amazon
ferrules; the McMaster/LIQUIfit alternatives land within pennies of the
same total); tube + sleeve add **$0.55/ft** with the spec overexpanded
sleeve (about $0.41/ft with the standard Amazon sleeve). Materials only,
before shipping:

| Length | Fittings | Tube + sleeve | Total |
|---|---|---|---|
| 6" (150 mm) | $3.60 | $0.28 | **$3.88** |
| 12" (300 mm) | $3.60 | $0.55 | **$4.15** |
| 16" (400 mm) | $3.60 | $0.73 | **$4.33** |
| 24" (600 mm) | $3.60 | $1.10 | **$4.70** |
| 36" (900 mm) | $3.60 | $1.65 | **$5.25** |

Landed cost lands near $10 for small orders once shipping is spread over a
few muscles. The Amazon-first cart is also the cheapest path for the barbs
(10-pack pricing); only the ferrules are meaningfully cheaper elsewhere
(McMaster, about a third of the Amazon per-unit price).

First-time builders: add the one-time crimper (~$38) from the
[tools list](#tools-one-time-buys); it amortizes across every muscle you
ever build.

## Stem-barb connector sourcing

The 3/8" stem x 1/4" barb pairing (push-to-connect stem on one end, barb on
the other) is uncommon, dominates per-muscle cost, and goes out of stock
often:

| Option | Part | Unit | Notes |
|---|---|---|---|
| Amazon | [NeoFit via Amazon](https://amzn.to/45fFL8x) | $11.23/10-pack (~$1.12/ea) | Cheapest per unit; in stock |
| Alt | [NeoFit ATBC64-E at FreshWater](https://www.freshwatersystems.com/products/neofit-acetal-black-stem-barb-connector-3-8-stem-x-1-4-barb) | $1.32 | Singles; frequently unavailable |
| Reliable | [LIQUIfit hose stem at US Plastic](https://www.usplastic.com/catalog/item.aspx?itemid=75180&catid=915) | $1.59 | The dependable backup; qty discounts at 20+ |
| Alt | [John Guest stem barb at FreshWater](https://www.freshwatersystems.com/products/john-guest-stem-barb-connector-3-8-od-stem-x-1-4-id-barb) | $1.66 | Frequently unavailable |

Dimensional and fit data for the NeoFit insert family is in the vendor's
[design guide](https://assets.freshwatersystems.com/image/upload/s--Qx6lkIKp--/mnkgbxvvoabscnclwqt1.pdf).

## Batch example: 12 muscles at 400 mm

Best-value sourcing:

| Part | Need | Buy | Cost | Per muscle |
|---|---|---|---|---|
| Ferrule | 24 | 1 x McMaster 50-pack | $11.12 | $0.93 (26 spare) |
| Stem-barb connector | 24 | 3 x Amazon 10-pack | $33.69 | $2.81 (6 spare) |
| Sleeve | ~24 ft | 1 x 25 ft WireCare cut | $7.50 | $0.63 |
| Tube | ~24 ft | 1 x 100 ft roll | $24.99 | $2.08 (76 ft spare) |
| Heat shrink | ~2 ft of bands | 1 x H4A 4 ft stick | $8.88 | $0.74 (half spare) |
| **Total** | | | **~$86** | **~$7.18** |
| +20% shipping/tax/waste | | | ~$103 | ~$8.62 |

A second batch is cheaper again: the tube roll, spare ferrules, and spare
shrink carry over.

## Tools (one-time buys)

These are required to build muscles but are not per-muscle costs; buy them
once and they cover every build after that.

| Item | Why | Source |
|---|---|---|
| Hydraulic crimping tool kit | **Required.** Crimps the ferrules that seal each end; dies cover the sizes used here | [Amazon, $37.89](https://amzn.to/4fs5lvU) |
| Heat gun, variable temperature | **Required.** Recovers the shrink bands; use focused, low heat (latex is heat-sensitive). A variable-temp gun (150 °F floor) makes the low-heat guidance easy to follow | [Wagner FURNO 500, $54.00](https://amzn.to/44LnkIH) |
| Hot knife | Cuts PET sleeve without fraying and seals the cut end | [Better Boat hot knife, $49.99](https://amzn.to/4x1cjPD) |
| Spray bottles (nice to have) | IPA application for barb seating and latex prep, much easier than pouring | [32 oz 3-pack, $17.97](https://amzn.to/4ffwEe0) |

To drive and leak-test the finished muscle you also need regulated air or
CO2 at 30-100 psi; see [`../docs/components.md`](../docs/components.md) for
regulators, valves, and tanks.

## Sourcing notes

- **Stem-barb connector:** the volatile part. The Amazon 10-pack is the
  cheapest per unit and currently in stock; FreshWater and John Guest
  singles come and go; LIQUIfit is the dependable non-Amazon backup. Check
  stock before planning a batch.
- **Ferrule:** the Amazon 50-pack (~$0.68/ea) is one-cart convenient;
  McMaster is about a third of the price if you are ordering from them
  anyway.
- **Heat shrink:** the Amazon roll is 3:1 marine-grade; the spec-exact
  Techflex H4A is 4:1 (better grab over the braid OD). Both are
  adhesive-lined; selection notes are in
  [`../docs/components.md`](../docs/components.md).
- **Sleeve:** the Amazon listing (Alex Tech) is standard expandable PET
  braid at ~$0.16/ft - fine for first builds. The documented spec is
  Techflex Flexo **Overexpanded** (WireCare, flat $0.30/ft at any length):
  its overexpanded weave allows much more radial expansion, which is what
  buys stroke. Use the overexpanded sleeve for builds you plan to
  characterize.
- **Tube:** price varies by seller and color. Latex ages, so buy quantities
  you will use within about 6 months. Silicone is on the roadmap.
- **Fittings dominate per-muscle cost.** A standard fitting kit that replaces
  this rare pairing is on the AeroFlex roadmap.
