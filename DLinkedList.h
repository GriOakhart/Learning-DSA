#ifndef DLinkedList_H
#define DLinkedList_H

#include <initializer_list>

template<typename T>
class DLinkedList
{
protected:
    struct Node
    {
        T data {};
        Node* prev { nullptr };
        Node* next { nullptr };
    };
public:
    DLinkedList() = default;
    DLinkedList(const std::initializer_list<T>& il);
    DLinkedList& operator=(const std::initializer_list<T>& il);
    DLinkedList(const DLinkedList& il);
    DLinkedList(DLinkedList&& il) noexcept;
    DLinkedList& operator=(const DLinkedList& il);
    DLinkedList& operator=(DLinkedList&& il) noexcept;
    ~DLinkedList();
    void print() const;
    void reset();
    [[nodiscard]] const int length() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    bool insertAt(int index, const T& value);
    void insertAtHead(const T& value);
    void insertAtTail(const T& value);
    bool removeAt(int index);
    bool removeFromHead();
    bool removeFromTail();
    int findIndex(const T& value) const;
    bool contains(const T& value) const;
    void reverse();
    [[nodiscard]] bool isEmpty() const;
    void swap(int index1, int index2);
protected:
    Node* head { nullptr };
};

#include "DLinkedList.tpp"

#endif //DLinkedList_H
