#include <aoc/math.hpp>

#include <cassert>
#include <cctype>

namespace
{
    long long extract_sub_expression(std::istream & input)
    {
        char ch;
        input >> ch;
        auto lhs = 0LL;
        if(std::isdigit(ch))
        {
            lhs = ch - '0';
        }
        else
        {
            lhs = extract_sub_expression(input);
        }

        while(input >> ch)
        {
            if(ch == ')')
            {
                return lhs;
            }

            auto rhs = aoc2020::extract_value(input);
            switch(ch)
            {
            case '+':
                lhs += rhs;
                break;

            case '*':
                lhs *= rhs;
                break;
            }
        }
        throw std::runtime_error{"Unexpected input"};
    }
} // namespace

namespace aoc2020
{
    long long extract_value(std::istream & input)
    {
        char ch;
        input >> ch;
        if(std::isdigit(ch))
        {
            return ch - '0';
        }
        assert(ch == '(');
        return extract_sub_expression(input);
    }
} // namespace aoc2020
