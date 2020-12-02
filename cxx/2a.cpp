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
        std::size_t min_count;
        std::size_t max_count;
        char special_character;
    };

    LineInfo parse_line(std::string const & line)
    {
        LineInfo li;
        auto const colon_pos = line.find(':');
        li.password = std::string_view(line.data() + colon_pos);
        li.special_character = line[colon_pos - 1];

        std::istringstream is(line);
        is >> li.min_count;
        is.get();
        is >> li.max_count;
        return li;
    }

    bool password_valid(LineInfo const & info)
    {
        std::size_t const special_count = std::count_if(
            std::begin(info.password), std::end(info.password),
            [&info](auto ch) { return ch == info.special_character; });
        return (info.min_count <= special_count) &&
               (special_count <= info.max_count);
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
