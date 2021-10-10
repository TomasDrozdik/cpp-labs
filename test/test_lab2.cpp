#include <gtest/gtest.h>

#include "lab2/foo.h"

TEST(TestFoo, Correctness) {
    EXPECT_EQ(foo(), 42);
}