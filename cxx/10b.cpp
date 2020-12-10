#include <algorithm>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    auto do_work(std::istream & input)
    {
        std::vector<int> adapters{0};
        int value;
        while(input >> value)
        {
            adapters.push_back(value);
        }
        std::sort(std::begin(adapters), std::end(adapters));

        std::vector<long long> end_count(adapters.size(), 0);
        end_count.back() = 1; // we have to use the last adapter
        auto current_index = end_count.size();
        while(current_index > 0)
        {
            --current_index;
            auto const last_index = (current_index > 3) ? current_index - 3 : 0;

            for(auto consider = last_index; consider < current_index;
                ++consider)
            {
                auto const difference =
                    adapters[current_index] - adapters[consider];
                if(difference <= 3)
                {
                    end_count[consider] += end_count[current_index];
                }
            }
        }
        return end_count.front();
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
