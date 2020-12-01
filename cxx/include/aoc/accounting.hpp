#ifndef AOC_ACCOUNTINT_HPP
#define AOC_ACCOUNTING_HPP 1

#include <optional>
#include <vector>

namespace aoc2020
{
    std::optional<int> calculate_product(std::vector<int>::const_iterator b,
                                         std::vector<int>::const_iterator e,
                                         int magic_value);
}

#endif
