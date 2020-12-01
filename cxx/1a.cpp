#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <aoc/accounting.hpp>

namespace
{
    constexpr auto magic_number = 2020;

    int do_work(std::istream & input)
    {
        std::vector<int> expenses;
        int value;
        while(input >> value)
        {
            expenses.push_back(value);
        }
        assert(expenses.size() > 1);
        std::sort(std::begin(expenses), std::end(expenses));

        auto result = aoc2020::calculate_product(
            std::begin(expenses), std::end(expenses), magic_number);
        if(result)
        {
            return *result;
        }

        throw std::runtime_error{"Match not found"};
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
