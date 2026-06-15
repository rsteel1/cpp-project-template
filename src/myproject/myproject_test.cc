#include <catch2/catch_test_macros.hpp>

#include "myproject/myproject.h"

// Example tests — replace with your own

TEST_CASE("hello returns expected string", "[myproject]") {
  REQUIRE(myproject::hello() == "hello from myproject");
}

// Catch2 quick-reference:
//
//  REQUIRE(expr)          — fails and stops the test
//  CHECK(expr)            — fails but continues the test
//  REQUIRE_THROWS_AS(expr, ExceptionType)
//  REQUIRE_NOTHROW(expr)
//
//  SECTION("name") { }   — sub-cases sharing setup from outer scope
//
//  TEST_CASE("name", "[tag1][tag2]")
//    Run only tagged tests:  ./tests "[tag1]"
