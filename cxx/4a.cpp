#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>

namespace
{
    bool is_valid(std::set<std::string> const & passport)
    {
        static std::string const required[] = {"byr", "iyr", "eyr", "hgt",
                                               "hcl", "ecl", "pid"};
        for(auto const & key : required)
        {
            auto const it = passport.find(key);
            if(it == std::end(passport))
            {
                return false;
            }
        }
        return true;
    }

    auto do_work(std::istream & istream)
    {
        static std::regex const key_regex("([a-z]+):");
        auto count = 0;
        std::string line;
        std::set<std::string> passport;
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
                    passport.insert(groups[1]);
                    line = groups.suffix().str();
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
