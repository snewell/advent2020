#include <aoc/computer.hpp>

#include <algorithm>
#include <cassert>
#include <map>

namespace aoc2020
{
    Instruction::Instruction(Command command, int argument)
      : command{command}
      , argument{argument}
    {
    }

    Instructions parse_instructions(std::istream & input)
    {
        static std::unordered_map<std::string, Instruction::Command> const
            command_map = {
                std::make_pair("nop", Instruction::Command::nop),
                std::make_pair("jmp", Instruction::Command::jump),
                std::make_pair("acc", Instruction::Command::accumulate)};
        Instructions ret;

        std::string command;
        int argument;
        while(input >> command >> argument)
        {
            auto it = command_map.find(command);
            assert(it != command_map.end());
            ret.emplace_back(it->second, argument);
        }
        return ret;
    }

    Computer::Computer(Instructions instructions)
      : m_instructions{std::move(instructions)}
      , m_current_instruction{std::begin(m_instructions)}
      , m_accumulator{0}
    {
    }
} // namespace aoc2020

namespace
{
    int accumulate(int argument, int & accumulator)
    {
        accumulator += argument;
        return 1;
    }

    int jump(int argument, int & accumulator)
    {
        (void)accumulator;
        return argument;
    }

    int nop(int argument, int & accumulator)
    {
        (void)argument;
        (void)accumulator;
        return 1;
    }

    std::map<aoc2020::Instruction::Command,
             int (*)(int, int &)> const instructions = {
        std::make_pair(aoc2020::Instruction::Command::accumulate, accumulate),
        std::make_pair(aoc2020::Instruction::Command::jump, jump),
        std::make_pair(aoc2020::Instruction::Command::nop, nop)};
} // namespace

namespace aoc2020
{
    Instructions::size_type Computer::execute_one()
    {
        auto const instruction_impl =
            instructions.find(m_current_instruction->command);
        assert(instruction_impl != std::end(instructions));

        auto const instruction_offset = instruction_impl->second(
            m_current_instruction->argument, m_accumulator);
        std::advance(m_current_instruction, instruction_offset);
        return std::distance(std::begin(m_instructions), m_current_instruction);
    }
} // namespace aoc2020
