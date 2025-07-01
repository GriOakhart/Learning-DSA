//
// Created by Veykhan Van on 12.06.2025.
//

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include <optional>

template <typename T>
class SeqQueue
{
private:
    static constexpr int kDefaultCapacity { 1024 };
public:
    SeqQueue()
        : m_queue { new T[kDefaultCapacity] }, m_front { kDefaultCapacity - 1 }, m_rear { kDefaultCapacity - 1 } {}
    ~SeqQueue() { delete[] m_queue; }
    [[nodiscard]] bool isEmpty() const { return m_front == m_rear; }
    [[nodiscard]] bool isFull() const { return m_front == (m_rear + 1) % kDefaultCapacity; }
    bool enqueue(const T& item);
    std::optional<T> dequeue();
private:
    T* m_queue { nullptr };
    int m_front {};
    int m_rear {};
};

template <typename T>
bool SeqQueue<T>::enqueue(const T& item)
{
    if (isFull()) return false;
    m_rear = (m_rear + 1) % kDefaultCapacity;
    m_queue[m_rear] = item;
    return true;
}

template <typename T>
std::optional<T> SeqQueue<T>::dequeue()
{
    if (isEmpty()) return std::nullopt;
    m_front = (m_front + 1) % kDefaultCapacity;
    return m_queue[m_front];
}

#endif //SEQQUEUE_H
