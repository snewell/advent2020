#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>

#include <aoc/seatmap.hpp>

namespace
{
#if 0
    void write(aoc2020::SeatMap const &seat_map) {
        for(std::size_t i = 0; i < seat_map.row_count; ++i) {
            std::cout.write(seat_map.seats.data() + (seat_map.row_length * i), seat_map.row_length);
            std::cout << '\n';
        }
    }
#endif
    int do_work(std::istream & input)
    {
        auto current_map = aoc2020::read_seat_map(input);
        auto next_map = aoc2020::run_cycle(
            current_map, &aoc2020::SeatMap::get_angle_info, 5);
        while(current_map != next_map)
        {
#if 0
            std::cout << "     CURRENT\n";
            std::cout << "-----------------\n";
            write(current_map);
            std::cout << "\n\n";
#endif
            aoc2020::run_cycle(next_map, current_map,
                               &aoc2020::SeatMap::get_angle_info, 5);
            std::swap(next_map, current_map);
        }
        return std::count_if(std::begin(current_map.seats),
                             std::end(current_map.seats),
                             [](auto seat) { return seat == '#'; });
        return 0;
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
