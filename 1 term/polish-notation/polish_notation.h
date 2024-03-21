#pragma once

#include <string>
#include <stdexcept>
#include <vector>
#include <stack>

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

int EvaluateExpression(const std::string& expression) {
    if (expression.length() == 1 && isdigit(expression[0])) {
        return stoi(expression);
    }
    std::vector<std::string> tokens = Split(expression);
    std::stack<int> s;
    for (const auto& k : tokens) {
        if (k == "+" || k == "-" || k == "*" || k == "/") {
            int one = s.top();
            s.pop();
            int two = s.top();
            s.pop();
            if (k == "+") {
                s.push(two + one);
            } else if (k == "-") {
                s.push(two - one);
            } else if (k == "*") {
                s.push(two * one);
            } else if (k == "/") {
                s.push(two / one);
            }
        } else {
            s.push(stoi(k));
        }
    }
    return s.top();
}
