#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <aoc/baggage.hpp>

namespace
{
    int do_work(std::istream & input)
    {
        auto const bag_info = aoc2020::parse_baggage(input);

        std::vector<std::string> pending_considerations{"shiny gold"};
        std::set<std::string> considered_colors;

        while(!pending_considerations.empty())
        {
            auto const current_color = pending_considerations.back();
            pending_considerations.pop_back();
            considered_colors.insert(current_color);
            auto const current_carried_by =
                bag_info.carried_by.find(current_color);
            if(current_carried_by != std::end(bag_info.carried_by))
            {
                std::for_each(std::begin(current_carried_by->second),
                              std::end(current_carried_by->second),
                              [&pending_considerations,
                               &considered_colors](auto const & next_color) {
                                  if(considered_colors.count(next_color) == 0)
                                  {
                                      considered_colors.insert(next_color);
                                      pending_considerations.push_back(
                                          next_color);
                                  }
                              });
            }
        }

        return considered_colors.size() - 1;
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
