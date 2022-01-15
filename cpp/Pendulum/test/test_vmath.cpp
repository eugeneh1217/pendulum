#include "gtest/gtest.h"

#include "vmath.h"

#include<vector>

TEST(TestVmath, TestVectorSum)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    std::vector<int> right{ 2, 4, 6, 8 , 10 };
    std::vector<double> expected{ 2, 5, 8, 11, 14 };
    EXPECT_TRUE(vmath::VectorSum(left, right) == expected);
}

TEST(TestVmath, TestScalarSum)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    int right = 1;
    std::vector<double> expected{ 1, 2, 3, 4, 5 };
    EXPECT_TRUE(vmath::ScalarSum(left, right) == expected);
}

TEST(TestVmath, TestVectorDifference)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    std::vector<int> right{ 2, 4, 6, 8 , 10 };
    std::vector<double> expected{ -2, -3, -4, -5, -6 };
    EXPECT_TRUE(vmath::VectorDiff(left, right) == expected);
}

TEST(TestVmath, TestScalarDifference)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    int right = 1;
    std::vector<double> expected{ -1, 0, 1, 2, 3};
    EXPECT_TRUE(vmath::ScalarDiff(left, right) == expected);
}

TEST(TestVmath, TestVectorProduct)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    std::vector<int> right{ 2, 4, 6, 8 , 10 };
    std::vector<double> expected{ 0, 4, 12, 24, 40 };
    EXPECT_TRUE(vmath::VectorProd(left, right) == expected);
}

TEST(TestVmath, TestScalarProduct)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    int right = 2;
    std::vector<double> expected{ 0, 2, 4, 6, 8};
    EXPECT_TRUE(vmath::ScalarProd(left, right) == expected);
}

TEST(TestVmath, TestVectorQuotient)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    std::vector<int> right{ 2, 4, 6, 8 , 10 };
    std::vector<double> expected{ 0, 1./4, 2./6, 3./8, 4./10 };
    EXPECT_TRUE(vmath::VectorQuot(left, right) == expected);
}

TEST(TestVmath, TestScalarQuotient)
{
    std::vector<double> left{ 0, 1, 2, 3 , 4 };
    int right = 2;
    std::vector<double> expected{ 0, 1./2, 2./2, 3./2, 4./2};
    EXPECT_TRUE(vmath::ScalarQuot(left, right) == expected);
}

TEST(TestVmath, TestNestedVectorMath)
{
    std::vector<double> first{ 1, -2, 0 };
    std::vector<int> second{ 8, 2, 1 };
    std::vector<double> third{ 1, -5, 9 };
    std::vector<double> fourth{ 1, 2, 3 };
    std::vector<double> result = vmath::VectorSum(
        vmath::VectorProd(first, second),
        vmath::VectorQuot(third, fourth)
    );
    std::vector<double> expected{9, -13.0/2, 3};
    EXPECT_TRUE(result == expected);
}