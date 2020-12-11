#ifndef AOC_SEATMAP_HPP
#define AOC_SEATMAP_HPP 1

#include <istream>
#include <string>

namespace aoc2020
{
    struct SeatMap
    {
        std::size_t get_occupied_neighbors(std::size_t row,
                                           std::size_t col) const noexcept;

        std::size_t get_occupied_angles(std::size_t row, std::size_t col) const
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
                      std::size_t (SeatMap::*lookup_fn)(std::size_t,
                                                        std::size_t) const,
                      std::size_t tolerance);

    void run_cycle(SeatMap const & previous, SeatMap & output,
                   std::size_t (SeatMap::*lookup_fn)(std::size_t, std::size_t)
                       const,
                   std::size_t tolerance);
} // namespace aoc2020

#endif
