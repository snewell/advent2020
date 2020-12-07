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

TEST(Baggage, parse_one_line)
{
    std::istringstream input{
        "light red bags contain 1 bright white bag, 2 muted yellow bags."};

    auto const bag_info = aoc2020::parse_baggage(input);

    ASSERT_EQ(2, bag_info.carried_by.size());
    ASSERT_EQ(1, bag_info.carries.size());
}

TEST(Baggage, count_total_bags)
{
    std::istringstream input{
        "vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.\n"
        "faded blue bags contain no other bags.\n"
        "dotted black bags contain no other bags."};

    auto bag_info = aoc2020::parse_baggage(input);

    std::pair<std::string, int> const expected_totals[] = {
        std::make_pair("vibrant plum", 11),
        std::make_pair("faded blue", 0),
        std::make_pair("dotted black", 0),
    };

    for(auto const & expected : expected_totals)
    {
        auto const total =
            aoc2020::calculate_total_bags(bag_info, expected.first);
        ASSERT_EQ(expected.second, total);
    }
}
