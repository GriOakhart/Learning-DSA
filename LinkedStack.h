//
// Created by Veykhan Van on 10.06.2025.
//

#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include <memory>
#include <optional>
#include <functional>

/**
 * @brief A template class implementing a stack data structure using a linked list.
 * @tparam T The type of elements stored in the stack.
 */
template <typename T>
class LinkedStack
{
private:
    /**
     * @brief Internal node structure for the linked stack.
     */
    struct Node
    {
        T data {}; ///< The data stored in the node
        std::shared_ptr<Node> prev { nullptr }; ///< Pointer to the previous node in the stack
    };
public:
    LinkedStack() = default;
    /**
     * @brief Pushes a new element onto the top of the stack.
     * @param data The element to be pushed.
     */
    void push(const T& data);
    /**
     * @brief Returns a reference to the top element without removing it.
     * @return An optional containing a reference to the top element if the stack is not empty,
     *         or std::nullopt if the stack is empty.
     */
    std::optional<std::reference_wrapper<const T>> top() const;
    /**
     * @brief Removes and returns the top element from the stack.
     * @return An optional containing the removed element if the stack is not empty,
     *         or std::nullopt if the stack is empty.
     */
    std::optional<const T> pop();
    /**
     * @brief Checks if the stack is empty.
     * @return true if the stack is empty, false otherwise.
     */
    [[nodiscard]] bool empty() const
    {
        return !m_top; }
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
