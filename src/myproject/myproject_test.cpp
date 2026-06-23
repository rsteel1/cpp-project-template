#include <gtest/gtest.h>

#include "myproject/myproject.h"

// Example tests — replace with your own

TEST(MyprojectTest, HelloReturnsExpectedString) {
  EXPECT_EQ(myproject::hello(), "hello from myproject");
}

// GTest quick-reference:
//
//  EXPECT_EQ(a, b)          — fails but continues
//  ASSERT_EQ(a, b)          — fails and stops test
//  EXPECT_TRUE(expr)
//  EXPECT_THROW(expr, Type)
//
//  TEST(SuiteName, TestName) { }
//  TEST_F(FixtureClass, TestName) { }  — uses SetUp/TearDown
//    Run filtered:  bazel test //... --test_arg=--gtest_filter=SuiteName*
