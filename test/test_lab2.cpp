#include <gtest/gtest.h>

#include "lab2/foo.h"

using namespace lab2;

TEST(TestFoo, Correctness) {
    EXPECT_EQ(foo(), 42);
}