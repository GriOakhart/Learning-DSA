//
// Created by Veykhan Van on 10.05.2025.
//

#include "Polynomial.h"

void Polynomial::print() const
{
    if (!head)
    {
        std::cout << "0\n";
        return;
    }

    for (Node* current { head }; current; current = current->next)
    {
        std::cout << current->data;
        if (current->next)
            std::cout << " ";
    }
    std::cout << '\n';
}

void Polynomial::attach(const Term& term)
{
    if (term.coeff == 0) return;
    Node* newNode { new Node { term, nullptr } };
    if (!head)
        head = newNode;
    else if (!head->next)
    {
        if (head->data.exponent != term.exponent)
            head->next = newNode;
        else
        {
            delete newNode;
            if (head->data.coeff + term.coeff != 0)
                head->data.coeff += term.coeff;
            else
            {
                delete head;
                head = nullptr;
            }
        }
    }
    else
    {
        Node* previous { head };
        for (; previous->next->next; previous = previous->next);
        if (previous->next->data.exponent != term.exponent)
            previous->next->next = newNode;
        else
        {
            delete newNode;
            if (previous->next->data.coeff + term.coeff != 0)
                previous->next->data.coeff += term.coeff;
            else
            {
                delete previous->next;
                previous->next = nullptr;
            }
        }
    }
}

Polynomial addPolynomial(const Polynomial& lhs, const Polynomial& rhs)
{
    if (lhs.isEmpty()) return rhs;
    if (rhs.isEmpty()) return lhs;

    Polynomial result;
    auto currentL { lhs.head };
    auto currentR { rhs.head };
    while (currentL && currentR)
    {
        if (currentL->data.exponent > currentR->data.exponent)
        {
            result.attach(currentR->data);
            currentR = currentR->next;
        }
        else if (currentL->data.exponent < currentR->data.exponent)
        {
            result.attach(currentL->data);
            currentL = currentL->next;
        }
        else
        {
            if (currentL->data.coeff + currentR->data.coeff != 0)
                result.attach(Term{ currentL->data.coeff + currentR->data.coeff, currentL->data.exponent });
            currentL = currentL->next;
            currentR = currentR->next;
        }
    }
    while (currentL)
    {
        result.attach(currentL->data);
        currentL = currentL->next;
    }
    while (currentR)
    {
        result.attach(currentR->data);
        currentR = currentR->next;
    }
    return result;
}
