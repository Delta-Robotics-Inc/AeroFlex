# Test-rig evidence assets

This folder preserves user-supplied evidence and handoff bundles referenced by
[`../test-rig-electronics.md`](../test-rig-electronics.md). These files are
review artifacts; the tracked source tree remains the authoritative, reproducible
implementation.

For the complete individual-photo download list, see
[`photo-downloads.md`](photo-downloads.md). The 26 original project photos are
in [`photos/`](photos/); the two temporary-motor photos are retained at this
folder's top level under their descriptive filenames.

For a one-click handoff, download
[`aeroflex-test-rig-reference-photo-set-20260817.zip`](aeroflex-test-rig-reference-photo-set-20260817.zip).
It contains all 28 original JPGs and `photo-downloads.md`.

| File | Purpose | SHA-256 |
|---|---|---|
| `motor-sm42ht47-1684b-label-and-pulley.jpg` | Temporary Smart Automation SM42HT47-1684B motor label, body, shaft, and pulley. | `87A726064FB8E19068235EB5D155E7F3256E2E7A504C48D7F0AD3F0069BD1D02`[...]
| `motor-sm42ht47-1684b-leads.jpg` | Temporary motor's four un-terminated leads. | `3ADBA8247F0D4E226450626493350CCCA4E14AA6F1A3275B0B8990991FF8BBB6` |
| [`aeroflex-test-rig-source-c8e5bc8-20260817.zip`](aeroflex-test-rig-source-c8e5bc8-20260817.zip) | Source/documentation snapshot produced from commit `c8e5bc8`. | `74D69E56C396A7583B9C0C77[...]
| [`aeroflex-test-rig-machine-artifacts-20260817.zip`](aeroflex-test-rig-machine-artifacts-20260817.zip) | Generated dashboard build and PlatformIO caches from the commissioning workstation.[...]
| [`aeroflex-test-rig-reference-photo-set-20260817.zip`](aeroflex-test-rig-reference-photo-set-20260817.zip) | All 28 original reference photos plus `photo-downloads.md`. | `7AF783DF26648A6D[...]

The artifacts ZIP is intentionally a separate review record. Do not use it as
the primary build input and do not edit its contents in place; rebuild the
dashboard and firmware from tracked source when a fresh build is required.
