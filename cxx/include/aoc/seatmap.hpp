#ifndef AOC_SEATMAP_HPP
#define AOC_SEATMAP_HPP 1

#include <istream>
#include <string>

namespace aoc2020
{
    struct SeatNeighbors
    {
        std::size_t occupied;
        std::size_t available;
    };

    struct SeatMap
    {
        SeatNeighbors get_neighbor_info(std::size_t row, std::size_t col) const
            noexcept;

        SeatNeighbors get_angle_info(std::size_t row, std::size_t col) const
            noexcept;

        friend bool operator==(SeatMap const & lhs,
                               SeatMap const & rhs) noexcept;

        friend bool operator!=(SeatMap const & lhs,
                               SeatMap const & rhs) noexcept;

        std::string seats;
        std::size_t row_count;
        std::size_t row_length;
    };

    SeatMap read_seat_map(std::istream & input);

    SeatMap run_cycle(SeatMap const & previous,
                      SeatNeighbors (SeatMap::*lookup_fn)(std::size_t,
                                                          std::size_t) const,
                      std::size_t tolerance);
} // namespace aoc2020

#endif
