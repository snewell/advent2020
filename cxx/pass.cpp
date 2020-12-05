#include <aoc/pass.hpp>

#include <algorithm>
#include <cassert>
#include <string_view>

namespace
{

}

namespace aoc2020
{
    Seat parse_pass(std::string const & seat)
    {
        assert(seat.length() == 10);

        auto calculate_assignment = [](std::string_view info, int low, int high,
                                       char left, char right) {
            auto calculate_midpoint = [](int low, int high) {
                auto const distance = high - low + 1;
                return low + (distance / 2);
            };

            std::for_each(
                std::begin(info), std::end(info),
                [&low, &high, calculate_midpoint, left, right](auto ch) {
                    auto const new_boundary = calculate_midpoint(low, high);
                    if(ch == left)
                    {
                        high = new_boundary;
                    }
                    else
                    {
                        assert(ch == right);
                        low = new_boundary;
                    }
                });
            return low;
        };

        return Seat{calculate_assignment(std::string_view(seat.data(), 7), 0,
                                         127, 'F', 'B'),
                    calculate_assignment(std::string_view(seat.data() + 7, 3),
                                         0, 8, 'L', 'R')};
    }

    int calculate_id(Seat const & seat) noexcept
    {
        return (seat.row * 8) + seat.column;
    }
} // namespace aoc2020
