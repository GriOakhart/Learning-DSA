//
// Created by Veykhan Van on 12.06.2025.
//

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

// #include "LinkedList.h"
//
// template <typename T>
// class LinkedQueue
// {
// public:
//     LinkedQueue() = default;
//     [[nodiscard]] bool isEmpty() const;
//     void enqueue(const T& value);
//     const T dequeue();
// private:
//     LinkedList<T> head;
// };
//
// template <typename T>
// bool LinkedQueue<T>::isEmpty() const
// {
//     return head.isEmpty();
// }
//
// template <typename T>
// void LinkedQueue<T>::enqueue(const T& value)
// {
//      head.insertAtTail(value); // O(n) 复杂度：需要从表头遍历链表
// }
//
// template <typename T>
// const T LinkedQueue<T>::dequeue()
// {
//     auto out { head[0] };
//     head.removeFromHead();
//     return out;
// }

#include <memory>
#include <optional>

template <typename T>
class LinkedQueue
{
private:
    struct Node
    {
        T data {};
        std::shared_ptr<Node> next { nullptr };
    };
public:
    LinkedQueue() = default;
    void enqueue(const T& data);
    std::optional<const T> dequeue();
    void clear();
    [[nodiscard]] bool isEmpty() const;
private:
    std::shared_ptr<Node> m_front { nullptr };
    std::shared_ptr<Node> m_rear { nullptr };
    int m_count { 0 };
};

template <typename T>
void LinkedQueue<T>::enqueue(const T& data)
{
    if (!isEmpty())
    {
        m_rear->next = std::make_shared<Node>(Node{data, nullptr});
        m_rear = m_rear->next;
    }
    else
        m_front = m_rear = std::make_shared<Node>(Node{data, nullptr});
    ++m_count;
}

template <typename T>
std::optional<const T> LinkedQueue<T>::dequeue()
{
    if (isEmpty()) return std::nullopt;
    auto temp = m_front;
    m_front = m_front->next;
    if (m_count == 1) m_rear = nullptr;
    --m_count;
    return temp->data;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return m_count == 0;
}

template <typename T>
void LinkedQueue<T>::clear()
{
    m_front = m_rear = nullptr;
    m_count = 0;
}

#endif //LINKEDQUEUE_H
