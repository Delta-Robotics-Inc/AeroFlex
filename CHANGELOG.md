# Changelog

All notable changes to the AeroFlex Standard are documented here.
Format follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/);
versioning follows [SemVer](https://semver.org/) once the standard reaches
its first tagged release (everything before 1.0.0 may change at any time).

## [Unreleased]

### Added

- Initial public structure of the AeroFlex Standard: muscle design and theory
  (`docs/`), the muscle build process (`manufacturing/`), cited research
  library (`research/`), and vendor datasheet index (`datasheets/`).
- Apache-2.0 license, trademark policy, code of conduct, contribution guide,
  issue and PR templates, and a CI link-integrity check.
- Per-muscle bill of materials with suppliers, verified prices,
  cost-by-length tables, and batch-order examples
  (`manufacturing/muscle-bom.md`).
- Browser telemetry HUD (`apps/hud/`): single-file Web Serial dashboard
  with a documented, controller-agnostic serial protocol, demo mode, and
  a porting guide.
