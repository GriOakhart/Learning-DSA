//
// Created by Wang on 2025/5/6.
//

#ifndef SEQLIST_H
#define SEQLIST_H

#include <memory>
#include <initializer_list>
#include <stdexcept>
#include <iostream>

template<typename T>
class SeqList
{
public:
    static constexpr int kDefaultCapacity { 1024 };

    /**
     * @brief 构造一个指定大小的顺序表
     * @param size 顺序表的初始大小，默认为0
     */
    explicit SeqList(int size = 0)
        : m_data { std::make_unique<T[]>(kDefaultCapacity) }, m_last { size - 1 } {}
    
    /**
     * @brief 使用初始化列表构造顺序表
     * @param il 用于初始化顺序表的初始化列表
     */
    SeqList(const std::initializer_list<T>& il)
        : m_data { std::make_unique<T[]>(kDefaultCapacity) }, m_last { static_cast<int>(il.size()) - 1 }
    {
        std::copy(il.begin(), il.end(), m_data.get());
    }
    
    /**
     * @brief 复制构造函数
     * @param other 要复制的顺序表对象
     */
    SeqList(const SeqList& other);
    
    /**
     * @brief 移动构造函数
     * @param other 要移动的顺序表对象
     */
    SeqList(SeqList&& other) noexcept;
    
    /**
     * @brief 复制赋值运算符
     * @param other 要复制的顺序表对象
     * @return 当前对象的引用
     */
    SeqList& operator=(const SeqList& other);
    
    /**
     * @brief 移动赋值运算符
     * @param other 要移动的顺序表对象
     * @return 当前对象的引用
     */
    SeqList& operator=(SeqList&& other) noexcept;
    
    /**
     * @brief 常量下标运算符
     * @param index 要访问的元素索引
     * @return 指定索引处元素的常量引用
     * @throws std::out_of_range 如果索引超出范围
     */
    const T& operator[](int index) const;
    
    /**
     * @brief 下标运算符
     * @param index 要访问的元素索引
     * @return 指定索引处元素的引用
     * @throws std::out_of_range 如果索引超出范围
     */
    T& operator[](int index);
    
    /**
     * @brief 在顺序表中查找指定值
     * @param key 要查找的值
     * @return 如果找到，返回该值在顺序表中的索引；否则返回-1
     */
    [[nodiscard]] int find(const T& key) const;
    
    /**
     * @brief 在指定位置插入元素
     * @param index 插入位置的索引
     * @param key 要插入的值
     * @throws std::runtime_error 如果顺序表已满
     * @throws std::out_of_range 如果索引超出范围
     */
    void insert(int index, const T& key);
    
    /**
     * @brief 删除指定位置的元素
     * @param index 要删除元素的索引
     * @throws std::runtime_error 如果顺序表为空
     * @throws std::out_of_range 如果索引超出范围
     */
    void del(int index);
    
    /**
     * @brief 获取顺序表的长度
     * @return 顺序表中元素的个数
     */
    [[nodiscard]] const int getLength() const;
    
    /**
     * @brief 打印顺序表中的所有元素
     * 如果顺序表为空，则输出"list is empty"
     */
    void print() const;

    /**
     * @brief 反转顺序表中所有元素的顺序
     * 如果顺序表中没有元素，则不进行任何操作。
     */
    void reverse();
protected:
    std::unique_ptr<T[]> m_data { nullptr };  ///< 存储顺序表数据的数组
    int m_last { -1 };                          ///< 最后一个元素的索引（-1表示空表）
};

// 包含模板实现
#include "SeqList.tpp"

#endif //SEQLIST_H
