#include <aoc/baggage.hpp>

#include <sstream>

#include <gtest/gtest.h>

/*
light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
 */

TEST(Baggage, one_line)
{
    std::istringstream input{
        "light red bags contain 1 bright white bag, 2 muted yellow bags."};

    auto const bag_info = aoc2020::parse_baggage(input);

    ASSERT_EQ(2, bag_info.carried_by.size());
    ASSERT_EQ(1, bag_info.carries.size());
}
