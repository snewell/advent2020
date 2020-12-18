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
        Point(int x, int y, int z, int w)
          : x{x}
          , y{y}
          , z{z}
          , w{w}
        {
        }

        int x;
        int y;
        int z;
        int w;
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
                if(lhs.z < rhs.z)
                {
                    return true;
                }
                else if(lhs.z == rhs.z)
                {
                    return lhs.w < rhs.w;
                }
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
                    ret.emplace(i, y, 0, 0);
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
                            for(auto next_w = point.w - 1;
                                next_w < (point.w + 2); ++next_w)
                            {
                                if((next_x != point.x) || (next_y != point.y) ||
                                   (next_z != point.z) || (next_w != point.w))
                                {
                                    Point key{next_x, next_y, next_z, next_w};
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
            }

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
