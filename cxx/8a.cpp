#include <fstream>
#include <iostream>
#include <vector>

#include <aoc/computer.hpp>

namespace
{
    int do_work(std::istream & input)
    {
        auto instructions = aoc2020::parse_instructions(input);
        std::vector<int> instruction_visits(instructions.size(), 0);
        aoc2020::Computer computer{std::move(instructions)};

        auto next_instruction = computer.execute_one();
        while(instruction_visits[next_instruction] == 0)
        {
            ++instruction_visits[next_instruction];
            next_instruction = computer.execute_one();
        }
        return computer.get_accumulator();
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
