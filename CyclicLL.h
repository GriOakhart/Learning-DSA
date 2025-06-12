//
// Created by Veykhan Van on 02.06.2025.
//

#ifndef CYCLICLL_H
#define CYCLICLL_H

#include <initializer_list>

class CyclicLL
{
private:
    struct Node
    {
        int data;
        Node* next;
    };
public:
    CyclicLL() = default;
    CyclicLL(const std::initializer_list<int>& list);
    CyclicLL(const CyclicLL& other);
    CyclicLL(CyclicLL&& other) noexcept;
    CyclicLL& operator=(const CyclicLL& other);
    CyclicLL& operator=(CyclicLL&& other) noexcept;
    [[nodiscard]] bool isEmpty() const { return !m_tail; }
    int length() const;
    void print() const;
    ~CyclicLL();
    void reset();
    friend CyclicLL merge(const CyclicLL& a, const CyclicLL& b);
    friend void JosephGame(CyclicLL& list, int spacing, int numToRemove);
private:
    // 使用尾指针作为循环链表的标记的好处：查找链表的头尾都是O(1)复杂度
    Node* m_tail { nullptr };
};


#endif //CYCLICLL_H
