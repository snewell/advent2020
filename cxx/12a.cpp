#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>

namespace
{
    int do_work(std::istream & input)
    {
        auto current_position = std::make_pair(0, 0);
        static std::array<std::pair<int, int>, 4> const headings = {
            std::make_pair(1, 0),  // east
            std::make_pair(0, -1), // south
            std::make_pair(-1, 0), // west
            std::make_pair(0, 1),  // north
        };

        auto current_heading = 0;

        auto adjust_position = [&current_position](auto adjustment,
                                                   auto multiplier) {
            current_position.first += adjustment.first * multiplier;
            current_position.second += adjustment.second * multiplier;
        };

        char command;
        int amount;
        while(input >> command >> amount)
        {
            static std::array<std::pair<int, std::pair<int, int>>, 4> const
                adjustments = {std::make_pair('E', std::make_pair(1, 0)),
                               std::make_pair('N', std::make_pair(0, 1)),
                               std::make_pair('S', std::make_pair(0, -1)),
                               std::make_pair('W', std::make_pair(-1, 0))

                };

            auto const direction_it =
                std::find_if(std::begin(adjustments), std::end(adjustments),
                             [command](auto const & adjustment) {
                                 return command == adjustment.first;
                             });
            if(direction_it != std::end(adjustments))
            {
                adjust_position(direction_it->second, amount);
            }
            else
            {
                switch(command)
                {
                case 'F':
                    adjust_position(headings[current_heading], amount);
                    break;

                case 'R':
                case 'L': {
                    auto const rotations = amount / 90;
                    assert((amount % 90) == 0);
                    current_heading += rotations * ((command == 'R') ? 1 : -1);
                    current_heading = (current_heading + 4) % 4;
                    assert(current_heading >= 0);
                    assert(current_heading < 4);
                }
                break;

                default:
                    assert("Unknown command");
                }
            }
        }
        return std::abs(current_position.first) +
               std::abs(current_position.second);
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
