#pragma once

#include <string>
#include <stdexcept>
#include <vector>

std::vector<std::string> Split(const std::string& string, const std::string& delimiter = " ") {
    if (string.empty()) {
        return std::vector<std::string>();
    }
    if (delimiter == string) {
        return std::vector<std::string>{"", ""};
    }
    std::vector<std::string> result;
    size_t i = 0;
    for (size_t j = 0; j < string.size(); ++j) {
        bool is_correct = true;
        for (size_t k = 0; k < delimiter.size(); k++) {
            if (string[j + k] != delimiter[k]) {
                is_correct = false;
            }
        }
        if (is_correct) {
            result.push_back(string.substr(i, j - i));
            i = j + delimiter.size();
        }
    }
    result.push_back(string.substr(i));
    return result;
}
