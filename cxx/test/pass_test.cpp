#include <aoc/pass.hpp>

#include <gtest/gtest.h>

/*

    BFFFBBFRRR: row 70, column 7, seat ID 567.
    FFFBBBFRRR: row 14, column 7, seat ID 119.
    BBFFBBFRLL: row 102, column 4, seat ID 820.

 */

TEST(Pass, example1)
{
    auto const seat = aoc2020::parse_pass("BFFFBBFRRR");

    ASSERT_EQ(70, seat.row);
    ASSERT_EQ(7, seat.column);
    ASSERT_EQ(567, aoc2020::calculate_id(seat));
}

TEST(Pass, example2)
{
    auto const seat = aoc2020::parse_pass("FFFBBBFRRR");

    ASSERT_EQ(14, seat.row);
    ASSERT_EQ(7, seat.column);
    ASSERT_EQ(119, aoc2020::calculate_id(seat));
}

TEST(Pass, example3)
{
    auto const seat = aoc2020::parse_pass("BBFFBBFRLL");

    ASSERT_EQ(102, seat.row);
    ASSERT_EQ(4, seat.column);
    ASSERT_EQ(820, aoc2020::calculate_id(seat));
}
