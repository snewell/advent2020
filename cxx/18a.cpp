#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <aoc/math.hpp>

namespace
{
    auto calculate_line(std::istream & input)
    {
        auto lhs = aoc2020::extract_value(input);

        char op;
        while(input >> op)
        {
            auto rhs = aoc2020::extract_value(input);

            switch(op)
            {
            case '+':
                lhs += rhs;
                break;

            case '*':
                lhs *= rhs;
                break;

            default:
                throw std::runtime_error{"Unexpected operator"};
            }
        }
        return lhs;
    }

    auto do_work(std::istream & input)
    {
        auto total = 0LL;
        std::string line;
        while(std::getline(input, line))
        {
            std::istringstream line_input{line};
            total += calculate_line(line_input);
        }
        return total;
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
