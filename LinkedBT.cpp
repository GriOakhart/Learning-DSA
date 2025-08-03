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
    void printPreOrder() const;
    void printInOrder() const;
    void printPostOrder() const;
private:
    TreeNode* m_root { nullptr };
    void printPreOrderHelper(TreeNode* node) const;
    void printInOrderHelper(TreeNode* node) const;
    void printPostOrderHelper(TreeNode* node) const;
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
        // Previous version: directly throws exception when parent is null,
        // which doesn't handle null parent nodes in the middle of the tree
        // if (!parent) throw std::runtime_error("parent is null");

        // Current version: when parent is null, check if its children are non-null (invalid case)
        // If children are null, enqueue nullptrs to maintain tree structure and continue
        if (!parent)
        {
            if (arr[currentIndex] || arr[currentIndex + 1])
                throw std::runtime_error("parent is null");
            parentQueue.enqueue(nullptr);
            parentQueue.enqueue(nullptr);
            currentIndex += 2;
            continue;
        }

        if (arr[currentIndex])
        {
            // std::cerr << "enqueue " << arr[currentIndex] << " to parentQueue" << std::endl;
            parent->left = new TreeNode { arr[currentIndex] };
        }
        parentQueue.enqueue(parent->left);
        ++currentIndex;

        if (currentIndex < N)
        {
            if (arr[currentIndex])
            {
                // std::cerr << "enqueue " << arr[currentIndex] << " to parentQueue" << std::endl;
                parent->right = new TreeNode { arr[currentIndex] };
            }
            parentQueue.enqueue(parent->right);
            ++currentIndex;
        }
    }
}

template <typename T>
void LinkedBT<T>::printPreOrderHelper(TreeNode* node) const
{
    if (!node) return;
    std::cout << node->data << " ";
    printPreOrderHelper(node->left);
    printPreOrderHelper(node->right);
}

template <typename T>
void LinkedBT<T>::printInOrderHelper(TreeNode* node) const
{
    if (!node) return;
    printInOrderHelper(node->left);
    std::cout << node->data << " ";
    printInOrderHelper(node->right);
}

template <typename T>
void LinkedBT<T>::printPostOrderHelper(TreeNode* node) const
{
    if (!node) return;
    printPostOrderHelper(node->left);
    printPostOrderHelper(node->right);
    std::cout << node->data << " ";
}

template <typename T>
void LinkedBT<T>::printPreOrder() const
{
    printPreOrderHelper(m_root);
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printInOrder() const
{
    printInOrderHelper(m_root);
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printPostOrder() const
{
    printPostOrderHelper(m_root);
    std::cout << '\n';
}

int main(int argc, char* argv[])
{
    // int myArr[16] { 0, 6, 3, 8, 2, 5, 7, 9, 0, 0, 4, 0, 0, 0, 0, 10 };
    // The previous algorithm has a fatal issue:
    // it crashes when creating a tree where some branches have a greater depth
    int myArr[8] { 0, 6, 0, 3, 0, 0, 0, 8 };
    LinkedBT<int> tree;
    tree.init(myArr);

    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    return 0;
}
