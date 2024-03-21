#pragma once

#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath>

struct Student {
    std::string name, surname;
    int day, month, year;
};

enum class SortType { kByName, kByDate };

bool CompareStudents(const Student& student1, const Student& student2, SortType sort_type) {
    if (sort_type == SortType::kByDate) {
        if (student1.year != student2.year) {
            return student1.year < student2.year;
        }
        if (student1.month != student2.month) {
            return student1.month < student2.month;
        }
        if (student1.day != student2.day) {
            return student1.day < student2.day;
        }
        if (student1.surname != student2.surname) {
            return student1.surname < student2.surname;
        }
        return student1.name < student2.name;
    } else if (sort_type == SortType::kByName) {
        if (student1.surname != student2.surname) {
            return student1.surname < student2.surname;
        }
        if (student1.name != student2.name) {
            return student1.name < student2.name;
        }
        if (student1.year != student2.year) {
            return student1.year < student2.year;
        }
        if (student1.month != student2.month) {
            return student1.month < student2.month;
        }
        return student1.day < student2.day;
    }
    return false;
}

void SortStudents(std::vector<Student>* students, SortType sort_type) {
    std::sort(students->begin(), students->end(),
              [&sort_type](const Student& student1, const Student& student2) {
                  return CompareStudents(student1, student2, sort_type);
              });
}
