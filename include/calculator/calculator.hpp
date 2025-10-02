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
    T evaluate(std::string &expr)
    {
        const std::vector<char> operators{'+', '-', '*', '/', '^'};

        if (expr.find('(') == 0 && expr.find(')') == expr.size() - 1)
        {
            expr = expr.substr(1, expr.size() - 2); // remove outer brackets
        }

        std::string blacked_expr = expr;
        int bracket_level = 0;
        for (size_t i = 0; i < blacked_expr.size(); ++i)
        {
            if (blacked_expr[i] == '(')
            {
                ++bracket_level;
            }
            else if (blacked_expr[i] == ')')
            {
                --bracket_level;
            }
            if (bracket_level > 0)
            {
                blacked_expr[i] = '@';
            }
        }

        assert(blacked_expr.size() == expr.size());

        for (char op : operators)
        {
            auto pos = blacked_expr.find(op);
            if (pos != std::string::npos)
            {
                const char operator_char = expr[pos];
                std::string left_str = expr.substr(0, pos);
                std::string right_str = expr.substr(pos + 1);

                switch (operator_char)
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
                case '^':
                    return static_cast<T>(std::pow(evaluate<T>(left_str), evaluate<T>(right_str)));
                default:
                    throw std::invalid_argument("Unsupported operator");
                }
            }
        }
        return static_cast<T>(std::stoi(expr));
    }
};

#endif // INCLUDE_CALCULATOR_CALCULATOR_HPP
