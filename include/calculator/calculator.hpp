#ifndef INCLUDE_CALCULATOR_CALCULATOR_HPP
#define INCLUDE_CALCULATOR_CALCULATOR_HPP

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <sstream>

class Calculator
{
public:
    Calculator() = default;
    ~Calculator() = default;

public:
    // Note: templated function have necessarily to be defined in the header file

    template <typename T = int>
    T solve(const std::string &expression)
    {
        // preprocess the expression

        std::string expr = expression;                                      // contains the trimmed expression
        expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end()); // remove all spaces

        // NOTE: ranges::count from c++20 are not fully supported yet by at least g++14
        // auto num_open_brackets = std::ranges::count(expr, "(");
        // auto num_close_brackets = std::ranges::count(expr, ")");

        std::string::difference_type n = std::count(expr.begin(), expr.end(), '(');
        std::string::difference_type m = std::count(expr.begin(), expr.end(), ')');

        int num_open_brackets = static_cast<int>(n);
        int num_close_brackets = static_cast<int>(m);

        // TODO: only guarantees correct number of brackets, not correct placement
        if (num_open_brackets != num_close_brackets)
        {
            throw std::invalid_argument("Mismatched number of opening and closing brackets");
        }

        return evaluate<T>(expr);
    }

private:
    template <typename T>
    T apply_operator(std::string &left_str, std::string &right_str, char op)
    {
        switch (op)
        {
        case '+':
            return evaluate<T>(left_str) + evaluate<T>(right_str);
        case '-':
            /*
            all signs of the the right-hand side have to be inverted
            this is required since we implicitly apply the associative law,
            requiring the factor -1 to be pulled into the right-hand side
             */
            std::replace(right_str.begin(), right_str.end(), '-', '@');
            std::replace(right_str.begin(), right_str.end(), '+', '-');
            std::replace(right_str.begin(), right_str.end(), '@', '+');
            return evaluate<T>(left_str) - evaluate<T>(right_str);
        case '*':
            return evaluate<T>(left_str) * evaluate<T>(right_str);
        case '/':
            return evaluate<T>(left_str) / evaluate<T>(right_str);
        case '%':
            if constexpr (std::is_same_v<T, int>)
            // modulo operator only defined for integer types
            {
                return evaluate<T>(left_str) % evaluate<T>(right_str);
            }
            else
            {
                throw std::invalid_argument("Modulo operator is only supported for integer types");
            }
        case '^':
            return static_cast<T>(std::pow(evaluate<T>(left_str), evaluate<T>(right_str)));
        default:
            throw std::invalid_argument("Unsupported operator");
        }
    }

    template <typename T>
    T evaluate(std::string &expr)
    {
        const std::vector<char> operators{'+', '-', '*', '/', '%', '^'}; // order of precedence from low to high

        if (expr[0] == '(' && expr[expr.size() - 1] == ')')
        // use explicit element access instead of str.find, since find yields the first occurrence, not allowing multiple brackets
        {
            // remove surrounding brackets
            expr = expr.substr(1, expr.size() - 2);
        }

        std::string blacked_expr = expr;
        int bracket_level{0};
        const char replacement_char = '@';
        for (size_t i = 0; i < blacked_expr.size(); ++i)
        {
            if (blacked_expr[i] == '(')
            // first open bracket will NOT be replaced
            {
                if (++bracket_level > 1)
                {
                    blacked_expr[i] = replacement_char;
                }
                continue;
            }
            else if (blacked_expr[i] == ')')
            {
                --bracket_level;
            }
            if (bracket_level > 0)
            // replace content of highest level brackets
            {
                blacked_expr[i] = replacement_char;
            }
        }

        assert(blacked_expr.size() == expr.size()); // invariant

        for (char op : operators)
        // check for occuring operators in order of precedence from low to high
        {
            auto pos = blacked_expr.find(op);
            if (pos != std::string::npos)
            // operator has been found
            {
                const char operator_char = expr[pos];
                std::string left_str = expr.substr(0, pos);
                std::string right_str = expr.substr(pos + 1);

                return apply_operator<T>(left_str, right_str, operator_char);
            }
        }
        return static_cast<T>(std::stoi(expr));
    }
};

#endif // INCLUDE_CALCULATOR_CALCULATOR_HPP
