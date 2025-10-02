#include <gtest/gtest.h>
#include <calculator/calculator.hpp>

TEST(HelloTest, BasicAssertions)
{
    // Expect two strings to be equal.
    EXPECT_STREQ("hello", "hello");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(SimpleOperators, TwoNumbers)
{
    Calculator calc{};
    auto res1 = calc.solve(" 2 + 6");
    EXPECT_EQ(res1, 8);
    auto res2 = calc.solve(" 5 - 8");
    EXPECT_EQ(res2, -3);
    auto res3 = calc.solve(" 6 * 7");
    EXPECT_EQ(res3, 42);
    auto res4 = calc.solve(" 63 / 9");
    EXPECT_EQ(res4, 7);
}

TEST(SimpleOperators, MoreNumbers)
{
    Calculator calc{};
    auto res1 = calc.solve(" 2 + 6 * 3 - 7");
    EXPECT_EQ(res1, 13);
    auto res2 = calc.solve(" 5  * 8+ 4 - 3 - 10");
    EXPECT_EQ(res2, 31);
    auto res3 = calc.solve(" 6 / 2 + 8 * 3");
    EXPECT_EQ(res3, 27);
    auto res4 = calc.solve(" 10 + 63 / 9 - 5");
    EXPECT_EQ(res4, 12);
}
