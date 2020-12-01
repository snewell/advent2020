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
        assert(expenses.size() > 2);
        std::sort(std::begin(expenses), std::end(expenses));

        auto first = std::begin(expenses);
        auto first_end = std::end(expenses) - 2;
        while(first != first_end)
        {
            auto const remaining = magic_number - (*first);
            auto const result = aoc2020::calculate_product(
                std::next(first), std::end(expenses), remaining);
            if(result)
            {
                return (*first) * (*result);
            }
            ++first;
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
