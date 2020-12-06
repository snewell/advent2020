#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace
{
    auto get_count(std::map<char, int> const & yes_counts, int total_people)
    {
        return std::count_if(std::begin(yes_counts), std::end(yes_counts),
                             [total_people](auto const & p) {
                                 return p.second == total_people;
                             });
    }

    auto do_work(std::istream & istream)
    {
        auto total = 0;
        std::string line;
        std::map<char, int> yes_questions;
        auto people_count = 0;
        while(std::getline(istream, line))
        {
            if(line.empty())
            {
                total += get_count(yes_questions, people_count);
                yes_questions.clear();
                people_count = 0;
            }
            else
            {
                std::for_each(std::begin(line), std::end(line),
                              [&yes_questions](auto ch) {
                                  auto it = yes_questions.find(ch);
                                  if(it != yes_questions.end())
                                  {
                                      ++(it->second);
                                  }
                                  else
                                  {
                                      yes_questions.insert(
                                          std::make_pair(ch, 1));
                                  }
                              });
                ++people_count;
            }
        }
        total += get_count(yes_questions, people_count);
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
