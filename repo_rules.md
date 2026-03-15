# Repository rules

## Branch naming

Branches should describe the type of work being done.

Format:
<type>/<short-description>


### Branch Types
- `feature/...` - new functionality
- `experimental/...` - experiments, prototypes, or research work
- `refactor/...` - internal code restructuring without changing behavior

### Examples
- feature/rust-bindings
- refactor/matrix-memory-layout
- experimental/gpu-backend

---

## Commit Message Rules

Commits follow a structured format:
<type>(<scope>): <short description>

Example:
- feat(core): add matrix multiplication
- fix(ffi): correct pointer type for buffer
- test(rust): add matrix wrapper tests
- chore(build): ignore rust build artifacts


### Commit Types

| Type | Meaning |
|-----|--------|
| `feat` | New feature |
| `fix` | Bug fix |
| `refactor` | Code restructuring without behavior change |
| `test` | Tests added or modified |
| `chore` | Build, tooling, repo maintenance |


### Commit Scopes

The scope describes **which part of the system is affected**.

Current scopes:

| Scope | Description |
|------|-------------|
| `core` | Core C++ ML library |
| `ffi` | C interface / ABI wrapper |
| `rust` | Rust bindings |
| `python` | Python bindings |
| `c` | C bindings |

Additional language bindings may be added later.

---

## General Guidelines
- Write commit messages in **imperativ mood** (e.g. `add`, `implement`)
- Keep the subject line **short and descriptive**
- Branch names describe **the work**, commits describe **the specific change**