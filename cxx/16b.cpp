#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>

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

    void cleanup_candidates(
        std::vector<std::vector<aoc2020::Field const *>> & candidate_fields,
        aoc2020::Field const * field)
    {
        // remove from every other candidate slot
        // std::cout << "Identified " << field->name << '\n';
        std::for_each(std::begin(candidate_fields), std::end(candidate_fields),
                      [field, &candidate_fields](auto & candidates) {
                          if(candidates.size() > 1)
                          {
                              auto it = std::find(std::begin(candidates),
                                                  std::end(candidates), field);
                              if(it != std::end(candidates))
                              {
                                  candidates.erase(it);
                                  if(candidates.size() == 1)
                                  {
                                      cleanup_candidates(candidate_fields,
                                                         candidates[0]);
                                  }
                              }
                          }
                      });
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
        auto const my_ticket = aoc2020::parse_ticket(line);
        std::getline(input, line);
        assert(line.empty());
        std::getline(input, line);
        assert(line.back() == ':');

        std::vector<std::vector<aoc2020::Field const *>> candidate_fields;
        {
            std::vector<aoc2020::Field const *> all_fields;
            all_fields.reserve(fields.size());
            std::for_each(std::begin(fields), std::end(fields),
                          [&all_fields](auto const & field) {
                              all_fields.push_back(&field);
                          });

            candidate_fields.resize(my_ticket.size(), all_fields);
        }

        [&line, &input, &fields, &candidate_fields]() {
            while(std::getline(input, line))
            {
                auto const ticket = aoc2020::parse_ticket(line);

                auto const invalid_field = std::find_if(
                    std::begin(ticket), std::end(ticket),
                    [&fields](auto value) {
                        auto const valid_field = std::find_if(
                            std::begin(fields), std::end(fields),
                            [value](auto const & field) {
                                return check_field_ranges(value, field);
                            });
                        return valid_field == std::end(fields);
                    });
                if(invalid_field == std::end(ticket))
                {
                    // ticket is valid, so figure out what fields work where
                    for(std::size_t i = 0; i < ticket.size(); ++i)
                    {
                        if(candidate_fields[i].size() > 1)
                        {
                            auto const invalid_it = std::remove_if(
                                std::begin(candidate_fields[i]),
                                std::end(candidate_fields[i]),
                                [value = ticket[i]](auto field) {
                                    return !check_field_ranges(value, *field);
                                });
                            candidate_fields[i].erase(
                                invalid_it, std::end(candidate_fields[i]));
                            if(candidate_fields[i].size() == 1)
                            {
                                cleanup_candidates(candidate_fields,
                                                   candidate_fields[i][0]);
                            }
                        }
                    }
                }
            }
        }();

        unsigned long long product = 1;
        for(std::size_t i = 0; i < candidate_fields.size(); ++i)
        {
            static std::regex starts_with_departure("^departure");

            if(std::regex_search(candidate_fields[i][0]->name,
                                 starts_with_departure))
            {
                product *= my_ticket[i];
            }
        }

        return product;
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
