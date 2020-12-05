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
        std::string line;
        std::vector<int> known_seats;
        while(std::getline(istream, line))
        {
            auto const seat = aoc2020::parse_pass(line);
            auto const seat_id = aoc2020::calculate_id(seat);
            auto const insert_pos = std::lower_bound(std::begin(known_seats), std::end(known_seats), seat_id);
            known_seats.insert(insert_pos, seat_id);
        }
        auto const missing_seat = std::adjacent_find(std::begin(known_seats), std::end(known_seats), [](auto first, auto second) {
            return (first + 1) != second;
        });
        return (*missing_seat) + 1;
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
