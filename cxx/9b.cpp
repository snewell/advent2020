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

    int find_invalid_number(std::istream & input, std::vector<int> & queue)
    {
        auto sorted_queue = queue;
        std::sort(std::begin(sorted_queue), std::end(sorted_queue));

        int value;
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
                                           queue[queue.size() - buffer_size]);
                assert(it != std::end(sorted_queue));
                assert((*it) == queue[queue.size() - buffer_size]);
                sorted_queue.erase(it);

                queue.push_back(value);
                it = std::lower_bound(std::begin(sorted_queue),
                                      std::end(sorted_queue), value);
                sorted_queue.insert(it, value);
            }
        }
        throw std::runtime_error{"No bad value found"};
    }

    int find_range_value(std::vector<int> & queue, int invalid_number)
    {

        auto b = std::begin(queue);
        auto const e = std::end(queue);

        while(b != e)
        {
            auto total = *b;
            auto sub_e = std::next(b, 1);
            while((sub_e != e) && (total < invalid_number))
            {
                total += *sub_e;
                std::advance(sub_e, 1);
            }
            if(total == invalid_number)
            {
                std::sort(b, sub_e);
                return (*b) + *(sub_e - 1);
            }
            std::advance(b, 1);
        }
        throw std::runtime_error{"No range found"};
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
        auto const invalid_number = find_invalid_number(input, queue);
        return find_range_value(queue, invalid_number);
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
