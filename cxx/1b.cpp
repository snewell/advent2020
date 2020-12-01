#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace
{
    int do_work(std::istream & input)
    {
        std::vector<int> expenses;
        int value;
        while(input >> value)
        {
            expenses.push_back(value);
        }
        std::sort(std::begin(expenses), std::end(expenses));
        assert(expenses.size() > 2);
        auto first = std::begin(expenses);
        auto second_end = std::end(expenses) - 1;
        auto first_end = second_end - 1;
        while(first != first_end)
        {
            auto const magic_number = 2020;
            auto const remaining = magic_number - (*first);

            auto second = std::next(first);
            while(second != second_end)
            {
                auto const expected = remaining - (*second);
                auto it = std::lower_bound(second, second_end, expected);
                if((it != second_end) && (*it == expected))
                {
                    return (*first) * (*second) * (*it);
                }
                second_end = it;
                ++second;
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
