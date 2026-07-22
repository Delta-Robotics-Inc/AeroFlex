# s-muscle - Commercial Thin McKibben Muscle (scrape)

Full scrape of **s-muscle Co., Ltd.** - the commercial source for the Suzumori/Wakimoto **thin McKibben artificial muscle**, sold by continuous length (the "spool" product). This is the closest off-the-shelf analog to AeroFlex's long-term miniaturized multifilament goal ([`../manufacturing/`](../manufacturing/)).

> **Provenance.** Scraped **2026-06-07** via Firecrawl (live HTTP 200) from `s-muscle.com` (technical / applications / business pages) and the `s-muscle.stores.jp` storefront + item pages - these block plain fetchers (HTTP 403) but Firecrawl rendered them. **Prices are tax-included (税込), live, and all items were in stock at scrape time.** Sales are Japan-based (STORES platform), priced in yen; USD is an approximation (¥155/$) - watch FX and confirm at checkout.

- **Company site:** <https://www.s-muscle.com/>
- **Online shop:** <https://s-muscle.stores.jp/>
- **Lab background:** [`Suzumori-Endo Robotics Laboratory.md`](Suzumori-Endo%20Robotics%20Laboratory.md)
- **The Multi-Filament Paper:** Kurumaya et al. (2017) - [`Research Papers/Thin McKibben muscle and multifilament structure.pdf`](https://github.com/Delta-Robotics-Inc/AeroFlex-Private/blob/main/papers/Thin%20McKibben%20muscle%20and%20multifilament%20structure.pdf)

---

## Company

Founded **April 1, 2016** as a university venture from Tokyo Tech (Prof. Koichi Suzumori) and Okayama University (Assoc. Prof. Shuichi Wakimoto), in cooperation with **Ikeda Seichusho Co., Ltd.** and **Koganei Corporation** (pneumatics). Began shipping samples July 2016; later opened internet sales.

**Services:** R&D, design, manufacturing, sales, application development, and technical consulting for McKibben-type artificial muscle. Active R&D partnerships with Tokyo Tech, Okayama University, and (per their applications page) **Disney Research** (automated muscle-fiber routing).

**Product categories:**
- **Artificial muscle** - bare thin McKibben by length (SM / EM series below).
- **Terminal processing & bundled assemblies** - custom end-processing and multifilament bundles (example shown: **30× 1.3 mm tubes bundled**, with **M3 tap** ends for standard quick-connect fittings).
- **Pneumatic control systems** - small portable compressors, regulators, manual valves; the B1 intro/eval kit.
- **New application development** - collaborative R&D / consulting.

---

## Product lineup & pricing

Two grades, three sizes each. Model number ≈ tube OD (**13** = 1.3 mm tube, **20** = 2.0 mm, **40** = 4.0 mm); the braid adds ~0.5 mm, giving the **finished OD** below. The shop rounds these in its titles ("約2 / 2.5 / 5 mm"). **Pricing is exactly linear per meter**, tax-included. USD ≈ ¥155/$.

### SM series - prototyping / evaluation grade (silicone tube)

For functional evaluation and prototypes. (Prices roughly halved vs. original after a production-process improvement.) Thinner = pricier (harder to make). *Same muscle as in the B1 kit.*

| Model | Tube OD | Finished OD | per m | 1 m | 5 m | 10 m |
|---|---|---|---|---|---|---|
| **SM13** | 1.3 mm | 1.8 mm | ¥5,390 (~$35) | ¥5,390 | ¥26,950 | ¥53,900 |
| **SM20** | 2.0 mm | 2.5 mm | ¥4,290 (~$28) | ¥4,290 | ¥21,450 | ¥42,900 |
| **SM40** | 4.0 mm | 4.5 mm | ¥3,740 (~$24) | ¥3,740 | ¥18,700 | ¥37,400 |

### EM series - high-durability grade (new rubber)

New rubber formulation rated **>1,000,000 cycles** at 0.3 MPa drive. ~4× the SM price. (10 m+ by inquiry; per-meter pricing implies ~¥173,800 / ¥151,800 for 10 m.)

| Model | Tube OD | Finished OD | per m | 1 m | 5 m |
|---|---|---|---|---|---|
| **EM20** | 2.0 mm | 2.5 mm | ¥17,380 (~$112) | ¥17,380 | ¥86,900 |
| **EM40** | 4.0 mm | 4.5 mm | ¥15,180 (~$98) | ¥15,180 | ¥75,900 |

### Intro kit

- **B1kit - "Play with Artificial Muscles"** (世界最小径の人工筋肉を動かしてみよう) - **¥13,200 (~$85).** Hand-actuated, **no compressor needed.** Contents: **2 m of SM20** muscle, 2 hand syringes, 2 types of pneumatic tube, 2 fittings, adhesive, 3 wooden boards, double-sided crimps, instruction manual.

### Direct item links

| Item | URL |
|---|---|
| SM13-1 / 5 / 10 m | [1 m](https://s-muscle.stores.jp/items/6164ed37e1fb4c2964efbe5b) · [5 m](https://s-muscle.stores.jp/items/6164f243a10275486f8631d9) · [10 m](https://s-muscle.stores.jp/items/6164f27e2305576093c3f84d) |
| SM20-1 / 5 / 10 m | [1 m](https://s-muscle.stores.jp/items/6164f2fc784e3f538cfefd4e) · [5 m](https://s-muscle.stores.jp/items/6164f501784e3f2cbcfefb74) · [10 m](https://s-muscle.stores.jp/items/6164f52ee1fb4c3689efbef7) |
| SM40-1 / 10 m | [1 m](https://s-muscle.stores.jp/items/6164f58a2305570757c3f9e1) · [10 m](https://s-muscle.stores.jp/items/6164f609603feb41b5131145) |
| EM20-1 / 5 m | [1 m](https://s-muscle.stores.jp/items/6165014cacbcb07fb4531c37) · [5 m](https://s-muscle.stores.jp/items/6165017a784e3f28b9fefa6a) |
| EM40-1 | [1 m](https://s-muscle.stores.jp/items/616501abacbcb05f695319a6) |
| B1kit | [kit](https://s-muscle.stores.jp/items/614fca0c51244e441beaeaf1) |
| SM series category | [category](https://s-muscle.stores.jp/?category_id=6153446023055728818c9be4) |

---

## Technical data

From the [technical page](https://www.s-muscle.com/%E6%8A%80%E8%A1%93%E8%B3%87%E6%96%99/) (per-model, verified):

| Model | Tube OD | Finished OD | Grade | Rec. pressure |
|---|---|---|---|---|
| SM13 | 1.3 mm | 1.8 mm | Silicone, eval/prototyping | 0.3 MPa |
| SM20 | 2.0 mm | 2.5 mm | Silicone, eval/prototyping | 0.3 MPa |
| SM40 | 4.0 mm | 4.5 mm | Silicone, eval/prototyping | 0.3 MPa |
| EM20 | 2.0 mm | 2.5 mm | High-durability rubber | 0.3 MPa |
| EM40 | 4.0 mm | 4.5 mm | High-durability rubber | 0.3 MPa |

General (across the line):

| Parameter | Value |
|---|---|
| Recommended operating pressure | **0.3 MPa** (all models) |
| Max operating pressure | ~0.5 MPa (~73 psi) |
| Contraction ratio | 20-25% |
| Max contraction force | ~30 kgf per 1 cm² cross-section (e.g. ~15 kgf for a 2.5 mm muscle) |
| Cycle life | **EM: >1,000,000 cycles at 0.3 MPa.** SM is eval-grade (life not specified) |
| Braid (per paper) | 18° braid angle, 24 outer fibers, ~0.5 mm over tube OD |
| Termination | **M3 tapped ends**, compatible with commercial one-touch connectors & clevis fittings |

Force-contraction characteristic **curves are published as images** on the technical page - numeric values aren't machine-extractable; read them off the page if exact force-vs-contraction is needed.

---

## Applications (from their 応用例 page)

1. **Moving fabric** - bundle or weave muscle fibers into textiles for flexible, shape-varied mechanisms.
2. **Body support** - soft, light power-assist suits; exoskeleton gloves; upper-limb support.
3. **Robotics** - ultralight long-reach robots, humanoid musculoskeletal robots, soft robots, quadrupeds, hexapods, the 20 m Giacometti arm.
4. **Specialized research** - Disney Research collaboration on automated muscle-fiber routing; biomechanical research rigs.

---

## Why this matters to AeroFlex

- **It's the proof-of-market and the benchmark** for the miniaturized multifilament muscle AeroFlex targets long-term. They sell **by the meter** - exactly the "spool" supply model AeroFlex wants ([`../design.md`](../docs/design.md), [`../manufacturing/muscle-assembly.md`](../manufacturing/muscle-assembly.md)).
- **Price reference points** for a thin muscle: ~$28/m (SM20) prototyping, ~$112/m (EM20) durable. Useful as the bar AeroFlex's current builds (~$10 per 12-in muscle, off-the-shelf) compare against on a $/performance basis.
- **The EM "new rubber, >1M cycles" grade** validates that durability is the lever worth paying ~4× for - consistent with AeroFlex's bladder/longevity roadmap ([`PAM Design Variables.md` §2.6](PAM%20Design%20Variables.md)).
- **M3-tapped terminations + bundled assemblies** are a concrete example of standardized fittings and multifilament bundling ([`PAM Design Variables.md` §5.2-5.3](PAM%20Design%20Variables.md)).

## Caveats

- Prices are **live and tax-included** as scraped 2026-06-07 (Firecrawl, HTTP 200); all items in stock. Still **confirm at checkout** and watch JPY/USD FX (USD figures are estimates at ¥155/$).
- Japan-based STORES shop; international buyers may need a forwarding service.
- Force-vs-contraction curves are image-only on the technical page - not captured numerically here.
- Listings/SKUs change over time.
</content>
