# C++ Project Template

A minimal C++20 project template with:
- **Clang 17** compiler (with GCC available as a secondary)
- **CMake + Ninja** build system
- **Catch2** for testing
- **Google Benchmark** for benchmarking
- **ASan / TSan** sanitiser support
- **clangd** for VSCode intellisense, go-to-definition, etc.
- **clang-format** and **clang-tidy** for code quality

---

## First-time setup

1. Install [Docker Desktop](https://www.docker.com/products/docker-desktop)
2. Install the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) VSCode extension
3. Clone this repo and open it in VSCode
4. When prompted, click **"Reopen in Container"** (or open the Command Palette → `Dev Containers: Reopen in Container`)
5. Wait for the container to build (~2–3 minutes first time, cached after that)

The `postCreateCommand` in `devcontainer.json` automatically runs `cmake` to configure the default debug build.

---

## Renaming for your project

1. Find and replace `myproject` with your project name throughout:
   - `CMakeLists.txt` — the `project()` call, library name, and target names
   - `include/myproject.hpp` → rename to `include/yourproject.hpp`
   - `src/myproject.cpp` → rename to `src/yourproject.cpp`
   - `tests/test_myproject.cpp` → rename to `tests/test_yourproject.cpp`
   - `benchmarks/bench_myproject.cpp` → rename to `benchmarks/bench_yourproject.cpp`
2. Delete this rename section from the README

---

## Building and testing

All of these are available from the VSCode Command Palette (`Cmd+Shift+P` → `Tasks: Run Task`):

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

# ThreadSanitizer (data races — use this on every concurrency project)
cmake -S . -B build-tsan -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_TSAN=ON
cmake --build build-tsan
cd build-tsan && ctest --output-on-failure
```

> **Note:** Never enable ASan and TSan together — they are incompatible.

---

## Header-only projects

For projects like a units library or TypeList where everything lives in headers:

1. Delete `src/myproject.cpp`
2. In `CMakeLists.txt`, change `STATIC` → `INTERFACE` on the `add_library` line
3. Change `PUBLIC` → `INTERFACE` on the `target_include_directories` line
4. Remove the `target_compile_options` block (INTERFACE targets can't have PRIVATE options)

---

## Project structure

```
.
├── .devcontainer/
│   ├── Dockerfile          # Ubuntu 24.04 + Clang 17 + CMake + Ninja
│   └── devcontainer.json   # VSCode container config + extensions
├── .vscode/
│   ├── tasks.json          # Build / test / sanitiser tasks
│   ├── launch.json         # Debug configurations
│   └── extensions.json     # Recommended extensions
├── cmake/
│   └── sanitizers.cmake    # ASan / TSan helper function
├── include/
│   └── myproject.hpp       # Your public header(s)
├── src/
│   └── myproject.cpp       # Your implementation
├── tests/
│   └── test_myproject.cpp  # Catch2 tests
├── benchmarks/
│   └── bench_myproject.cpp # Google Benchmark benchmarks
├── .clang-format           # Formatting rules
├── .clang-tidy             # Linting rules
├── .gitignore
└── CMakeLists.txt
```
