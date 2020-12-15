#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

namespace
{
    constexpr int iterations = 2020;

    int do_work(std::istream & input)
    {
        std::vector<int> numbers;
        numbers.reserve(iterations);

        int current;
        while(input >> current)
        {
            numbers.push_back(current);
            char dummy;
            input.get(dummy);
        }
        while(numbers.size() < iterations)
        {
            auto const b = std::rbegin(numbers);
            auto const e = std::rend(numbers);
            auto const previous = std::find(std::next(b), e, numbers.back());
            if(previous == e)
            {
                // first time we've seen it
                numbers.push_back(0);
            }
            else
            {
                numbers.push_back(std::distance(b, previous));
            }
        }

        return numbers[iterations - 1];
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
