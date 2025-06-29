//
// Created by jason on 6/28/25.
//

#include <initializer_list>
#include <iostream>

class SeqBinaryTree
{
public:
    SeqBinaryTree(const std::initializer_list<int>& list)
    {
        for (auto i : list)
        {
            int numeral { 1 };
            while (m_tree[numeral] != 0)
            {
                numeral = (i < m_tree[numeral]) ? (numeral << 1) : (numeral << 1 | 1);
            }
            m_tree[numeral] = i;

            if (numeral > m_maxNumeral) m_maxNumeral = numeral;
        }
    }
    void printList()
    {
        for (int i = 1; i <= m_maxNumeral; ++i)
        {
            if (m_tree[i] != 0)
            {
                std::cout << "treeNode[" << i << "]" << m_tree[i] << "\n";
            }
        }
        std::cout << std::endl;
    }
private:
    int m_tree[1024] {};
    int m_maxNumeral { 0 };
};

int main(int argc, char* argv[])
{
    SeqBinaryTree tree {6, 9, 3, 7, 11, 4, 17, 5, 12, 14, 1, 15, 2, 13, 16, 10, 19, 18, 8, 20};
    tree.printList();
    return 0;
}
