//
// Created by jason on 7/1/25.
//

#include <iostream>
#include "SeqQueue.h"
#include "LinkedStack.h"

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
    // Recursive version for Traversals
    void printPreOrderRecursive() const;
    void printInOrderRecursive() const;
    void printPostOrderRecursive() const;
    // Iterative version for Traversals
    void printPreOrderIterative() const;
    void printInOrderIterative() const;
    void printPostOrderIterative() const;
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
void LinkedBT<T>::printPreOrderRecursive() const
{
    printPreOrderHelper(m_root);
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printInOrderRecursive() const
{
    printInOrderHelper(m_root);
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printPostOrderRecursive() const
{
    printPostOrderHelper(m_root);
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printPreOrderIterative() const
{
    if (!m_root) return;
    LinkedStack<TreeNode*> nodeToVisit;
    nodeToVisit.push(m_root);
    while (!nodeToVisit.empty())
    {
        auto node { nodeToVisit.pop().value() };
        std::cout << node->data << " ";
        if (node->right) nodeToVisit.push(node->right);
        if (node->left) nodeToVisit.push(node->left);
    }
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printInOrderIterative() const
{
    if (!m_root) return;
    LinkedStack<TreeNode*> nodeToVisit;

    // 中序遍历中的“移动游标”
    // 负责判断“沿左链下潜”的结束和向右转向
    TreeNode* current { m_root };
    while (!nodeToVisit.empty() || current)
    {
        // 沿当前左链压栈
        while (current)
        {
            nodeToVisit.push(current);
            current = current->left;
        }

        // 弹栈并访问
        auto tempNode { nodeToVisit.pop().value() };
        std::cout << tempNode->data << ' ';

        // 换到右孩子节点，开始访问右子树
        // 此处无需判断右孩子是否为空节点，因为开头压栈会进行判断
        current = tempNode->right;
    }
    std::cout << '\n';
}

template <typename T>
void LinkedBT<T>::printPostOrderIterative() const
{
    if (!m_root) return;
    LinkedStack<TreeNode*> nodeToVisit;
    TreeNode* current { m_root };

    // 相比中序遍历，多一个指针用来标记刚刚访问过的
    // 以防重新访问已访问过的右孩子节点导致循环
    TreeNode* lastVisited { nullptr };
    while (!nodeToVisit.empty() || current)
    {
        while (current)
        {
            nodeToVisit.push(current);
            current = current->left;
        }
        auto tempNode { nodeToVisit.top().value().get() };
        // 不仅需要存在右孩子节点，而且必须是未访问过的
        if (tempNode->right && tempNode->right != lastVisited)
            current = tempNode->right;
        else
        {
            // 如果访问，则立即标记
            std::cout << tempNode->data << ' ';
            lastVisited = tempNode;
            nodeToVisit.pop();
        }
    }
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

    tree.printPreOrderRecursive();
    tree.printInOrderRecursive();
    tree.printPostOrderRecursive();

    std::cout << "==========" << '\n';

    tree.printPreOrderIterative();
    tree.printInOrderIterative();
    tree.printPostOrderIterative();
    return 0;
}
