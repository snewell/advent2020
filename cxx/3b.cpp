#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace
{
    std::vector<std::string> read_map(std::istream & input)
    {
        std::vector<std::string> map;
        std::string line;
        while(std::getline(input, line))
        {
            map.push_back(line);
        }
        return map;
    }

    auto do_work(std::istream & input)
    {
        auto const map = read_map(input);
        auto count_trees = [&map](decltype(map)::size_type right_slope,
                                  decltype(map)::size_type down_slope) {
            decltype(map)::size_type row = 0;
            decltype(map)::size_type column = 0;

            auto const row_length = map[0].size();
            auto count = 0;
            while(row < map.size())
            {
                if(map[row][column] == '#')
                {
                    ++count;
                }
                row += down_slope;
                column += right_slope;
                column %= row_length;
            }
            return count;
        };

        std::pair<int, int> const slopes[] = {
            std::make_pair(1, 1), std::make_pair(3, 1), std::make_pair(5, 1),
            std::make_pair(7, 1), std::make_pair(1, 2)};

        auto result = 1;
        for(auto const & slope : slopes)
        {
            result *= count_trees(slope.first, slope.second);
        }
        return result;
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
