#ifndef AOC_COMPUTER_HPP
#define AOC_COMPUTER_HPP 1

#include <istream>
#include <string>
#include <vector>

namespace aoc2020
{
    struct Instruction
    {
        Instruction(std::string command, int argument);

        std::string command;
        int argument;
    };

    using Instructions = std::vector<Instruction>;

    class Computer
    {
    public:
        Computer(Instructions instructions);

        int get_accumulator() const noexcept;

        Instructions::size_type execute_one();

    private:
        Instructions const m_instructions;
        Instructions::const_iterator m_current_instruction;

        int m_accumulator;
    };

    Instructions parse_instructions(std::istream & input);

    inline int Computer::get_accumulator() const noexcept
    {
        return m_accumulator;
    }
} // namespace aoc2020

#endif
