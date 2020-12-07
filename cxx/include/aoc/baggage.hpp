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

        std::map<std::string, int> total_bags;
    };

    NestedBags parse_baggage(std::istream & istream);

    int calculate_total_bags(NestedBags & bag_info, std::string const & color);
} // namespace aoc2020

#endif
