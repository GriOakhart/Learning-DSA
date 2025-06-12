//
// Created by Wang on 2025/5/6.
//

#include <iostream>
#include <stdexcept>

template<typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& il)
{
    Node* current { nullptr };
    for (const auto& i : il)
    {
        auto newNode { new Node{ i, nullptr } };
        if (!head)
        {
            head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = current->next;
        }
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const std::initializer_list<T>& il)
{
    if (head) reset();
    Node* current { nullptr };
    for (const auto& i : il)
    {
        auto newNode { new Node{ i, nullptr } };
        if (!head)
        {
            head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = current->next;
        }
    }
    return *this;
}

template<typename T>
void LinkedList<T>::print() const
{
    if (!head)
        std::cout << "list is empty";
    else
    {
        for (Node* current { head }; current; current = current->next)
            std::cout << current->data << '\t';
    }
    std::cout << '\n';
}

template<typename T>
LinkedList<T>::~LinkedList()
{
    reset();
}

template<typename T>
void LinkedList<T>::reset()
{
    if (head)
    {
        Node* current { head };
        while (current)
        {
            Node* temp { current->next };
            delete current;
            current = temp;
        }
        head = nullptr;
    }
}

template<typename T>
const int LinkedList<T>::length() const
{
    int length { 0 };
    for (Node* current { head }; current; current = current->next)
        ++length;
    return length;
}

template<typename T>
T& LinkedList<T>::operator[](int index)
{
    if (index < 0)
        throw std::out_of_range("index out of range");
    int i { 0 };
    for (Node* current { head }; current; current = current->next)
    {
        if (i == index) return current->data;
        ++i;
    }
    throw std::out_of_range("index out of range");
}

template<typename T>
const T& LinkedList<T>::operator[](int index) const
{
    if (index < 0)
        throw std::out_of_range("index out of range");
    int i { 0 };
    for (Node* current { head }; current; current = current->next)
    {
        if (i == index) return current->data;
        ++i;
    }
    throw std::out_of_range("index out of range");
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList& il)
{
    Node* current { nullptr };
    for (Node* currentSource { il.head }; currentSource; currentSource = currentSource->next)
    {
        auto newNode { new Node{ currentSource->data, nullptr } };
        if (!head)
        {
            head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = current->next;
        }
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& il)
{
    if (this != &il)
    {
        Node* dummy { new Node { T{}, head } };
        Node* previous { dummy };
        for (Node* currentSource { il.head }; currentSource; currentSource = currentSource->next)
        {
            if (previous->next)
                previous->next->data = currentSource->data;
            else
                previous->next = new Node { currentSource->data, nullptr };
            previous = previous->next;
        }
        Node* tail { previous->next };
        previous->next = nullptr;
        while (tail)
        {
            // clear the trailing nodes
            Node* temp { tail->next };
            delete tail;
            tail = temp;
        }
        head = dummy->next;
        delete dummy;
    }
    return *this;
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList&& il) noexcept
{
    head = il.head;
    il.head = nullptr;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& il) noexcept
{
    if (this != &il)
    {
        reset();
        head = il.head;
        il.head = nullptr;
    }
    return *this;
}

template<typename T>
bool LinkedList<T>::insertAt(int index, const T& value)
{
    if (index < 0) throw std::out_of_range("index out of range");
    if (index == 0)
    {
        Node* newNode { new Node { value, head } };
        head = newNode;
        return true;
    }
    int indexPrevious { 0 };
    for (Node* current { head }; current; current = current->next)
    {
        if (indexPrevious == index - 1)
        {
            Node* newNode { new Node{ value, current->next } };
            current->next = newNode;
            return true;
        }
        ++indexPrevious;
    }
    return false;
}

template<typename T>
void LinkedList<T>::insertAtHead(const T& value)
{
    insertAt(0, value);
}

template<typename T>
void LinkedList<T>::insertAtTail(const T& value)
{
    if (!head)
    {
        insertAt(0, value);
        return;
    }
    Node* current { head };
    for (; current->next; current = current->next);
    Node* newNode { new Node{ value, nullptr } };
    current->next = newNode;
}

template<typename T>
bool LinkedList<T>::removeAt(int index)
{
    if (index < 0) throw std::out_of_range("index out of range");
    if (!head) return false;
    if (index == 0)
    {
        Node* toDelete { head };
        head = toDelete->next;
        delete toDelete;
        return true;
    }
    int indexPrevious { 0 };
    for (Node* current { head }; current->next; current = current->next)
    {
        if (indexPrevious == index - 1)
        {
            Node* toDelete { current->next };
            current->next = toDelete->next;
            delete toDelete;
            return true;
        }
        ++indexPrevious;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::removeFromHead()
{
    return removeAt(0);
}

template<typename T>
bool LinkedList<T>::removeFromTail()
{
    if (!head) return false;
    if (!head->next) return removeAt(0);
    Node* current { head };
    for (; current->next->next; current = current->next);
    delete current->next;
    current->next = nullptr;
    return true;
}

template<typename T>
int LinkedList<T>::findIndex(const T& value) const
{
    if (!head) return -1;
    int index { 0 };
    for (Node* current { head }; current; current = current->next)
    {
        if (current->data == value)
            return index;
        ++index;
    }
    return -1;
}

template<typename T>
bool LinkedList<T>::contains(const T& value) const
{
    return findIndex(value) != -1;
}

template<typename T>
void LinkedList<T>::reverse()
{
    if (!head) return;
    if (!head->next) return;
    Node* previous { head };
    Node* current { previous->next };
    head->next = nullptr;
    while (true)
    {
        if (!current->next)
        {
            current->next = previous;
            head = current;
            return;
        }
        Node* next { current->next };
        current->next = previous;
        previous = current;
        current = next;
    }
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
    return !head;
}

template <typename T>
void LinkedList<T>::swap(int index1, int index2)
{
    if (head)
        if (head->next)
        {
            if (index1 < 0 || index2 < 0)
                throw std::out_of_range("index out of range");
            if (index1 == index2)
                return;
            if (index1 > index2)
                std::swap(index1, index2);

            Node* prev1 { nullptr };
            Node* curr1 { head };
            for (int i { 0 }; curr1 && i < index1; ++i)
            {
                prev1 = curr1;
                curr1 = curr1->next;
            }
            if (!curr1)
                throw std::out_of_range("index1 out of range");

            Node* prev2 { prev1 };
            Node* curr2 { curr1 };
            for (int i { index1 }; curr2 && i < index2; ++i)
            {
                prev2 = curr2;
                curr2 = curr2->next;
            }
            if (!curr2)
                throw std::out_of_range("index2 out of range");

            if (prev1)
                prev1->next = curr2;
            else
                head = curr2;

            if (prev2)
                prev2->next = curr1;
            else
                head = curr1;

            Node* temp { curr2->next };
            curr2->next = curr1->next;
            curr1->next = temp;
        }
}
