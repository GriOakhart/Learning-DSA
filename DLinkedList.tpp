#include <iostream>
#include <stdexcept>

template<typename T>
DLinkedList<T>::DLinkedList(const std::initializer_list<T>& il)
{
    Node* current { nullptr };
    for (const auto& i : il)
    {
        auto newNode { new Node{ i, current, nullptr } };
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
DLinkedList<T>& DLinkedList<T>::operator=(const std::initializer_list<T>& il)
{
    if (head) reset();
    Node* current { nullptr };
    for (const auto& i : il)
    {
        auto newNode { new Node{ i, current, nullptr } };
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
void DLinkedList<T>::print() const
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
DLinkedList<T>::~DLinkedList()
{
    reset();
}

template<typename T>
void DLinkedList<T>::reset()
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
const int DLinkedList<T>::length() const
{
    int length { 0 };
    for (Node* current { head }; current; current = current->next)
        ++length;
    return length;
}

template<typename T>
T& DLinkedList<T>::operator[](int index)
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
const T& DLinkedList<T>::operator[](int index) const
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
DLinkedList<T>::DLinkedList(const DLinkedList& il)
{
    Node* current { nullptr };
    for (Node* currentSource { il.head }; currentSource; currentSource = currentSource->next)
    {
        auto newNode { new Node{ currentSource->data, current, nullptr } };
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
DLinkedList<T>& DLinkedList<T>::operator=(const DLinkedList& il)
{
    if (this != &il)
    {
        Node* dummy { new Node { T{}, nullptr, head } };
        if (head) head->prev = dummy;
        Node* previous { dummy };
        for (Node* currentSource { il.head }; currentSource; currentSource = currentSource->next)
        {
            if (previous->next)
                previous->next->data = currentSource->data;
            else
                previous->next = new Node { currentSource->data, previous, nullptr };
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
        if (head) head->prev = nullptr;
        delete dummy;
    }
    return *this;
}

template<typename T>
DLinkedList<T>::DLinkedList(DLinkedList&& il) noexcept
{
    head = il.head;
    il.head = nullptr;
}

template<typename T>
DLinkedList<T>& DLinkedList<T>::operator=(DLinkedList&& il) noexcept
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
bool DLinkedList<T>::insertAt(int index, const T& value)
{
    if (index < 0) throw std::out_of_range("index out of range");
    if (index == 0)
    {
        Node* newNode { new Node { value, nullptr, head } };
        if (head)
            head->prev = newNode;
        head = newNode;
        return true;
    }
    int indexPrevious { 0 };
    for (Node* current { head }; current; current = current->next)
    {
        if (indexPrevious == index - 1)
        {
            Node* newNode { new Node{ value, current, current->next } };
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            return true;
        }
        ++indexPrevious;
    }
    return false;
}

template<typename T>
void DLinkedList<T>::insertAtHead(const T& value)
{
    insertAt(0, value);
}

template<typename T>
void DLinkedList<T>::insertAtTail(const T& value)
{
    if (!head)
    {
        insertAtHead(value);
        return;
    }
    Node* current { head };
    for (; current->next; current = current->next);
    current->next = new Node { value, current, nullptr };
}

template<typename T>
bool DLinkedList<T>::removeAt(int index)
{
    if (index < 0) throw std::out_of_range("index out of range");
    if (!head) return false;
    if (index == 0)
    {
        Node* toDelete { head };
        head = toDelete->next;
        head->prev = nullptr;
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
            if (toDelete->next) toDelete->next->prev = current;
            delete toDelete;
            return true;
        }
        ++indexPrevious;
    }
    return false;
}

template<typename T>
bool DLinkedList<T>::removeFromHead()
{
    return removeAt(0);
}

template<typename T>
bool DLinkedList<T>::removeFromTail()
{
    if (!head) return false;
    if (!head->next) return removeFromHead();
    Node* current { head };
    for (; current->next->next; current = current->next);
    delete current->next;
    current->next = nullptr;
    return true;
}

template<typename T>
int DLinkedList<T>::findIndex(const T& value) const
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
bool DLinkedList<T>::contains(const T& value) const
{
    return findIndex(value) != -1;
}

template<typename T>
void DLinkedList<T>::reverse()
{
    for (Node* current { head }; current; current = current->prev)
    {
        auto temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        if (!current->prev) head = current;
    }
}

template <typename T>
bool DLinkedList<T>::isEmpty() const
{
    return !head;
}

template <typename T>
void DLinkedList<T>::swap(int index1, int index2)
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
            {
                prev1->next = curr2;
                curr2->prev = prev1;
            }
            else
            {
                head = curr2;
                curr2->prev = nullptr;
            }

            if (prev2)
            {
                prev2->next = curr1;
                curr1->prev = prev2;
            }
            else
            {
                head = curr1;
                curr1->prev = nullptr;
            }

            Node* temp { curr2->next };
            curr2->next = curr1->next;
            curr1->next->prev = curr2;
            curr1->next = temp;
            if (temp)
                temp->prev = curr1;
        }
}
