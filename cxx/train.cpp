#include <aoc/train.hpp>

#include <iostream>
#include <regex>
#include <sstream>

namespace aoc2020
{
    Field parse_field(std::string const & input)
    {
        static std::regex const name_pattern("^(.*): ");
        static std::regex const range_pattern("(\\d+)-(\\d+)(?: or )?");

        Field ret;
        std::smatch group_info;
        auto match = std::regex_search(input, group_info, name_pattern);
        if(match)
        {
            ret.name = group_info[1];
            auto remaining = group_info.suffix().str();
            match = std::regex_search(remaining, group_info, range_pattern);
            while(match)
            {
                auto first = std::stoi(group_info[1]);
                auto second = std::stoi(group_info[2]);
                ret.ranges.push_back(std::make_pair(first, second));
                auto remaining = group_info.suffix().str();
                match = std::regex_search(remaining, group_info, range_pattern);
            }
        }
        return ret;
    }

    Ticket parse_ticket(std::string const & input)
    {
        std::istringstream helper(input);

        Ticket ret;
        int value;
        while(helper >> value)
        {
            ret.push_back(value);
            helper.get();
        }
        return ret;
    }
} // namespace aoc2020
