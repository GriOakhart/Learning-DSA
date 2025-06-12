//
// Created by Veykhan Van on 10.06.2025.
//

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <memory>
#include <optional>
#include <functional>

template <typename T>
class LinkedStack
{
private:
    struct Node
    {
        T data {};
        std::shared_ptr<Node> prev { nullptr };
    };
public:
    LinkedStack() = default;
    void push(const T& data);
    std::optional<std::reference_wrapper<const T>> top() const;
    std::optional<const T> pop();
    [[nodiscard]] bool empty() const { return !m_top; }
private:
    std::shared_ptr<Node> m_top { nullptr };
};

template <typename T>
void LinkedStack<T>::push(const T& data)
{
    // auto newNode { std::make_shared<Node>(data, m_top) };
    std::shared_ptr<Node> newNode { new Node { data, m_top } };
    m_top = newNode;
}

template <typename T>
std::optional<std::reference_wrapper<const T>> LinkedStack<T>::top() const
{
    if (!m_top) return std::nullopt;
    return m_top->data;
}

template <typename T>
std::optional<const T> LinkedStack<T>::pop()
{
    if (!m_top) return std::nullopt;
    auto oldTop { m_top };
    m_top = m_top->prev;
    return oldTop->data;
}

#endif //LINKEDSTACK_H
