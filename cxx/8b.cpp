#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include <aoc/computer.hpp>

namespace
{
    auto
    make_instructions(aoc2020::Instructions const & original_instructions,
                      aoc2020::Instructions::const_iterator candidate_to_change)
    {
        auto ret = original_instructions;
        auto position = std::distance(std::begin(original_instructions),
                                      candidate_to_change);
        if(ret[position].command == "nop")
        {
            ret[position].command = "jmp";
        }
        else
        {
            assert(ret[position].command == "jmp");
            ret[position].command = "nop";
        }
        return ret;
    }

    int do_work(std::istream & input)
    {
        auto const original_instructions = aoc2020::parse_instructions(input);
        auto find_possible_change = [&original_instructions](auto start_point) {
            return std::find_if(start_point, std::end(original_instructions),
                                [](auto const & instruction) {
                                    return (instruction.command == "jmp") ||
                                           (instruction.command == "nop");
                                });
        };

        std::vector<int> instruction_visits(original_instructions.size(), 0);
        for(auto next_change =
                find_possible_change(std::begin(original_instructions));
            next_change != std::end(original_instructions);
            next_change = find_possible_change(std::next(next_change)))
        {
            aoc2020::Computer computer{
                make_instructions(original_instructions, next_change)};

            auto next_instruction = computer.execute_one();
            while((instruction_visits[next_instruction] == 0) &&
                  (next_instruction != original_instructions.size()))
            {
                ++instruction_visits[next_instruction];
                next_instruction = computer.execute_one();
            }
            if(next_instruction == original_instructions.size())
            {
                return computer.get_accumulator();
            }
            instruction_visits.clear();
            instruction_visits.insert(std::begin(instruction_visits),
                                      original_instructions.size(), 0);
        }
        throw std::runtime_error{"Unable to terminate program"};
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
