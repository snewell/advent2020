#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    struct LineInfo
    {
        std::string_view password;
        std::size_t position_a;
        std::size_t position_b;
        char special_character;
    };

    LineInfo parse_line(std::string const & line)
    {
        LineInfo li;
        auto const colon_pos = line.find(':');
        li.password = std::string_view(line.data() + colon_pos + 2);
        li.special_character = line[colon_pos - 1];

        std::istringstream is(line);
        is >> li.position_a;
        is.get();
        is >> li.position_b;
        return li;
    }

    bool password_valid(LineInfo const & info)
    {
        auto check_position = [&info](auto position) {
            auto const index = position - 1;
            if(index < info.password.length())
            {
                return (info.password[index] == info.special_character);
            }
            return false;
        };

        auto const first_check = check_position(info.position_a);
        auto const second_check = check_position(info.position_b);
        return (first_check != second_check);
    }

    auto do_work(std::istream & input)
    {
        auto valid_passwords = 0;
        std::string line;
        while(std::getline(input, line))
        {
            auto const line_info = parse_line(line);
            if(password_valid(line_info))
            {
                ++valid_passwords;
            }
        }
        return valid_passwords;
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
