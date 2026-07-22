# Muscle Assembly Process

The validated hand-build sequence for the current off-the-shelf AeroFlex muscle. The design rationale and materials live in [`../design.md`](../docs/design.md) and [`../components.md`](../docs/components.md).

## Bill of materials (per muscle)

Full BOM with quantities, suppliers, prices, and batch-order math:
[`muscle-bom.md`](muscle-bom.md). Summary:

| Part | Current choice | Notes |
|---|---|---|
| Inner tube | Latex slingshot tubing | Heat-sensitive - see step 4 |
| Braided sleeve | PET Techflex Flexo Overexpanded | Hot-knife to cut without fraying |
| Heat-shrink end bands (×2) | Adhesive-lined dual-wall polyolefin, 4:1 (Techflex H4A) | Selection notes in [`../components.md`](../docs/components.md) |
| End fittings (x2) | Stem-barb connector, 3/8" stem x 1/4" barb | One per end; the stems plug into push-to-connect sockets on the manifold/supply side (sockets are part of the manifold build, not the muscle). Uncommon part; dominates cost |
| Ferrules (×2) | Standard pneumatic hose ferrule | Hydraulically crimped |
| Consumable | IPA (isopropyl alcohol) | Assembly lubricant, evaporates clean |

## Steps

1. **Cut to length.** Latex tube, PET overexpanded sleeve, two short bands of adhesive-lined heat shrink, and stage the ferrules + barbed fitting. (A hot knife keeps the PET from fraying - see [`../products/tools.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/tools.md).)
2. **Insert tube into sleeve.** Push the latex tubing inside the braided sleeve along the full length.
3. **Place the heat-shrink bands.** Slide a band onto the very edge of each end, over the sleeve + tube.
4. **Recover the heat shrink.** Heat each band so it shrinks and pulls the braid and latex tight together. The inner adhesive flows in between the braid picks - it holds the sleeve denser and adds an extra durability/cushion layer. *Use focused, low heat: latex is heat-sensitive, and H4A starts shrinking at ~90 °C (prefer a low-temperature-activation adhesive shrink - see [`../components.md`](../docs/components.md)).*
5. **Insert the barbed fitting.** Use IPA as a lubricant to seat the barb inside the tube. The IPA evaporates and leaves a clean, solid, tight seal - no residue. (Wiping the latex with IPA also degreases/de-talcs it, improving heat-shrink adhesion.)
6. **Crimp the ferrule.** Slide the ferrule over the heat-shrunk end and crimp it onto the barbed stem. The heat-shrink layer cushions the crimp: it keeps the ferrule's sharp edges from cutting the braid or puncturing the latex, and spreads the crimp load for a more uniform, durable seal. (Radial crimp ≫ hex crimp - see [`../products/tools.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/tools.md) and crimp-quality notes in [`../research/PAM Design Variables.md` §5.1](../research/PAM%20Design%20Variables.md).)
7. **Leak / pressure test.** Verify the build before use - see the validation plan in [`../design.md`](../docs/design.md).

## Why the heat-shrink step helps

Maps directly to [`../research/PAM Design Variables.md`](../research/PAM%20Design%20Variables.md): it attacks the **end-fitting stress concentration (§3.4)** and **crimp-quality variability (§5.1)** - the two places most muscles fail. The adhesive densifies the braid locally and the cushion prevents crimp-induced damage to braid and bladder. The bond is mostly **mechanical keying into the braid** plus the radial shrink squeeze.

Improved end-termination approaches are in active development.

## Related

- [`README.md`](README.md) - the manufacturing docs index.
- [`../design.md`](../docs/design.md) - design overview, performance, validation plan.
- [`../components.md`](../docs/components.md) - materials, fittings, and heat-shrink selection.
- [`../products/tools.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/tools.md) - hot knife, radial crimper, jigs, gauges.
</content>
