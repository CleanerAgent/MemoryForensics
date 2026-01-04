# Contributing to Memory Forensics Library

Thank you for your interest in contributing.

This project is a low-level C library focused on **process memory inspection and analysis**, with a clean separation between core logic and operating system backends.

---

## Project Structure

- `src/core/`  
  Platform-independent core logic and public API implementation.

- `src/os/`  
  Operating system backends.
  - `linux/` — Linux implementation (current)
  - `windows/` — Windows backend (work in progress)

- `src/region-analyzer/`  
  Memory region classification and analysis logic.

- `src/utils/`  
  Internal utility helpers (lists, helpers, etc).

- `api/`  
  Public headers exposed to users of the library.

---

## Contribution Guidelines

### General rules
- Follow existing code style and naming conventions.
- Keep changes focused and minimal.
- Avoid introducing OS-specific logic outside `src/os/`.
- Public API changes must be discussed before submission.

### Platform backends
- OS backends **must not** expose OS-specific types to the public API.
- Backend code is responsible only for collecting raw memory data.
- Analysis, classification, and logic belong to the core.

### Windows backend
- The Windows implementation should live entirely under `src/os/windows/`.
- It must conform to the same backend interface used by Linux.

---

## Commits and Pull Requests

- Write clear commit messages.
- One logical change per commit.
- Pull requests should describe **what** was changed and **why**.

---

## Project Status

- Current version: **v0.1.0-beta**
- Supported platform: **Linux**
- Windows backend: **under development**

---

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
