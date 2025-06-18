//
// Created by Veykhan Van on 07.06.2025.
//

#ifndef SEQSTACK_H
#define SEQSTACK_H

#include <functional>
#include <memory>
#include <optional>

template <typename T>
class SeqStack
{
public:
    static constexpr int kDefaultCapacity { 1024 };
    explicit SeqStack()
        : m_datas { std::make_unique<T[]>(kDefaultCapacity) }, m_top { -1 } {}
    bool push(const T& obj);
    std::optional<std::reference_wrapper<const T>> top() const;
    std::optional<const T> pop();
    bool empty() const;
    int size() const;
private:
    std::unique_ptr<T[]> m_datas { nullptr };
    int m_top { -1 };
};

#include "SeqStack.tpp"

#endif //SEQSTACK_H
