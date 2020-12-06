#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

namespace
{
    auto do_work(std::istream & istream)
    {
        auto total = 0;
        std::string line;
        std::set<char> yes_questions;
        while(std::getline(istream, line))
        {
            if(line.empty())
            {
                total += yes_questions.size();
                yes_questions.clear();
            }
            else
            {
                std::for_each(
                    std::begin(line), std::end(line),
                    [&yes_questions](auto ch) { yes_questions.insert(ch); });
            }
        }
        total += yes_questions.size();
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
