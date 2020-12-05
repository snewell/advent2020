#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include <aoc/pass.hpp>

namespace
{
    auto find_missing(std::vector<int> const & known_seats)
    {
        auto low = std::begin(known_seats);
        auto high = std::end(known_seats);
        auto range = std::distance(low, high);

        while(range > 2)
        {
            auto const midpoint_distance = range / 2;
            auto const expected_id = *low + midpoint_distance;
            auto const midpoint = std::next(low, midpoint_distance);

            if(*midpoint == expected_id)
            {
                // nothing missing between low and high, so search upper half
                low = midpoint;
            }
            else
            {
                // something missing, search lower half
                high = midpoint;
            }
            range = std::distance(low, high);
        }
        return *low + 1;
    }

    auto do_work(std::istream & istream)
    {
        std::string line;
        std::vector<int> known_seats;
        while(std::getline(istream, line))
        {
            auto const seat = aoc2020::parse_pass(line);
            auto const seat_id = aoc2020::calculate_id(seat);
            auto const insert_pos = std::lower_bound(
                std::begin(known_seats), std::end(known_seats), seat_id);
            known_seats.insert(insert_pos, seat_id);
        }
        auto missing_seat = find_missing(known_seats);
        return missing_seat;
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
