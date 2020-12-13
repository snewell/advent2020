#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>

namespace
{
    int do_work(std::istream & input)
    {
        int departure_time;
        std::string bus_number;

        int shortest_bus_id = 0;
        auto shortest_wait_time = std::numeric_limits<int>::max();
        input >> departure_time;
        while(std::getline(input, bus_number, ','))
        {
            if(bus_number[0] != 'x')
            {
                auto const current_bus_number = std::stoi(bus_number);
                auto const minutes_early =
                    (departure_time % current_bus_number);

                if(minutes_early != 0)
                {
                    auto const current_wait_time =
                        current_bus_number - minutes_early;
                    if(current_wait_time < shortest_wait_time)
                    {
                        shortest_wait_time = current_wait_time;
                        shortest_bus_id = current_bus_number;
                    }
                }
                else
                {
                    return 0; // bus * minutes_to_wait = 0
                }
            }
        }
        return shortest_bus_id * shortest_wait_time;
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
