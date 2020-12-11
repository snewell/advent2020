#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>

#include <aoc/seatmap.hpp>

namespace
{
    int do_work(std::istream & input)
    {
        auto current_map = aoc2020::read_seat_map(input);
        auto next_map = aoc2020::run_cycle(
            current_map, &aoc2020::SeatMap::get_occupied_neighbors, 4);
        while(current_map != next_map)
        {
            aoc2020::run_cycle(next_map, current_map,
                               &aoc2020::SeatMap::get_occupied_neighbors, 4);
            std::swap(next_map, current_map);
        }
        return std::count_if(std::begin(current_map.seats),
                             std::end(current_map.seats),
                             [](auto seat) { return seat == '#'; });
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
