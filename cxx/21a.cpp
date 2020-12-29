#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

namespace
{
    using PotentialAllergans = std::map<std::string, std::vector<std::string>>;
    using KnownAllergans = std::map<std::string, std::string>;

    void extract_words(std::vector<std::string> & output,
                       std::string const & line)
    {
        output.clear();

        std::istringstream input(line);
        std::string word;
        while(input >> word)
        {
            if(word.back() == ',')
            {
                word = word.substr(0, word.size() - 1);
            }
            output.push_back(word);
        }
    }

    void cleanup(std::vector<std::string> & ingredients,
                 KnownAllergans const & known)
    {
        auto it = std::remove_if(std::begin(ingredients), std::end(ingredients),
                                 [&known](auto const & ingredient) {
                                     return known.count(ingredient) == 1;
                                 });
        if(it != std::end(ingredients))
        {
            ingredients.erase(it, std::end(ingredients));
        }
    }

    auto do_work(std::istream & input)
    {
        PotentialAllergans potential;
        KnownAllergans known;

        std::vector<std::string> ingredients;
        std::vector<std::string> allergens;
        std::set<std::string> all_ingredients;

        std::string line;
        while(std::getline(input, line))
        {
            static std::regex const splitter("^(.*) \\(contains (.*)\\)$");

            std::smatch groups;
            auto match = std::regex_match(line, groups, splitter);
            assert(match);
            extract_words(ingredients, groups[1].str());
            extract_words(allergens, groups[2].str());

            cleanup(ingredients, known);
            std::sort(std::begin(ingredients), std::end(ingredients));
            for(auto const & ingredients : ingredients)
            {
                all_ingredients.insert(ingredients);
            }

            for(auto const & allergen : allergens)
            {
                auto const current_candidates = potential.find(allergen);
                if(current_candidates == std::end(potential))
                {
                    // first time we're seeing this
                    potential.emplace(allergen, ingredients);
                }
                else
                {
                    std::vector<std::string> new_potential;
                    std::set_intersection(
                        std::begin(current_candidates->second),
                        std::end(current_candidates->second),
                        std::begin(ingredients), std::end(ingredients),
                        std::back_inserter(new_potential));
                    assert(!new_potential.empty());
                    if(new_potential.size() == 1)
                    {
                        known.emplace(new_potential.front(), allergen);
                    }
                    current_candidates->second = new_potential;
                }
            }
        }

        // cleanup
        auto total_unresolved = std::numeric_limits<std::size_t>::max();
        while(total_unresolved > 0)
        {
            std::size_t current_unresolved = 0;
            for(auto & [allergen, ingredients] : potential)
            {
                if(ingredients.size() > 1)
                {
                    cleanup(ingredients, known);
                    current_unresolved += ingredients.size() - 1;
                }
            }
            assert(current_unresolved < total_unresolved);
            total_unresolved = current_unresolved;
        }
        return all_ingredients.size() - known.size();
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
