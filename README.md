# C++ Project Template

A minimal C++20 project template following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

**Toolchain:**
- **Clang 17** (compiler, clangd, clang-format, clang-tidy) + GCC as secondary
- **Bazel** build system (via Bazelisk)
- **GoogleTest** for unit testing
- **Google Benchmark** for benchmarking
- **ASan / TSan** sanitizer support (`--config=asan` / `--config=tsan`)
- **cpplint** for Google style checking
- **IWYU** for include hygiene

**Dev environment (devcontainer):**
- Ubuntu 24.04 with zsh + oh-my-zsh
- `gh` CLI (auth carried from host `~/.config/gh`)
- `claude` CLI (auth via `ANTHROPIC_API_KEY` env var)
- SSH keys, gitconfig, and `~/.zshrc` mounted from host
- `bazel-compile-commands` generates `compile_commands.json` for clangd on `postCreate`
- `buildifier` for BUILD file formatting

---

## First-time setup

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop)
2. Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) VS Code extension
3. Add to your host `~/.zshrc`:
   ```zsh
   export ANTHROPIC_API_KEY="sk-ant-..."
   ```
4. Clone this repo and open it in VS Code
5. When prompted, click **"Reopen in Container"** (or Command Palette → `Dev Containers: Reopen in Container`)
6. Wait for the container to build (~2–3 min first time, cached after)

The `postCreateCommand` automatically runs `bazel build //...` and generates `compile_commands.json` for clangd.


---

## Adapting for your project

1. Update `MODULE.bazel` — change `module(name = "myproject", ...)` to your project name
2. Rename `myproject` throughout:
   - `src/myproject/` → `src/yourproject/`
   - `src/myproject/BUILD` — update target names (`myproject_lib` → `yourproject_lib`)
   - Source files: `myproject.h`, `myproject.cpp`, `myproject_test.cpp`
   - `benchmarks/bench_myproject.cpp` and its `BUILD` deps
3. Update header guard: `#ifndef YOURPROJECT_YOURPROJECT_H_`
4. Delete this section from the README

**Header-only projects** (e.g. a units library, TypeList): use `hdrs` only in `cc_library` (no `srcs`), delete the `.cpp` implementation file.

---

## Building and testing

Available from the VS Code Command Palette (`Cmd+Shift+P` → `Tasks: Run Task`):

| Task | Command |
|---|---|
| **Build** | `bazel build //...` |
| **Run Tests** | `bazel test //...` |
| **Run Benchmarks** | `bazel run //benchmarks:benchmarks` |
| **Build (ASan)** | `bazel build //... --config=asan` |
| **Run Tests (ASan)** | `bazel test //... --config=asan` |
| **Build (TSan)** | `bazel build //... --config=tsan` |
| **Run Tests (TSan)** | `bazel test //... --config=tsan` |
| **Refresh compile_commands.json** | `bazel-compile-commands //...` |
| **Clean** | `bazel clean` |

Or use the terminal directly:

```bash
# Build and test
bazel build //...
bazel test //...

# AddressSanitizer (memory errors, use-after-free, leaks)
bazel test //... --config=asan

# ThreadSanitizer (data races)
bazel test //... --config=tsan

# Run benchmarks
bazel run //benchmarks:benchmarks
```

> **Note:** Never enable ASan and TSan together — they are incompatible.

---

## Project structure

```
.
├── .devcontainer/
│   ├── Dockerfile              # Ubuntu 24.04 + Clang 17 + full toolchain
│   ├── devcontainer.json       # VS Code container config + extensions
│   ├── init-zshrc.sh           # Copies ~/.zshrc from host (Mac/Linux/WSL)
│   └── install-caveman.sh      # Installs caveman Claude Code hooks
├── .vscode/
│   ├── tasks.json              # Bazel build/test/sanitizer tasks
│   ├── launch.json             # LLDB debug configurations
│   ├── extensions.json         # Recommended extensions
│   └── cpp.code-snippets       # C++ code snippets
├── benchmarks/
│   ├── BUILD                   # Bazel cc_binary benchmark target
│   └── bench_myproject.cpp     # Google Benchmark suite
├── src/
│   └── myproject/
│       ├── BUILD               # Bazel cc_library + cc_test
│       ├── myproject.h         # Public header
│       ├── myproject.cpp       # Implementation
│       └── myproject_test.cpp  # GoogleTest tests
├── .bazelignore
├── .bazelrc                    # C++20, -Wall/-Werror, asan/tsan configs
├── .clang-format               # Google C++ style
├── .clang-tidy                 # Google C++ linting rules
├── .clangd                     # clangd configuration
├── .gitignore
├── BUILD.bazel                 # Root Bazel package
├── CPPLINT.cfg                 # cpplint configuration
├── MODULE.bazel                # Bazel module deps (googletest, google_benchmark)
└── MODULE.bazel.lock
```
