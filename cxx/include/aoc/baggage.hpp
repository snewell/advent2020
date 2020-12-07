#ifndef AOC_BAGGAGE_HPP
#define AOC_BAGGAGE_HPP 1

#include <istream>
#include <map>
#include <set>
#include <string>

namespace aoc2020
{
    struct NestedBags
    {
        std::map<std::string, std::set<std::string>> carried_by;
        std::map<std::string, std::map<std::string, int>> carries;
    };

    NestedBags parse_baggage(std::istream & istream);
} // namespace aoc2020

#endif
