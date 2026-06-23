load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "myproject_lib",
    srcs = ["myproject.cpp"],
    hdrs = ["myproject.h"],
    strip_include_prefix = "/src",
    visibility = ["//visibility:public"],
)

cc_test(
    name = "tests",
    srcs = ["myproject_test.cpp"],
    deps = [
        ":myproject_lib",
        "@googletest//:gtest_main",
    ],
)
