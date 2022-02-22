#include "../src/main.h"
#include "gtest/gtest.h"

TEST(TestMain, TestAdd)
{
    EXPECT_EQ(2, add(1, 1));
}

