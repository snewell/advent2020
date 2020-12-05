#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include <aoc/pass.hpp>

namespace
{
    auto do_work(std::istream & istream)
    {
        auto highest = std::numeric_limits<int>::min();
        std::string line;
        while(std::getline(istream, line))
        {
            auto const seat = aoc2020::parse_pass(line);
            auto const seat_id = aoc2020::calculate_id(seat);
            highest = std::max(highest, seat_id);
        }
        return highest;
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
