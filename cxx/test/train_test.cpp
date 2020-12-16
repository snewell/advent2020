#include <aoc/train.hpp>

#include <gtest/gtest.h>

TEST(Train, parse_field)
{
    auto const field =
        aoc2020::parse_field("departure location: 30-828 or 839-971");

    ASSERT_EQ("departure location", field.name);
    ASSERT_EQ(2, field.ranges.size());
    ASSERT_EQ(30, field.ranges[0].first);
    ASSERT_EQ(828, field.ranges[0].second);
    ASSERT_EQ(839, field.ranges[1].first);
    ASSERT_EQ(971, field.ranges[1].second);
}

TEST(Train, parse_ticket)
{
    auto const ticket =
        aoc2020::parse_ticket("475,649,830,432,685,476,743,278,558,283,496,337,"
                              "83,313,153,139,405,522,648,894");

    ASSERT_EQ(20, ticket.size());
}
