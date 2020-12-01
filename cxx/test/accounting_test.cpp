#include <aoc/accounting.hpp>

#include <gtest/gtest.h>

TEST(Accounting, bounds_check)
{
    std::vector<int> values = {0, 10};
    auto result =
        aoc2020::calculate_product(std::begin(values), std::end(values), 10);

    ASSERT_TRUE(result);
    ASSERT_EQ(0, *result);
}

TEST(Accounting, trim_outer)
{
    std::vector<int> values = {1, 2, 8, 10};
    auto result =
        aoc2020::calculate_product(std::begin(values), std::end(values), 10);

    ASSERT_TRUE(result);
    ASSERT_EQ(16, *result);
}
