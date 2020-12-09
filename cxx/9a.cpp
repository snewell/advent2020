#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    constexpr auto buffer_size = 25;

    bool pair_exists(int value, std::vector<int> const & sorted_considerations)
    {
        auto b = std::begin(sorted_considerations);
        auto e = std::end(sorted_considerations);

        while(b != e)
        {
            auto const required = value - (*b);
            auto const next_b = std::next(b);
            auto it = std::lower_bound(next_b, e, required);
            if((it != e) && ((*it) == required))
            {
                return true;
            }
            e = it;
            b = next_b;
        }
        return false;
    }

    int do_work(std::istream & input)
    {
        std::vector<int> queue;
        queue.reserve(buffer_size);
        int value;
        for(auto i = 0; i < buffer_size; ++i)
        {
            input >> value;
            queue.push_back(value);
        }

        auto sorted_queue = queue;
        std::sort(std::begin(sorted_queue), std::end(sorted_queue));
        auto replace_index = 0;
        while(input >> value)
        {
            if(!pair_exists(value, sorted_queue))
            {
                return value;
            }
            else
            {
                auto it = std::lower_bound(std::begin(sorted_queue),
                                           std::end(sorted_queue),
                                           queue[replace_index]);
                assert(it != std::end(sorted_queue));
                assert((*it) == queue[replace_index]);
                sorted_queue.erase(it);

                queue[replace_index] = value;
                it = std::lower_bound(std::begin(sorted_queue),
                                      std::end(sorted_queue), value);
                sorted_queue.insert(it, value);
                replace_index = (replace_index + 1) % buffer_size;
            }
        }
        throw std::runtime_error{"No bad value found"};
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
