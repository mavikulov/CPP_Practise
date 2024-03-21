#pragma once

#include <stdexcept>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

struct StudentName {
    std::string name, surname;
};

struct Date {
    int year, month, day;
};

struct Student {
    std::string name, surname;
    int day, month, year, score;
    std::vector<std::string> preferences;
};

bool CompareScores(const Student& st1, const Student& st2) {
    if (st1.score > st2.score) {
        return true;
    }
    if (st1.score < st2.score) {
        return false;
    }
    if (st1.year < st2.year) {
        return true;
    }
    if (st1.year > st2.year) {
        return false;
    }
    if (st1.month < st2.month) {
        return true;
    }
    if (st1.month > st2.month) {
        return false;
    }
    if (st1.day < st2.day) {
        return true;
    }
    if (st1.day > st2.day) {
        return false;
    }
    if (st1.surname < st2.surname) {
        return true;
    }
    if (st1.surname > st2.surname) {
        return false;
    }
    if (st1.name < st2.name) {
        return true;
    }
    if (st1.name > st2.name) {
        return false;
    }
    return true;
}

bool CompareNames(const StudentName& st1, const StudentName& st2) {
    if (st1.surname < st2.surname) {
        return true;
    }
    if (st1.surname > st2.surname) {
        return false;
    }
    if (st1.name < st2.name) {
        return true;
    }
    if (st1.name > st2.name) {
        return false;
    }
    return true;
}

std::map<std::string, std::vector<StudentName>> GetStudents(
    const std::vector<std::pair<std::string, int>>& universities_info,
    const std::vector<std::tuple<StudentName, Date, int, std::vector<std::string>>>&
        students_info) {

    std::map<std::string, int> universities;
    for (const auto& [name, limit] : universities_info) {
        universities[name] = limit;
    }
    std::vector<Student> students;
    for (size_t i = 0; i < students_info.size(); ++i) {
        Student student;
        student.name = std::get<0>(students_info[i]).name;
        student.surname = std::get<0>(students_info[i]).surname;
        student.year = std::get<1>(students_info[i]).year;
        student.month = std::get<1>(students_info[i]).month;
        student.day = std::get<1>(students_info[i]).day;
        student.score = std::get<2>(students_info[i]);
        student.preferences = std::get<3>(students_info[i]);
        students.push_back(student);
    }
    std::sort(students.begin(), students.end(), CompareScores);
    std::map<std::string, std::vector<StudentName>> result;
    for (auto it = universities_info.begin(); it != universities_info.end(); ++it) {
        result[it->first];
    }
    for (size_t i = 0; i < students.size(); i++) {
        for (std::string university : students[i].preferences) {
            if (universities[university] > 0) {
                --universities[university];
                result[university].push_back({students[i].name, students[i].surname});
                break;
            }
        }
    }

    for (std::map<std::string, std::vector<StudentName>>::iterator it = result.begin();
         it != result.end(); it++) {
        std::sort((it->second).begin(), (it->second).end(), CompareNames);
    }

    return result;
}

