//
// Created by Veykhan Van on 11.05.2025.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <optional>
#include <string>
#include "SeqList.h"

struct Student
{
    std::string name {};
    int id {};
    double score {};
};

inline std::ostream& operator<<(std::ostream& os, const Student& student)
{
    return os << student.name << "\tid: " << student.id << "\tscore: " << student.score;
}

class AcademicClass : public SeqList<Student>
{
public:
    static constexpr int kDefaultCapacity { 50 };

    // constructors and assignments
    AcademicClass() : SeqList<Student>(0) {}
    explicit AcademicClass(int) = delete;
    AcademicClass(const std::initializer_list<Student>& il) : SeqList<Student>(il) {}
    AcademicClass(const AcademicClass& other) : SeqList<Student>(other) {}
    AcademicClass(AcademicClass&& other) noexcept : SeqList<Student>(std::move(other)) {}
    AcademicClass& operator=(const AcademicClass& other) = default;
    AcademicClass& operator=(AcademicClass&& other) noexcept = default;

    // deleted functions
    const Student& operator[](int index) const = delete;
    Student& operator[](int index) = delete;
    [[nodiscard]] int find(const Student& key) const = delete;
    void insert(int index, const Student& key) = delete;
    void del(int index) = delete;

    // newly implemented functions
    /**
     * @brief Find a student by their ID number
     * @param id The ID number to search for
     * @return Optional reference to the const Student if found, empty optional if not found
     */
    [[nodiscard]] std::optional<std::reference_wrapper<const Student>> find(int id) const;

    /**
     * @brief Find a student by their name
     * @param name The name to search for
     * @return Optional reference to the const Student if found, empty optional if not found
     */
    [[nodiscard]] std::optional<std::reference_wrapper<const Student>> find(std::string_view name) const;

    /**
     * @brief Add a new student to the class
     * @param student The Student object to add
     * @throws std::runtime_error if the class is full or if student ID is invalid
     */
    void addStudent(const Student& student);

    /**
     * @brief Delete a student from the class by ID
     * @param id The ID number of the student to delete
     */
    void delStudent(int id);

    /**
     * @brief Delete a student from the class by name
     * @param name The name of the student to delete
     */
    void delStudent(std::string_view name);
};

#endif //STUDENT_H
