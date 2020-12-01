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
        assert(expenses.size() > 1);
        std::sort(std::begin(expenses), std::end(expenses));
        auto b = std::begin(expenses);
        auto e = std::end(expenses) - 1;
        while(b != e)
        {
            auto const magic_number = 2020;
            auto const expected = magic_number - (*b);
            auto it = std::lower_bound(b, e, expected);
            if((it != e) && (*it == expected))
            {
                return (*b) * (*it);
            }
            e = it;
            ++b;
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
