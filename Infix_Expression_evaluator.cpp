//
// Created by jason on 6/17/25.
//

#include <iostream>
#include "SeqStack.h"

enum class Type
{
    Operand,
    Operator,
    Separator,
};

Type getCharType(char c)
{
    if (c == ' ') return Type::Separator;
    if (c == '+' || c == '-' || c == '*' || c == '/') return Type::Operator;
    return Type::Operand;
}

int getPriority(char c)
{
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

int main(int argc, char* argv[])
{
    // Calculate the expression: 8 + 3 * 5 - 7 / 2 + 9 - 4 * 6 + 1 / 3 - 2
    char myExpression[] { "8 + 3 * 5 - 7 / 2 + 9 - 4 * 6 + 1 / 3 - 2" };
    std::cout << "The desired result is: " << 8 + 3 * 5 - 7 / 2 + 9 - 4 * 6 + 1 / 3 - 2 << std::endl;

    // create the stacks for operands and operators
    SeqStack<int> sOperands;
    SeqStack<char> sOperators;

    int current { 0 };
    // scan the expression from left to end
    while (myExpression[current] != '\0')
    {
        switch (getCharType(myExpression[current]))
        {
            // skip any space
        case Type::Separator:
            ++current;
            continue;
            // push the operand onto the stack
        case Type::Operand:
            sOperands.push(myExpression[current] - '0');
            ++current;
            continue;
        case Type::Operator:
            // if the previous operator is of higher priority, do calculation first
            if (!sOperators.empty())
                while (getPriority(sOperators.top().value().get()) >= getPriority(myExpression[current]))
                {
                    int b { sOperands.pop().value() };
                    int a { sOperands.pop().value() };
                    sOperands.push(calculate(a, b, sOperators.pop().value()));
                    // break if no operator left in the stack
                    if (sOperators.empty()) break;
                }
            // then push the current operator and move to next
            sOperators.push(myExpression[current]);
            ++current;
        }
    }

    // process the remaining elements in sOperators
    while (!sOperators.empty())
    {
        int b { sOperands.pop().value() };
        int a { sOperands.pop().value() };
        sOperands.push(calculate(a, b, sOperators.pop().value()));
    }

    std::cout << "The result is: " << sOperands.pop().value() << '\n';

    return 0;
}
