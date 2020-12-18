#include <aoc/math.hpp>

#include <sstream>

#include <gtest/gtest.h>

TEST(LRMath, extract_simple)
{
    std::istringstream input{"4"};

    auto value = aoc2020::extract_value(input);
    ASSERT_EQ(4, value);
}

TEST(LRMath, extract_parens)
{
    std::istringstream input{"(4 + 2)"};

    auto value = aoc2020::extract_value(input);
    ASSERT_EQ(6, value);
}

TEST(LRMath, extract_nested)
{
    std::istringstream input{"((4 + 2))"};

    auto value = aoc2020::extract_value(input);
    ASSERT_EQ(6, value);
}
