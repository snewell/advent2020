#include <aoc/accounting.hpp>

#include <algorithm>
#include <cassert>
#include <stdexcept>

namespace aoc2020
{
    std::optional<int> calculate_product(std::vector<int>::const_iterator b,
                                         std::vector<int>::const_iterator e,
                                         int magic_value)
    {
        assert(std::distance(b, e) > 2);

        auto const first_end = e - 1;
        while(b != first_end)
        {
            auto const expected = magic_value - (*b);
            auto it = std::lower_bound(b, e, expected);
            if((it != e) && (*it == expected))
            {
                return std::make_optional((*b) * (*it));
            }
            e = it;
            ++b;
        }
        return std::nullopt;
    }
} // namespace aoc2020
