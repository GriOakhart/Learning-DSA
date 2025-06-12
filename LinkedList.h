//
// Created by Wang on 2025/5/6.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <initializer_list>

template<typename T>
class LinkedList
{
protected:
    struct Node
    {
        T data {};
        Node* next { nullptr };
    };
public:
    /**
     * @brief 默认构造函数，创建一个空链表
     */
    LinkedList() = default;
    
    /**
     * @brief 使用初始化列表构造链表
     * @param il 包含泛型值的初始化列表
     */
    LinkedList(const std::initializer_list<T>& il);
    
    /**
     * @brief 使用初始化列表赋值运算符
     * @param il 包含泛型值的初始化列表
     * @return 更新后的链表引用
     */
    LinkedList& operator=(const std::initializer_list<T>& il);
    
    /**
     * @brief 复制构造函数
     * @param il 要复制的链表
     */
    LinkedList(const LinkedList& il);
    
    /**
     * @brief 移动构造函数
     * @param il 要移动的链表
     */
    LinkedList(LinkedList&& il) noexcept;
    
    /**
     * @brief 复制赋值运算符
     * @param il 要复制的链表
     * @return 更新后的链表引用
     */
    LinkedList& operator=(const LinkedList& il);
    
    /**
     * @brief 移动赋值运算符
     * @param il 要移动的链表
     * @return 更新后的链表引用
     */
    LinkedList& operator=(LinkedList&& il) noexcept;
    
    /**
     * @brief 析构函数，释放链表占用的所有内存
     */
    ~LinkedList();
    
    /**
     * @brief 打印链表的所有元素
     */
    void print() const;
    
    /**
     * @brief 重置链表，删除所有节点并释放内存
     */
    void reset();
    
    /**
     * @brief 获取链表的长度
     * @return 链表中的元素数量
     */
    [[nodiscard]] const int length() const;
    
    /**
     * @brief 索引运算符，访问指定索引的元素
     * @param index 要访问的元素索引
     * @return 指定索引元素的引用
     * @throws std::out_of_range 如果索引无效
     */
    T& operator[](int index);
    
    /**
     * @brief 索引运算符的常量版本
     * @param index 要访问的元素索引
     * @return 指定索引元素的常量引用
     * @throws std::out_of_range 如果索引无效
     */
    const T& operator[](int index) const;
    
    /**
     * @brief 在指定索引处插入值
     * @param index 要插入的位置
     * @param value 要插入的值
     * @return 插入是否成功
     * @throws std::out_of_range 如果索引小于0
     */
    bool insertAt(int index, const T& value);
    
    /**
     * @brief 在链表头部插入值
     * @param value 要插入的值
     */
    void insertAtHead(const T& value);
    
    /**
     * @brief 在链表尾部插入值
     * @param value 要插入的值
     */
    void insertAtTail(const T& value);

    /**
     * @brief 删除指定索引处的元素
     * @param index 要删除元素的索引
     * @return 删除是否成功
     * @throws std::out_of_range 如果索引小于0
     */
    bool removeAt(int index);
    
    /**
     * @brief 删除链表头部元素
     * @return 删除是否成功
     */
    bool removeFromHead();
    
    /**
     * @brief 删除链表尾部元素
     * @return 删除是否成功
     */
    bool removeFromTail();
    
    /**
     * @brief 查找值在链表中的索引
     * @param value 要查找的值
     * @return 值的索引，如果未找到则返回-1
     */
    int findIndex(const T& value) const;
    
    /**
     * @brief 检查链表是否包含指定值
     * @param value 要查找的值
     * @return 是否包含该值
     */
    bool contains(const T& value) const;

    /**
     * @brief 反转链表的节点顺序
     *
     * 此方法对链表进行就地反转，即将链表中节点的顺序倒置，从尾节点变为头节点。
     */
    void reverse();

    /**
     * @brief 检查链表是否为空
     * @return 如果链表为空返回true，否则返回false
     */
    [[nodiscard]] bool isEmpty() const;

    /**
     * @brief 交换链表中两个指定索引位置的元素
     * @param index1 第一个要交换的元素的索引
     * @param index2 第二个要交换的元素的索引
     * @throws std::out_of_range 如果任一索引无效
     */
    void swap(int index1, int index2);
protected:
    Node* head { nullptr };
};

// 包含模板实现
#include "LinkedList.tpp"

#endif //LINKEDLIST_H
