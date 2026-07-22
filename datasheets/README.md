# Datasheets

Vendor spec sheets and design guides downloaded for reference. The PDFs live in the **private** [AeroFlex-Private](https://github.com/Delta-Robotics-Inc/AeroFlex-Private) repo (vendor-copyrighted, so not redistributed here) - file links below need repo access; the Source column links to the original public downloads.

> Scraped/downloaded 2026-06-09. Source URLs kept for each so they can be refreshed.

## Adaract - ultra-compact (hydraulic) fluid power

Adaract makes high-pressure **hydraulic** artificial-muscle actuators, compact HPUs, and proportional/servo valves - a direct force-density benchmark for AeroFlex. Full writeup: [Adaract vendor writeup](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/research/Adaract%20%E2%80%94%20Hydraulic%20Artificial%20Muscle%20%26%20Fluid%20Power%20%28vendor%29.md) (private).

| File | What it is | Source |
|---|---|---|
| [`Adaract-Artificial-Muscle-Actuator-Spec-Sheet.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Adaract-Artificial-Muscle-Actuator-Spec-Sheet.pdf) | AM70 fluid-driven muscle - 70 lbf, 3.5 mm OD, 30% contraction, 1500 psi, 1.5M cycles | [adaract.com](https://adaract.com/s/Adaract-Artificial-Muscle-Actuator-Spec-Sheet.pdf) |
| [`Adaract-Compact-HPU-Spec-Sheet-2025-08-26.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Adaract-Compact-HPU-Spec-Sheet-2025-08-26.pdf) | 200 W hydraulic power unit, 3,200 psi, 1.1 lb, pump-in-rotor | [adaract.com](https://adaract.com/s/Adaract-Compact-HPU-Spec-Sheet-82625.pdf) |
| [`Adaract-PCV-Spec-Sheet.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Adaract-PCV-Spec-Sheet.pdf) | PCV electro-proportional valve - ~30-3,000 psi, 67 g, 4.5 W, 25 ms | [adaract.com](https://adaract.com/s/Adaract-PCV-Spec-Sheet.pdf) |
| [`Adaract-RSTV-Spec-Sheet-2026-01-08.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Adaract-RSTV-Spec-Sheet-2026-01-08.pdf) | Rotary Servo Throttling Valve - <50 g, to 2,650 psi, <1 W | [adaract.com](https://adaract.com/s/Adaract-RSTV-Spec-Sheet-1826.pdf) |

Spec-sheet hub: <https://adaract.com/adaract-specsheet-download> · Company: <https://adaract.com/>

## Build references

| File | What it is | Source |
|---|---|---|
| [`Freshwater-NeoFit-Insert-Design-Guide.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/datasheets/Freshwater-NeoFit-Insert-Design-Guide.pdf) | NeoFit barb/stem insert design & manufacturing guide - dimensions and fit data for the barbed end fittings AeroFlex uses | [freshwatersystems.com](https://assets.freshwatersystems.com/image/upload/s--Qx6lkIKp--/mnkgbxvvoabscnclwqt1.pdf) |

## Web-only references (not PDFs - captured in docs)

These vendors' data was scraped into the docs rather than downloaded:

- **iQ Valves - Tesla Proportional Valve** (no-moving-parts proportional valve) - <https://www.iqvalves.com/tesla-proportional-no>
- **Proportion-Air - MPV** (ultra-high-res electronic pressure regulator) - <https://proportionair.com/product/mpv/>
- **Enfield Technologies - Pressure Control** (TR voice-coil regulators) - <https://www.enfieldtech.com/Solutions/Pressure-Control>
- **WireCare - Flexo Overexpanded** (the PET braided sleeve, alt source) - <https://www.wirecare.com/product-lines/flexo-overexpanded>

See [`../components.md`](../docs/components.md) for where these slot into the AeroFlex build, and [`../products/regulator-variable.md`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/products/regulator-variable.md) for the proportional-valve benchmarks.
</content>
