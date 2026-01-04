# Changelog

All notable changes to this project will be documented in this file.

This project follows [Keep a Changelog](https://keepachangelog.com/en/1.1.0/)
and adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [0.1.0-beta] - 2026-01-04

### Added
- Initial public release of the Memory Forensics Library.
- Stable public C API with opaque handles for:
  - Library context
  - Process attachment
  - Memory snapshots
  - Snapshot diffs
- Linux backend for live process memory inspection.
- Snapshot-based memory acquisition with immutable snapshots.
- Snapshot diffing for runtime memory change detection.
- Memory region classification and analysis engine.
- Backend abstraction layer isolating OS-specific mechanisms.
- Integration test validating end-to-end snapshot and analysis flow.
- Tooling support via `compile_commands.json` generation.

### Design
- Strict read-only access to target process memory.
- No kernel modules, hooks, or intrusive instrumentation.
- Clean separation between public API, core engine, and OS backends.
- ABI-safe design enabling future internal refactoring.
- Backend-agnostic core enabling future platform extensions.

### Limitations
- Linux-only backend.
- Snapshot diff reporting currently exposes aggregated statistics only.
- No thread-safety guarantees at this stage.

---

## [Unreleased]

### Planned
- Extended diff inspection APIs.
- Improved logging and diagnostics subsystem.
- Backend expansion (platform-dependent).
- API stability review for `v0.2.0`.

