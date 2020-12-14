#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

namespace
{
    auto do_work(std::istream & input)
    {
        auto disable_mask = std::numeric_limits<std::uint64_t>::max();
        std::uint64_t enable_mask = 0;
        std::vector<std::uint64_t> memory;

        std::string command;
        std::string dummy;
        while(input >> command >> dummy)
        {
            if(command == "mask")
            {
                input >> command;
                std::uint64_t new_disable_mask = 0;
                std::uint64_t new_enable_mask = 0;
                std::for_each(
                    std::begin(command), std::end(command),
                    [&new_disable_mask, &new_enable_mask](auto ch) {
                        new_disable_mask <<= 1;
                        new_disable_mask |= 1;
                        new_enable_mask <<= 1;
                        switch(ch)
                        {
                        case 'X':
                            break;

                        case '0':
                            new_disable_mask ^=
                                0x01; // initilized to all 1s, so we'll just
                                      // toggle the last bit
                            break;

                        case '1':
                            new_enable_mask |=
                                0x01; // initialized to all 0s, so we'll just
                                      // enable the last bit
                            break;

                        default:
                            assert(!"Unexpected character in mask");
                            break;
                        }
                    });
                disable_mask = new_disable_mask;
                enable_mask = new_enable_mask;
            }
            else
            {
                auto const address_start =
                    std::find_if(std::begin(command), std::end(command),
                                 [](auto ch) { return std::isdigit(ch); });
                auto const address_end =
                    std::find(address_start, std::end(command), ']');

                std::string const digit(address_start, address_end);
                std::uint64_t const address = std::stoll(digit);

                if(memory.size() < (address + 1))
                {
                    memory.resize(address + 1, 0);
                }
                input >> memory[address];
                memory[address] &= disable_mask;
                memory[address] |= enable_mask;
            }
        }

        return std::reduce(std::begin(memory), std::end(memory));
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
