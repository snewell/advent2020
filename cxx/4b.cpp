#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>

namespace
{
    bool validate_range(std::string const & value, int min, int max)
    {
        static std::regex const value_regex("^(\\d+)$");
        auto match = std::regex_search(value, value_regex);
        if(match)
        {
            auto const int_value = std::stoi(value);
            return ((min <= int_value) && (int_value <= max));
        }
        return false;
    }

    bool validate_height(std::string const & value)
    {
        static std::regex const value_regex("^(\\d+)(in|cm)$");

        std::smatch groups;
        auto match = std::regex_search(value, groups, value_regex);
        if(match)
        {
            static std::map<std::string, std::pair<int, int>> const
                height_ranges = {std::make_pair("cm", std::make_pair(150, 193)),
                                 std::make_pair("in", std::make_pair(59, 76))};

            auto it = height_ranges.find(groups[2]);
            if(it != height_ranges.end())
            {
                return validate_range(groups[1], it->second.first,
                                      it->second.second);
            }
        }
        return false;
    }

    bool validate_hair_color(std::string const & value)
    {
        static std::regex const value_regex("^#[a-f0-9]{6}$");
        return std::regex_match(value, value_regex);
    }

    bool validate_eye_color(std::string const & value)
    {
        std::set<std::string> const valid_colors = {"amb", "blu", "brn", "gry",
                                                    "grn", "hzl", "oth"};

        auto it = valid_colors.find(value);
        return (it != valid_colors.end());
    }

    bool validate_passport_id(std::string const & value)
    {
        static std::regex const value_regex("^\\d{9}$");
        return std::regex_match(value, value_regex);
    }

    bool is_valid(std::map<std::string, std::string> const & passport)
    {
        static std::pair<std::string,
                         std::function<bool(std::string const &)>> const
            required[] = {
                std::make_pair("byr",
                               [](auto const & value) {
                                   return validate_range(value, 1920, 2002);
                               }),
                std::make_pair("iyr",
                               [](auto const & value) {
                                   return validate_range(value, 2010, 2020);
                               }),
                std::make_pair("eyr",
                               [](auto const & value) {
                                   return validate_range(value, 2020, 2030);
                               }),
                std::make_pair("hgt", validate_height),
                std::make_pair("hcl", validate_hair_color),
                std::make_pair("ecl", validate_eye_color),
                std::make_pair("pid", validate_passport_id)};
        for(auto const & field : required)
        {
            auto const it = passport.find(field.first);
            if(it == std::end(passport))
            {
                return false;
            }
            else
            {
                if(!field.second(it->second))
                {
                    return false;
                }
            }
        }
        return true;
    }

    auto do_work(std::istream & istream)
    {
        static std::regex const key_regex("([a-z]+):");
        auto count = 0;
        std::string line;
        std::map<std::string, std::string> passport;
        while(std::getline(istream, line))
        {
            if(line.empty())
            {
                if(is_valid(passport))
                {
                    ++count;
                }
                passport.clear();
            }
            else
            {
                std::smatch groups;
                auto match = std::regex_search(line, groups, key_regex);
                while(match)
                {
                    auto const key = groups[1].str();
                    line = groups.suffix().str();
                    auto const value = line.substr(0, line.find(' '));
                    // std::cout << key << " -> " << value << " (" << line <<
                    // ")\n";
                    passport.insert(std::make_pair(key, value));
                    match = std::regex_search(line, groups, key_regex);
                }
            }
        }
        if(is_valid(passport))
        {
            ++count;
        }
        return count;
    }
} // namespace

int main(int argc, char ** argv)
{
    auto total = [argc, argv]() {
        if(argc == 1)
        {
            return do_work(std::cin);
        }
        else
        {
            std::ifstream input{argv[1]};
            return do_work(input);
        }
    }();
    std::cout << total << '\n';
    return 0;
}
