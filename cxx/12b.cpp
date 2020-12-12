#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace
{
    int do_work(std::istream & input)
    {
        auto current_position = std::make_pair(0, 0);
        auto waypoint = std::make_pair(10, 1);

        auto adjust_position = [&current_position, &waypoint](auto multiplier) {
            current_position.first += waypoint.first * multiplier;
            current_position.second += waypoint.second * multiplier;
        };

        char command;
        int amount;
        while(input >> command >> amount)
        {
            static std::unordered_map<int, std::pair<int, int>> const
                adjustments = {std::make_pair('N', std::make_pair(0, 1)),
                               std::make_pair('S', std::make_pair(0, -1)),
                               std::make_pair('E', std::make_pair(1, 0)),
                               std::make_pair('W', std::make_pair(-1, 0))};

            auto const direction_it = adjustments.find(command);
            if(direction_it != std::end(adjustments))
            {
                waypoint.first += direction_it->second.first * amount;
                waypoint.second += direction_it->second.second * amount;
            }
            else
            {
                switch(command)
                {
                case 'F':
                    adjust_position(amount);
                    break;

                case 'R':
                case 'L': {
                    static std::array<std::pair<int, int>, 2> const
                        multipliers = {std::make_pair(1, -1),
                                       std::make_pair(-1, 1)};
                    auto const rotations = (amount / 90) % 4;
                    assert((amount % 90) == 0);
                    auto const rotation_index = (command == 'L');
                    for(auto i = 0; i < rotations; ++i)
                    {
                        std::swap(waypoint.first, waypoint.second);
                        waypoint.first *= multipliers[rotation_index].first;
                        waypoint.second *= multipliers[rotation_index].second;
                    }
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
