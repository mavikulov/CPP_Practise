#pragma once

#include <stddef.h>
#include <string>
#include <cstring>
#include <stdexcept>

class StringView {
private:
    const char* data_;
    size_t size_;

public:
    StringView(const std::string& str, size_t start_pos = 0, size_t length = std::string ::npos) {
        start_pos = std::min(start_pos, str.length());
        length = std::min(length, str.length() - start_pos);
        data_ = str.c_str() + start_pos;
        size_ = length;
    }
    StringView(const char* str) {
        data_ = str;
        size_ = std::strlen(str);
    }
    StringView(const char* str, size_t length) : data_(str), size_(length) {
    }
    char operator[](size_t i) const {
        if (i < size_) {
            return data_[i];
        }
        throw std::out_of_range("Index out of range");
    }
    const char* Data() const {
        return data_;
    }
    size_t Size() const {
        return size_;
    }
};
