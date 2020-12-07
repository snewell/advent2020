#include <aoc/baggage.hpp>

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
} // namespace aoc2020
