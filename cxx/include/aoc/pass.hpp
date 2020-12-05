#ifndef AOC_PASS_HPP
#define AOC_PASS_HPP 1

#include <string>

namespace aoc2020
{
    struct Seat
    {
        int row;
        int column;
    };

    Seat parse_pass(std::string const & seat);

    int calculate_id(Seat const & seat) noexcept;
} // namespace aoc2020

#endif
