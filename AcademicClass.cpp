//
// Created by Veykhan Van on 11.05.2025.
//

#include "AcademicClass.h"

std::optional<std::reference_wrapper<const Student>> AcademicClass::find(int id) const
{
    for (int index { 0 }; index <= m_last; ++index)
        if (m_data[index].id == id)
            return m_data[index];
    return std::nullopt;
}

std::optional<std::reference_wrapper<const Student>> AcademicClass::find(std::string_view name) const
{
    for (int index { 0 }; index <= m_last; ++index)
        if (m_data[index].name == name)
            return m_data[index];
    return std::nullopt;
}

void AcademicClass::addStudent(const Student& student)
{
    if (m_last == kDefaultCapacity - 1)
        throw std::runtime_error("Class is full");
    if (student.id > kDefaultCapacity || find(student.id) != std::nullopt)
        throw std::runtime_error("ID is invalid");
    m_data[m_last + 1] = student;
    m_data[m_last + 1].id = m_last + 2;
    ++m_last;
}

void AcademicClass::delStudent(int id)
{
    int index { 0 };
    for (; index <= m_last && m_data[index].id != id; ++index);
    if (index <= m_last)
    {
        for (int i { index }; i < m_last; ++i)
            m_data[i] = m_data[i + 1];
        --m_last;
    }
}

void AcademicClass::delStudent(std::string_view name)
{
    int index { 0 };
    for (; index <= m_last && m_data[index].name != name; ++index);
    if (index <= m_last)
    {
        for (int i { index }; i < m_last; ++i)
            m_data[i] = m_data[i + 1];
        --m_last;
    }
}

