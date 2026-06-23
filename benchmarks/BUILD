load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "benchmarks",
    srcs = ["bench_myproject.cpp"],
    deps = [
        "//src/myproject:myproject_lib",
        "@google_benchmark//:benchmark_main",
    ],
)
