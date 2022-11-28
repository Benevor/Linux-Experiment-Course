#include <limits.h>
#include "../MyProject/my_math.h"
#include "gtest/gtest.h" //包含头文件

namespace
{

    // 测试负数的阶乘.
    TEST(FactorialTest, Negative)
    {
        EXPECT_EQ(1, Factorial(-5));
        EXPECT_EQ(1, Factorial(0));
        EXPECT_GT(Factorial(-10), 0);
    }

    // 测试正数的阶乘
    TEST(FactorialTest, Positive)
    {
        EXPECT_EQ(1, Factorial(1));
        EXPECT_EQ(2, Factorial(2));
        EXPECT_EQ(6, Factorial(3));
        EXPECT_EQ(40320, Factorial(8));
    }

    // 测试负数是否为质数
    TEST(IsPrimeTest, Negative)
    {
        EXPECT_FALSE(IsPrime(-1));
        EXPECT_FALSE(IsPrime(-2));
        EXPECT_FALSE(IsPrime(INT_MIN));
    }

    // 测试正数是否为质数
    TEST(IsPrimeTest, Positive)
    {
        EXPECT_FALSE(IsPrime(4));
        EXPECT_TRUE(IsPrime(5));
        EXPECT_FALSE(IsPrime(6));
        EXPECT_TRUE(IsPrime(23));
    }
} // namespace
