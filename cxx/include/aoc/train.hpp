#ifndef AOC_TRAIN_HPP
#define AOC_TRAIN_HPP 1

#include <istream>
#include <vector>

namespace aoc2020
{
    struct Field
    {
        std::string name;
        std::vector<std::pair<int, int>> ranges;
    };

    using Ticket = std::vector<int>;

    struct TicketSet
    {
        std::vector<Field> fields;
        std::vector<Ticket> tickets;
    };

    Field parse_field(std::string const & input);

    Ticket parse_ticket(std::string const & input);
} // namespace aoc2020

#endif
