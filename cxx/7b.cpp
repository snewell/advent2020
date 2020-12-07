#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <aoc/baggage.hpp>

namespace
{
    int do_work(std::istream & input)
    {
        auto bag_info = aoc2020::parse_baggage(input);

        return aoc2020::calculate_total_bags(bag_info, "shiny gold");
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
