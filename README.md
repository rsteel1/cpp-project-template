# C++ Project Template

A minimal C++20 project template following the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html).

**Toolchain:**
- **Clang 17** (compiler, clangd, clang-format, clang-tidy) + GCC as secondary
- **CMake + Ninja** build system
- **Catch2** for testing
- **Google Benchmark** for benchmarking
- **ASan / TSan** sanitiser support
- **cpplint** for Google style checking

**Dev environment (devcontainer):**
- Ubuntu 24.04 with zsh + oh-my-zsh
- `gh` CLI (auth carried from host `~/.config/gh`)
- `claude` CLI (auth via `ANTHROPIC_API_KEY` env var)
- SSH keys, gitconfig, and `~/.zshrc` mounted from host

---

## First-time setup

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop)
2. Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) VSCode extension
3. Add to your host `~/.zshrc`:
   ```zsh
   export ANTHROPIC_API_KEY="sk-ant-..."
   ```
4. Clone this repo and open it in VSCode
5. When prompted, click **"Reopen in Container"** (or Command Palette → `Dev Containers: Reopen in Container`)
6. Wait for the container to build (~2–3 minutes first time, cached after)

The `postCreateCommand` automatically runs `cmake` to configure the default debug build.

---

## Adapting for your project

1. Rename `myproject` throughout:
   - `CMakeLists.txt` — `project()`, library name, target names
   - `src/myproject/` → `src/yourproject/`
   - `src/myproject/myproject.h` → `src/yourproject/yourproject.h`
   - `src/myproject/myproject.cc` → `src/yourproject/yourproject.cc`
   - `src/myproject/myproject_test.cc` → `src/yourproject/yourproject_test.cc`
   - `benchmarks/bench_myproject.cc` → `benchmarks/bench_yourproject.cc`
2. Update the header guard in `yourproject.h`:
   `#ifndef YOURPROJECT_YOURPROJECT_H_`
3. Delete this section from the README

---

## Building and testing

Available from the VSCode Command Palette (`Cmd+Shift+P` → `Tasks: Run Task`):

| Task | What it does |
|---|---|
| **Build** | Configures (if needed) and builds the default debug build |
| **Run Tests** | Builds and runs all Catch2 tests |
| **Run Benchmarks** | Builds and runs Google Benchmark suite |
| **Run Tests (ASan)** | Builds with AddressSanitizer + UBSan and runs tests |
| **Run Tests (TSan)** | Builds with ThreadSanitizer and runs tests |
| **Clean All Builds** | Removes all build directories |

Or use the terminal directly:

```bash
# Standard debug build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cd build && ctest --output-on-failure

# AddressSanitizer (memory errors, use-after-free, leaks)
cmake -S . -B build-asan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_ASAN=ON
cmake --build build-asan
cd build-asan && ctest --output-on-failure

# ThreadSanitizer (data races)
cmake -S . -B build-tsan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_TSAN=ON
cmake --build build-tsan
cd build-tsan && ctest --output-on-failure
```

> **Note:** Never enable ASan and TSan together — they are incompatible.

---

## Header-only projects

For projects where everything lives in headers (e.g. a units library, TypeList):

1. Delete `src/myproject/myproject.cc`
2. In `CMakeLists.txt`, change `STATIC` → `INTERFACE` on `add_library`
3. Change `PUBLIC` → `INTERFACE` on `target_include_directories`
4. Remove the `target_compile_options` block (INTERFACE targets can't have PRIVATE options)

---

## Project structure

```
.
├── .devcontainer/
│   ├── Dockerfile              # Ubuntu 24.04 + Clang 17 + toolchain
│   ├── devcontainer.json       # VSCode container config + extensions
│   ├── init-zshrc.sh           # Copies ~/.zshrc from host (Mac/Linux/WSL)
│   └── .zshrc.baseline         # Fallback zshrc (agnoster theme, git plugin)
├── .vscode/
│   ├── tasks.json              # Build / test / sanitiser tasks
│   ├── launch.json             # Debug configurations
│   └── extensions.json         # Recommended extensions
├── cmake/
│   └── sanitizers.cmake        # ASan / TSan helper
├── src/
│   └── myproject/
│       ├── myproject.h         # Public header (include as "myproject/myproject.h")
│       ├── myproject.cc        # Implementation
│       └── myproject_test.cc   # Catch2 tests
├── benchmarks/
│   └── bench_myproject.cc      # Google Benchmark benchmarks
├── .clang-format               # Google C++ style formatting
├── .clang-tidy                 # Google C++ style linting
├── CPPLINT.cfg                 # cpplint configuration
├── .gitignore
└── CMakeLists.txt
```
