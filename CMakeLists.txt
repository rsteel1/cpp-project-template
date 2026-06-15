cmake_minimum_required(VERSION 3.20)

# ─────────────────────────────────────────────────────────────
#  PROJECT
#  Rename "myproject" to your project name throughout this file
# ─────────────────────────────────────────────────────────────
project(myproject CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ─────────────────────────────────────────────────────────────
#  SANITISER OPTIONS
#  Never enable both at once — they are incompatible.
#
#  ASan  — memory errors, use-after-free, leaks
#    cmake -S . -B build-asan -DENABLE_ASAN=ON && cmake --build build-asan
#
#  TSan  — data races, lock-order violations
#    cmake -S . -B build-tsan -DENABLE_TSAN=ON && cmake --build build-tsan
# ─────────────────────────────────────────────────────────────
option(ENABLE_ASAN "Enable AddressSanitizer + UBSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer"                OFF)

include(cmake/sanitizers.cmake)

# ─────────────────────────────────────────────────────────────
#  DEPENDENCIES  (fetched automatically — no installs needed)
# ─────────────────────────────────────────────────────────────
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG        v1.8.3
)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(googlebenchmark)

# ─────────────────────────────────────────────────────────────
#  LIBRARY  (your implementation)
#
#  Header-only project?  Change STATIC → INTERFACE everywhere
#  below and remove src/myproject.cpp
# ─────────────────────────────────────────────────────────────
add_library(myproject_lib STATIC
    src/myproject.cpp
)

target_include_directories(myproject_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(myproject_lib PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Werror
)

apply_sanitizers(myproject_lib)

# ─────────────────────────────────────────────────────────────
#  TESTS
# ─────────────────────────────────────────────────────────────
enable_testing()

add_executable(tests
    tests/test_myproject.cpp
)

target_link_libraries(tests PRIVATE
    myproject_lib
    Catch2::Catch2WithMain
)

apply_sanitizers(tests)

include(CTest)
include(Catch)
catch_discover_tests(tests)

# ─────────────────────────────────────────────────────────────
#  BENCHMARKS
# ─────────────────────────────────────────────────────────────
add_executable(benchmarks
    benchmarks/bench_myproject.cpp
)

target_link_libraries(benchmarks PRIVATE
    myproject_lib
    benchmark::benchmark_main
)
