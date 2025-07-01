//
// Created by jason on 7/1/25.
//

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
    SeqQueue<TreeNode*> queue;
    m_root = new TreeNode { arr[1] };
    queue.enqueue(m_root);

    TreeNode* leftNode { nullptr };
    TreeNode* rightNode { nullptr };
    for (int i = 2; i < N; ++i)
    {
        auto newNode = new TreeNode { arr[i] };
        queue.enqueue(newNode);
        if (i & 1)  // i is odd
        {
            rightNode = newNode;
            auto fatherNode = queue.dequeue();
            fatherNode.value()->left = leftNode;
            fatherNode.value()->right = rightNode;
        }
        else
        {
            leftNode = newNode;
            if (i == N - 1)
                queue.dequeue().value()->left = leftNode;
        }
    }
}

int main(int argc, char* argv[])
{
    int myArr[17] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    LinkedBT<int> tree;
    tree.init(myArr);
    return 0;
}
