//
// Created by jason on 7/1/25.
//

#include <iostream>
#include "SeqQueue.h"

template <typename T>
class LinkedBT
{
public:
    struct TreeNode
    {
        T data {};
        TreeNode* left { nullptr };
        TreeNode* right { nullptr };
    };
    LinkedBT() = default;
    template <std::size_t N>
    void init(const T (&arr)[N]);
private:
    TreeNode* m_root { nullptr };
};

template <typename T>
template <std::size_t N>
void LinkedBT<T>::init(const T (&arr)[N])
{
    // starting from arr[1], the arr[0] is null.
    if (N <= 1) return;
    SeqQueue<TreeNode*> parentQueue;
    m_root = new TreeNode { arr[1] };
    parentQueue.enqueue(m_root);

    int currentIndex { 2 };
    while (currentIndex < N)
    {
        auto parent { parentQueue.dequeue().value() };
        if (!parent) throw std::runtime_error("parent is null");

        if (arr[currentIndex])
        {
            std::cerr << "enqueue " << arr[currentIndex] << " to parentQueue" << std::endl;
            parent->left = new TreeNode { arr[currentIndex] };
        }
        parentQueue.enqueue(parent->left);
        ++currentIndex;

        if (currentIndex < N)
        {
            if (arr[currentIndex])
            {
                std::cerr << "enqueue " << arr[currentIndex] << " to parentQueue" << std::endl;
                parent->right = new TreeNode { arr[currentIndex] };
            }
            parentQueue.enqueue(parent->right);
            ++currentIndex;
        }
    }
}

int main(int argc, char* argv[])
{
    int myArr[17] { 0, 6, 3, 8, 2, 5, 7, 9, 0, 0, 4, 0, 0, 0, 0, 10, 1 };
    LinkedBT<int> tree;
    tree.init(myArr);
    return 0;
}
