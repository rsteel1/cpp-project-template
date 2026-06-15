#include <benchmark/benchmark.h>
#include "myproject.hpp"

// ─────────────────────────────────────────────────────────────
//  Example benchmark — replace with your own
// ─────────────────────────────────────────────────────────────

static void BM_Hello(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(myproject::hello());
    }
}
BENCHMARK(BM_Hello);

// Google Benchmark quick-reference:
//
//  benchmark::DoNotOptimize(val)  — prevents the compiler optimising away your work
//  benchmark::ClobberMemory()     — forces memory to be flushed (use after DoNotOptimize)
//  state.SetBytesProcessed(...)   — report throughput in benchmark output
//
//  Run:            ./benchmarks
//  Filter:         ./benchmarks --benchmark_filter=BM_Hello
//  Output as JSON: ./benchmarks --benchmark_out=results.json --benchmark_out_format=json
