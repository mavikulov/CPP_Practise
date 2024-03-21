#pragma once

#include <string>
#include <stdexcept>
#include <algorithm>

std::string LongSum(const std::string& a, const std::string& b) {
    if (a.empty() && b.empty()) {
        return "";
    }
    if (a.empty() && !b.empty()) {
        return b;
    }
    if (b.empty() && !a.empty()) {
        return a;
    }

    std::string str1 = a;
    std::string str2 = b;
    std::string result;
    if (str1.length() > str2.length()) {
        std::swap(str1, str2);
    }

    int n1 = str1.length(), n2 = str2.length();
    std::reverse(str1.begin(), str1.end());
    std::reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i = 0; i < n1; i++) {
        int sum = (str1[i] - '0') + (str2[i] - '0') + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    for (int i = n1; i < n2; i++) {
        int sum = (str2[i] - '0') + carry;
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    if (carry) {
        result.push_back(carry + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}
