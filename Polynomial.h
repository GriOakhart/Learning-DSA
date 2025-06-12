//
// Created by Veykhan Van on 10.05.2025.
//

#ifndef POLY_H
#define POLY_H

#include "LinkedList.h"

struct Term
{
    int coeff {};
    int exponent {};
};

inline std::ostream& operator<<(std::ostream& os, const Term& term)
{
    if (term.coeff == 0)
        return os << "0";
    if (term.exponent == 0)
        return os << std::showpos << term.coeff << std::noshowpos;
    if (term.exponent == 1)
        return os << std::showpos << term.coeff << std::noshowpos << " x";
    return os << std::showpos << term.coeff << std::noshowpos << " x^" << term.exponent;
}

class Polynomial : public LinkedList<Term>
{
public:
    Polynomial() = default;
    ~Polynomial() = default;

    // newly implemented functions
    [[nodiscard]] Node* getHead() const { return head; }
    void print() const;
    void attach(const Term& term);
    friend Polynomial addPolynomial(const Polynomial& lhs, const Polynomial& rhs);

    // deleted functions
    Term& operator[](int index) = delete;
    const Term& operator[](int index) const = delete;
    Polynomial(const std::initializer_list<Term>& il) = delete;
    Polynomial& operator=(const std::initializer_list<Term>& il) = delete;
    bool insertAt(int index, const Term& value) = delete;
    void insertAtHead(const Term& value) = delete;
    void insertAtTail(const Term& value) = delete;
    bool removeAt(int index) = delete;
    bool removeFromHead() = delete;
    bool removeFromTail() = delete;
    int findIndex(const Term& value) const = delete;
    bool contains(const Term& value) const = delete;
    void reverse() = delete;
};

Polynomial addPolynomial(const Polynomial& lhs, const Polynomial& rhs);

#endif //POLY_H
