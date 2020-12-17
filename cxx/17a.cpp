#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

namespace
{
    struct Point
    {
        Point(int x, int y, int z)
          : x{x}
          , y{y}
          , z{z}
        {
        }

        int x;
        int y;
        int z;
    };

    bool operator<(Point lhs, Point rhs)
    {
        if(lhs.x < rhs.x)
        {
            return true;
        }
        else if(lhs.x == rhs.x)
        {
            if(lhs.y < rhs.y)
            {
                return true;
            }
            else if(lhs.y == rhs.y)
            {
                return lhs.z < rhs.z;
            }
        }
        return false;
    }

    auto read_starting_state(std::istream & input)
    {
        std::set<Point> ret;

        std::string line;
        int y = 0;
        while(std::getline(input, line))
        {
            for(std::size_t i = 0; i < line.length(); ++i)
            {
                if(line[i] == '#')
                {
                    ret.emplace(i, y, 0);
                }
            }
            --y;
        }
        return ret;
    }

    auto do_work(std::istream & input)
    {
        auto current_state = read_starting_state(input);

        for(auto count = 0; count < 6; ++count)
        {
            auto considerations = 0;
            std::map<Point, int> neighbor_data;
            for(auto const & point : current_state)
            {
                for(auto next_x = point.x - 1; next_x < (point.x + 2); ++next_x)
                {
                    for(auto next_y = point.y - 1; next_y < (point.y + 2);
                        ++next_y)
                    {
                        for(auto next_z = point.z - 1; next_z < (point.z + 2);
                            ++next_z)
                        {
                            if((next_x != point.x) || (next_y != point.y) ||
                               (next_z != point.z))
                            {
                                ++considerations;
                                Point key{next_x, next_y, next_z};
                                auto it = neighbor_data.find(key);
                                if(it != neighbor_data.end())
                                {
                                    ++(it->second);
                                }
                                else
                                {
                                    neighbor_data.emplace(key, 1);
                                }
                            }
                        }
                    }
                }
            }

#if 0
            for(auto z = -1; z < 2; ++z)
            {
                std::cout << "z = " << z << '\n';
                for(auto y = 4; y > -4; --y)
                {
                    for(auto x = -4; x < 4; ++x)
                    {
                        auto it = neighbor_data.find(Point{x, y, z});
                        if(it != neighbor_data.end())
                        {
                            std::cout << it->second;
                        }
                        else
                        {
                            std::cout << 'x';
                        }
                    }
                    std::cout << "\t\t";
                    for(auto x = -4; x < 4; ++x)
                    {
                        if(current_state.count(Point{x, y, z}) != 0)
                        {
                            std::cout << '#';
                        }
                        else
                        {
                            std::cout << '.';
                        }
                    }

                    std::cout << '\n';
                }
                std::cout << '\n';
            }
#endif

            std::set<Point> next_state;
            for(auto const & [point, count] : neighbor_data)
            {
                if(count == 3)
                {
                    next_state.insert(point);
                }
                else if(count == 2)
                {
                    if(current_state.count(point) != 0)
                    {
                        next_state.insert(point);
                    }
                }
            }

#if 0
            for(auto z = -1; z < 2; ++z)
            {
                std::cout << "z = " << z << '\n';
                for(auto y = -1; y < 2; ++y)
                {
                    for(auto x = -1; x < 2; ++x)
                    {
                        if(next_state.count(Point{x, y, z}) == 1)
                        {
                            std::cout << '#';
                        }
                        else
                        {
                            std::cout << '.';
                        }
                    }
                    std::cout << '\n';
                }
            }
#endif

            std::swap(next_state, current_state);
        }

        return current_state.size();
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
