//
// Created by Wang on 2025/5/6.
//

#include <memory>
#include <stdexcept>
#include <iostream>

template<typename T>
SeqList<T>::SeqList(const SeqList<T>& other)
    : m_data { std::make_unique<T[]>(kDefaultCapacity) }, m_last { other.m_last }
{
    std::copy(other.m_data.get(), other.m_data.get() + m_last + 1, m_data.get());
}

template<typename T>
SeqList<T>::SeqList(SeqList<T>&& other) noexcept
    : m_data { std::move(other.m_data) }, m_last { other.m_last }
{
    other.m_last = -1;
}

template<typename T>
SeqList<T>& SeqList<T>::operator=(const SeqList<T>& other)
{
    if (this != &other)
    {
        m_data = std::make_unique<T[]>(kDefaultCapacity);
        m_last = other.m_last;
        std::copy(other.m_data.get(), other.m_data.get() + m_last + 1, m_data.get());
    }
    return *this;
}

template<typename T>
SeqList<T>& SeqList<T>::operator=(SeqList<T>&& other) noexcept
{
    if (this != &other)
    {
        m_data = std::move(other.m_data);
        m_last = other.m_last;
        other.m_last = -1;
    }
    return *this;
}

template<typename T>
T& SeqList<T>::operator[](int index)
{
    if (index < 0 || index > m_last)
        throw std::out_of_range("index out of range");
    return m_data[index];
}

template<typename T>
const T& SeqList<T>::operator[](int index) const
{
    if (index < 0 || index > m_last)
        throw std::out_of_range("index out of range");
    return m_data[index];
}

template<typename T>
int SeqList<T>::find(const T& key) const
{
    for (int index { 0 }; index <= m_last; ++index)
        if (m_data[index] == key)
            return index;
    return -1;
}

template<typename T>
void SeqList<T>::insert(int index, const T& key)
{
    if (m_last == kDefaultCapacity - 1)
        throw std::runtime_error("list is full");
    if (index < 0 || index > m_last + 1)
        throw std::out_of_range("index out of range");
    for (int i { m_last }; i >= index; --i)
        m_data[i + 1] = m_data[i];
    m_data[index] = key;
    ++m_last;
}

template<typename T>
void SeqList<T>::del(int index)
{
    if (m_last == -1)
        throw std::runtime_error("list is empty");
    if (index < 0 || index > m_last)
        throw std::out_of_range("index out of range");
    for (int i { index }; i <= m_last - 1; ++i)
        m_data[i] = m_data[i + 1];
    --m_last;
}

template<typename T>
const int SeqList<T>::getLength() const
{
    return m_last + 1;
}

template<typename T>
void SeqList<T>::print() const
{
    if (m_last == -1)
        std::cout << "list is empty" << '\n';
    else
        for (int i { 0 }; i <= m_last; ++i)
            std::cout << m_data[i] << '\n';
    std::cout << '\n';
}

template<typename T>
void SeqList<T>::reverse()
{
    if (m_last > 0)
        for (int i { 0 }; i <= (m_last - 1) / 2; ++i)
            std::swap(m_data[i], m_data[m_last - i]);
}
