#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    int do_work(std::istream & input)
    {
        std::vector<int> adapters{0};
        int value;
        while(input >> value)
        {
            adapters.push_back(value);
        }
        std::sort(std::begin(adapters), std::end(adapters));

        std::array<int, 3> differences = {0, 0, 0};
        ++differences[2]; // laptop is always 3 more
        std::adjacent_find(std::begin(adapters), std::end(adapters),
                           [&differences](auto first, auto second) {
                               auto const difference = second - first;
                               assert(difference > 0);
                               assert(difference <= 3);
                               ++differences[difference - 1];
                               return false;
                           });
        return differences[0] * differences[2];
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
