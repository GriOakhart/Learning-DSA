//
// Created by Veykhan Van on 07.06.2025.
//

template <typename T>
bool SeqStack<T>::push(const T& obj)
{
    if (m_top >= kDefaultCapacity - 1) return false;
    m_datas[++m_top] = obj;
    return true;
}

template <typename T>
std::optional<std::reference_wrapper<const T>> SeqStack<T>::top() const
{
    if (empty()) return std::nullopt;
    return std::cref(m_datas[m_top]);
}

template <typename T>
bool SeqStack<T>::empty() const
{
    return m_top == -1;
}

template <typename T>
std::optional<const T> SeqStack<T>::pop()
{
    if (empty()) return std::nullopt;
    return std::cref(m_datas[m_top--]);
}

template <typename T>
int SeqStack<T>::size() const
{
    return m_top + 1;
}
