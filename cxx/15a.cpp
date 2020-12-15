#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <unordered_map>

namespace
{
    struct NumberEntry
    {
        NumberEntry()
          : recent_turn{0}
          , previous_turn{0}
        {
        }

        NumberEntry & operator=(int last)
        {
            previous_turn = recent_turn;
            recent_turn = last;
            return *this;
        }

        int recent_turn;
        int previous_turn;
    };

    constexpr int iterations = 2020;

    auto do_work(std::istream & input)
    {
        std::unordered_map<int, NumberEntry> numbers;
        numbers.reserve(iterations);

        int count = 0;
        int current;
        while(input >> current)
        {
            ++count;
            numbers[current] = count;
            char dummy;
            input.get(dummy);
        }
        while(count < iterations)
        {
            ++count;
            auto const previous = numbers.find(current);
            assert(previous != std::end(numbers));
            if(previous->second.previous_turn == 0)
            {
                // first time we're seeing it
                current = 0;
            }
            else
            {
                current = previous->second.recent_turn -
                          previous->second.previous_turn;
            }
            numbers[current] = count;
        }

        return current;
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
