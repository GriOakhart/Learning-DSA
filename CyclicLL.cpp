//
// Created by Veykhan Van on 02.06.2025.
//

#include <iostream>
#include "CyclicLL.h"

CyclicLL::CyclicLL(const std::initializer_list<int>& list)
{
    Node* head { nullptr };
    Node* current { nullptr };
    for (const auto& element : list)
    {
        auto newNode { new Node{element, nullptr} };
        if (!head)
        {
            head = newNode;
            current = head;
        }
        else
        {
            current->next = newNode;
            current = current->next;
        }
    }
    if (current)
        current->next = head;
    m_tail = current;
}

void CyclicLL::print() const
{
    if (isEmpty())
    {
        std::cout << "empty list\n";
        return;
    }
    auto current { m_tail->next };
    while (true)
    {
        std::cout << current->data << '\t';
        current = current->next;
        if (current == m_tail->next) break;
    }
    std::cout << '\n';
}

void CyclicLL::reset()
{
    if (m_tail)
    {
        Node* current = m_tail->next;
        while (current != m_tail)
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete m_tail;
        m_tail = nullptr;
    }
}

CyclicLL::~CyclicLL()
{
    reset();
}

CyclicLL::CyclicLL(const CyclicLL& other)
{
    if (!other.isEmpty())
    {
        m_tail = new Node{ other.m_tail->data, nullptr };
        Node* current { m_tail };
        for (Node* otherCurrent { other.m_tail->next }; otherCurrent != other.m_tail; otherCurrent = otherCurrent->next)
        {
            Node* newNode = new Node{ otherCurrent->data, nullptr };
            current->next = newNode;
            current = current->next;
        }
        current->next = m_tail;
    }
}

CyclicLL::CyclicLL(CyclicLL&& other) noexcept
{
    m_tail = other.m_tail;
    other.m_tail = nullptr;
}

CyclicLL& CyclicLL::operator=(const CyclicLL& other)
{
    if (this != &other)
    {
        if (other.isEmpty())
        {
            reset();
            return *this;
        }
        if (m_tail)
            m_tail->data = other.m_tail->data;
        else
            m_tail = new Node{ other.m_tail->data, nullptr };
        Node* current { m_tail };
        for (Node* otherCurrent { other.m_tail->next }; otherCurrent != other.m_tail; otherCurrent = otherCurrent->next)
        {
            if (current->next && current->next != m_tail)
                current->next->data = otherCurrent->data;
            else
                current->next = new Node{ otherCurrent->data, nullptr };
            current = current->next;
        }
        if (current->next && current->next != m_tail)
        {
            auto toDelete { current->next };
            while (toDelete != m_tail)
            {
                auto temp { toDelete->next };
                delete toDelete;
                toDelete = temp;
            }
        }
        current->next = m_tail;
    }
    return *this;
}

CyclicLL& CyclicLL::operator=(CyclicLL&& other) noexcept
{
    if (this != &other)
    {
        reset();
        m_tail = other.m_tail;
        other.m_tail = nullptr;
    }
    return *this;
}

CyclicLL merge(const CyclicLL& a, const CyclicLL& b)
{
    if (a.isEmpty()) return b;
    if (b.isEmpty()) return a;
    CyclicLL copyA { a };
    CyclicLL copyB { b };
    auto copyAHead { copyA.m_tail->next };
    copyA.m_tail->next = copyB.m_tail->next;
    copyB.m_tail->next = copyAHead;

    // 使用尾指针作为标记，则不再需要遍历链表。查找链表的头尾都是O(1)复杂度
    // CyclicLL::Node* current { copyA.m_head };
    // for (; current->next != copyA.m_head; current = current->next);
    // current->next = copyB.m_head;
    // current = current->next;
    // for (; current->next != copyB.m_head; current = current->next);
    // current->next = copyA.m_head;
    copyA.m_tail = nullptr; // 如果没有这一行，会导致双重释放
    return copyB;
}

int CyclicLL::length() const
{
    if (isEmpty()) return 0;
    int length { 1 };
    for (Node* current { m_tail->next }; current != m_tail; current = current->next)
        ++length;
    return length;
}

void JosephGame(CyclicLL& list, int spacing, int numToRemove)
{
    if (numToRemove > list.length())
    {
        std::cout << "ERROR: numToRemove > length\n";
        return;
    }
    if (numToRemove == list.length())
    {
        list.reset();
        return;
    }
    CyclicLL::Node* current { list.m_tail };
    for (; numToRemove > 0; --numToRemove)
    {
        for (int i { 1 }; i < spacing; ++i)
            current = current->next;
        auto toDelete { current->next };
        if (toDelete == list.m_tail)
            list.m_tail = current;
        current->next = toDelete->next;
        std::cout << "delete element: " << toDelete->data << '\n';
        delete toDelete;
    }
}
