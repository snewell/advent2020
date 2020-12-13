#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

namespace
{
    struct BusOffset
    {
        BusOffset(unsigned long long bus_id, unsigned int offset)
          : bus_id{bus_id}
          , offset{offset}
        {
        }

        unsigned long long bus_id;
        unsigned int offset;
    };

    std::vector<BusOffset> parse(std::istream & input)
    {
        int departure_time;
        int offset_index = 0;
        std::string bus_number;
        std::vector<BusOffset> offset_requirements;

        input >> departure_time;
        while(std::getline(input, bus_number, ','))
        {

            if(bus_number[0] != 'x')
            {
                offset_requirements.emplace_back(std::stoi(bus_number),
                                                 offset_index);
            }
            ++offset_index;
        }
        return offset_requirements;
    }

    auto do_work(std::istream & input)
    {
        auto const offset_requirements = parse(input);
#if 0
        auto current = offset_requirements.front();
        std::for_each(std::begin(offset_requirements) + 1, std::end(offset_requirements), [&current](auto const &rhs) {
            auto current_timestamp = current.bus_id;
            while(true) {
                auto const offset_timestamp = current_timestamp - rhs.offset;
                if((offset_timestamp % rhs.bus_id) == 0) {
                    current.bus_id = current_timestamp;
                    return;
                }
                current_timestamp += current.bus_id;
            }
        });
        return current.bus_id;
#else
        auto const maximum_duration = std::max_element(
            std::begin(offset_requirements), std::end(offset_requirements),
            [](auto const & lhs, auto const & rhs) {
                return lhs.bus_id < rhs.bus_id;
            });

        unsigned long long current_timestamp = maximum_duration->bus_id;
        while(current_timestamp < maximum_duration->offset)
        {
            current_timestamp += maximum_duration->bus_id;
        }
        current_timestamp -= maximum_duration->offset;
        while(true)
        {
            if(current_timestamp >= 1068780)
            {
                // std::cout << "Breakpoint\n";
            }
            auto conflicting_bus = std::find_if(
                std::begin(offset_requirements), std::end(offset_requirements),
                [current_timestamp](auto const & bus_info) {
                    auto const required_time =
                        current_timestamp + bus_info.offset;
                    return (required_time % bus_info.bus_id) != 0;
                });
            if(conflicting_bus == std::end(offset_requirements))
            {
                return current_timestamp;
            }
            current_timestamp += maximum_duration->bus_id;
        }
#endif
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
