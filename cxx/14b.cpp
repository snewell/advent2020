#include <algorithm>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <vector>

namespace
{
    void apply_value(std::unordered_map<std::uint64_t, std::uint64_t> & memory,
                     std::uint64_t address, std::uint64_t value)
    {
        memory[address] = value;
    }

    template <typename IT>
    void apply_floating_values(
        IT begin, IT end,
        std::unordered_map<std::uint64_t, std::uint64_t> & memory,
        std::uint64_t base_address, std::uint64_t value)
    {
        for(; begin != end; ++begin)
        {
            if(*begin)
            {
                auto const enable_mask =
                    (1ULL << (std::distance(begin, end) - 1));
                auto const enable_address = base_address | enable_mask;
                apply_floating_values(std::next(begin), end, memory,
                                      enable_address, value);

                auto const disable_address = base_address & (~enable_mask);
                apply_floating_values(std::next(begin), end, memory,
                                      disable_address, value);

                apply_value(memory, enable_address, value);
                apply_value(memory, disable_address, value);
            }
        }
    }

    auto do_work(std::istream & input)
    {
        auto mask = std::numeric_limits<std::uint64_t>::max();
        std::unordered_map<std::uint64_t, std::uint64_t> memory;
        std::vector<bool> floating_bits(36, false);

        std::string command;
        std::string dummy;
        while(input >> command >> dummy)
        {
            if(command == "mask")
            {
                input >> command;
                std::uint64_t new_mask = 0;
                floating_bits.clear();
                std::for_each(
                    std::begin(command), std::end(command),
                    [&new_mask, &floating_bits](auto ch) {
                        new_mask <<= 1;
                        floating_bits.push_back(false);
                        switch(ch)
                        {
                        case 'X':
                            floating_bits.back() = true;
                            break;

                        case '0':
                            break;

                        case '1':
                            new_mask |= 0x01; // initialized to all 0s, so we'll
                                              // just enable the last bit
                            break;

                        default:
                            assert(!"Unexpected character in mask");
                            break;
                        }
                    });
                mask = new_mask;
            }
            else
            {
                auto const address_start =
                    std::find_if(std::begin(command), std::end(command),
                                 [](auto ch) { return std::isdigit(ch); });
                auto const address_end =
                    std::find(address_start, std::end(command), ']');

                std::string const digit(address_start, address_end);
                std::uint64_t address = std::stoll(digit);
                address |= mask;

                std::uint64_t value;
                input >> value;

                // apply_value(memory, address, value);
                apply_floating_values(std::begin(floating_bits),
                                      std::end(floating_bits), memory, address,
                                      value);
            }
        }

        return std::accumulate(
            std::begin(memory), std::end(memory), 0ULL,
            [](auto result, auto const & rhs) { return result + rhs.second; });
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
