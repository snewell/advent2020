#include <aoc/baggage.hpp>

#include <algorithm>
#include <cassert>
#include <regex>

namespace aoc2020
{
    NestedBags parse_baggage(std::istream & input)
    {
        static std::regex const carries_pattern(" bags contain");
        static std::regex const carried_by_pattern(" (\\d+) ([a-z ]+) bag");

        NestedBags ret;

        std::string line;
        while(std::getline(input, line))
        {
            std::smatch groups;
            auto match = std::regex_search(line, groups, carries_pattern);
            assert(match);
            auto const outer_bag = groups.prefix().str();
            auto & carries_map = ret.carries[outer_bag];
            assert(carries_map.empty());

            line = groups.suffix().str();
            match = std::regex_search(line, groups, carried_by_pattern);
            while(match)
            {
                carries_map[groups[2]] = std::stoi(groups[1]);
                ret.carried_by[groups[2]].insert(outer_bag);
                line = groups.suffix().str();
                match = std::regex_search(line, groups, carried_by_pattern);
            }
        }
        return ret;
    }

    int calculate_total_bags(NestedBags & bag_info, std::string const & color)
    {
        auto total_count = bag_info.total_bags.find(color);
        if(total_count == std::end(bag_info.total_bags))
        {
            auto total = 0;
            auto carries_it = bag_info.carries.find(color);
            if(carries_it != std::end(bag_info.carries))
            {
                std::for_each(std::begin(carries_it->second),
                              std::end(carries_it->second),
                              [&bag_info, &total](auto const & carries_info) {
                                  total += carries_info.second *
                                           (calculate_total_bags(
                                                bag_info, carries_info.first) +
                                            1);
                              });
            }

            bag_info.total_bags[color] = total;
            return total;
        }
        return total_count->second;
    }
} // namespace aoc2020
