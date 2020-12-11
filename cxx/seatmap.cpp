#include <aoc/seatmap.hpp>

#include <cassert>
#include <functional>

namespace aoc2020
{
    SeatMap read_seat_map(std::istream & input)
    {
        std::string line;
        std::getline(input, line);

        SeatMap ret;
        ret.seats = line;
        ret.row_length = line.size();
        ret.row_count = 1;
        while(std::getline(input, line))
        {
            assert(line.size() == ret.row_length);
            ret.seats += line;
            ++ret.row_count;
        }
        assert(ret.seats.size() == (ret.row_length * ret.row_count));
        return ret;
    }

    SeatNeighbors SeatMap::get_neighbor_info(std::size_t row,
                                             std::size_t col) const noexcept
    {
        SeatNeighbors ret{0, 0};

        auto adjust_correct = [&ret](auto seat) {
            if(seat == '#')
            {
                ++ret.occupied;
            }
            else
            {
                ++ret.available;
            }
        };

        auto get_seat = [this](auto row, auto col) {
            return seats[(row * row_length) + col];
        };

        if(row != 0)
        {
            // we're not at the top
            if(col != 0)
            {
                // we're not at the far left
                adjust_correct(get_seat(row - 1, col - 1));
            }
            adjust_correct(get_seat(row - 1, col));
            if(col != (row_length - 1))
            {
                // we're not at the far left
                adjust_correct(get_seat(row - 1, col + 1));
            }
        }
        if(col != 0)
        {
            // we're not at the far left
            adjust_correct(get_seat(row, col - 1));
        }
        if(col != (row_length - 1))
        {
            // we're not at the far left
            adjust_correct(get_seat(row, col + 1));
        }
        if(row != (row_count - 1))
        {
            // we're not at the bottom
            if(col != 0)
            {
                // we're not at the far left
                adjust_correct(get_seat(row + 1, col - 1));
            }
            adjust_correct(get_seat(row + 1, col));
            if(col != (row_length - 1))
            {
                // we're not at the far left
                adjust_correct(get_seat(row + 1, col + 1));
            }
        }
        return ret;
    }

    SeatMap run_cycle(SeatMap const & previous,
                      SeatNeighbors (SeatMap::*lookup_fn)(std::size_t,
                                                          std::size_t) const,
                      std::size_t tolerance)
    {
        auto ret = previous;
        for(decltype(ret.row_count) row = 0; row < ret.row_count; ++row)
        {
            for(decltype(ret.row_length) col = 0; col < ret.row_length; ++col)
            {
                auto & seat = ret.seats[(row * ret.row_length) + col];
                if(seat != '.')
                {
                    auto const neighbors =
                        std::invoke(lookup_fn, previous, row, col);
                    if(seat == 'L')
                    {
                        if(neighbors.occupied == 0)
                        {
                            seat = '#';
                        }
                    }
                    else
                    {
                        assert(seat == '#');
                        if(neighbors.occupied >= tolerance)
                        {
                            seat = 'L';
                        }
                    }
                }
            }
        }
        return ret;
    }

    bool operator==(SeatMap const & lhs, SeatMap const & rhs) noexcept
    {
        assert(lhs.row_count == rhs.row_count);
        assert(lhs.row_length == rhs.row_length);
        return lhs.seats == rhs.seats;
    }

    bool operator!=(SeatMap const & lhs, SeatMap const & rhs) noexcept
    {
        assert(lhs.row_count == rhs.row_count);
        assert(lhs.row_length == rhs.row_length);
        return lhs.seats != rhs.seats;
    }
} // namespace aoc2020
