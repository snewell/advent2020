#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

#include <aoc/train.hpp>

namespace
{
    auto check_field_ranges(int value, aoc2020::Field const & field)
    {
        auto const fits_range = std::find_if(
            std::begin(field.ranges), std::end(field.ranges),
            [value](auto range) {
                return (value >= range.first) && (value <= range.second);
            });
        return fits_range != std::end(field.ranges);
    }

    auto do_work(std::istream & input)
    {
        std::string line;

        aoc2020::Fields fields;
        [&line, &input, &fields]() {
            while(std::getline(input, line) && !line.empty())
            {
                fields.push_back(aoc2020::parse_field(line));
            }
        }();

        // read everything until the generic tickets
        std::getline(input, line);
        assert(line.back() == ':');
        std::getline(input, line); // ticket
        std::getline(input, line);
        assert(line.empty());
        std::getline(input, line);
        assert(line.back() == ':');

        auto error_rate = 0;
        [&line, &input, &fields, &error_rate]() {
            while(std::getline(input, line))
            {
                auto const ticket = aoc2020::parse_ticket(line);
                std::for_each(std::begin(ticket), std::end(ticket),
                              [&fields, &error_rate](auto value) {
                                  auto const valid_field = std::find_if(
                                      std::begin(fields), std::end(fields),
                                      [value](auto const & field) {
                                          return check_field_ranges(value,
                                                                    field);
                                      });
                                  if(valid_field == std::end(fields))
                                  {
                                      error_rate += value;
                                  }
                              });
            }
        }();

        return error_rate;
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
