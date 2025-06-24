//
// Created by jason on 6/18/25.
//

#include <iostream>
#include "SeqStack.h"

namespace myVariables
{
    constexpr char expression0[] { "8 + 3 * 5 - 7 / 2 + 9 - 4 * 6 + 1 / 3 - 2" };
    constexpr char expression1[] { "8 3 5 * + 7 2 / - 9 + 4 6 * - 1 3 / + 2 -" };
    constexpr char expression2[] { "((7 + 3) * (9 - 2)) / ((8 + 1) - (4 * 2)) + ((6 + 5) * 2) - ((3 + 7) / (9 - 4)) + (8 * (2 + 6)) - ((9 - 3) + (1 * 4)) / (7 + 2) + ((5 * 8) - (6 + 3)) * ((4 - 1) + (9 / 3)) - (2 * (7 + 5)) + ((8 - 4) * (6 + 2)) / (9 - 1)" };
}

int suffixExpressionEvaluate(const char* expression)
{
    SeqStack<int> sOperands;

    // 执行二元运算的辅助函数
    auto performBinaryOperation = [&sOperands](char op) {
        int b = sOperands.pop().value();
        int a = sOperands.pop().value();

        switch (op) {
            case '+': sOperands.push(a + b); break;
            case '-': sOperands.push(a - b); break;
            case '*': sOperands.push(a * b); break;
            case '/': sOperands.push(a / b); break;
        }
    };

    // 判断是否为运算符
    auto isOperator = [](char ch) {
        return ch == '+' || ch == '-' || ch == '*' || ch == '/';
    };

    int current { -1 };
    while (expression[++current] != '\0')
    {
        char ch = expression[current];

        if (ch == ' ') {
            continue;
        }

        if (isOperator(ch)) {
            performBinaryOperation(ch);
        } else {
            sOperands.push(ch - '0');
        }
    }

    return sOperands.pop().value();
}

enum class Type { numbers, operators, left_paren, right_paren, space };
Type getType(char ch)
{
    switch (ch)
    {
    case ' ': return Type::space;
    case '(': return Type::left_paren;
    case ')': return Type::right_paren;
    case '+':
    case '-':
    case '*':
    case '/': return Type::operators;
    default: return Type::numbers;
    }
}

int getPriority(char ch)
{
    switch (ch)
    {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    default: return 0;
    }
}

void infixToSuffix(const char* inExpression, char* outExpression)
{
    SeqStack<char> sOperators;

    int rCurrent { -1 };
    int current { -1 };
    while (inExpression[++current] != '\0')
    {
        switch (getType(inExpression[current]))
        {
        case Type::space: continue;
        case Type::numbers:
            outExpression[++rCurrent] = inExpression[current];
            outExpression[++rCurrent] = ' ';
            continue;
        case Type::left_paren: sOperators.push('('); continue;
        case Type::right_paren:
            while (true)
            {
                auto out { sOperators.pop().value() };
                if (getType(out) == Type::left_paren) break;
                outExpression[++rCurrent] = out;
                outExpression[++rCurrent] = ' ';
            }
            continue;
        case Type::operators:
            if (!(sOperators.empty() || getType(sOperators.top().value().get()) == Type::left_paren))
                while (getPriority(sOperators.top().value().get()) >= getPriority(inExpression[current]))
                {
                    outExpression[++rCurrent] = sOperators.pop().value();
                    outExpression[++rCurrent] = ' ';
                    if (sOperators.empty() || getType(sOperators.top().value().get()) == Type::left_paren) break;
                }
            sOperators.push(inExpression[current]);
        }
    }
    while (!sOperators.empty())
    {
        outExpression[++rCurrent] = sOperators.pop().value();
        outExpression[++rCurrent] = ' ';
    }
    outExpression[++rCurrent] = '\0';
}

int main(int argc, char* argv[])
{
    std::cout << "The result is: " << suffixExpressionEvaluate(myVariables::expression1) << '\n';
    char result[1024];
    infixToSuffix(myVariables::expression2, result);
    std::cout << result << '\n';
    std::cout << "The result is: " << suffixExpressionEvaluate(result) << '\n';
    std::cout << "=====\n";
    std::cout << "The correct result is: " << ((7 + 3) * (9 - 2)) / ((8 + 1) - (4 * 2)) + ((6 + 5) * 2) - ((3 + 7) / (9 - 4)) + (8 * (2 + 6)) - ((9 - 3) + (1 * 4)) / (7 + 2) + ((5 * 8) - (6 + 3)) * ((4 - 1) + (9 / 3)) - (2 * (7 + 5)) + ((8 - 4) * (6 + 2)) / (9 - 1) << '\n';
    return 0;
}