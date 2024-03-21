#pragma once

#include <cstddef>
#include <vector>

class Stack {
private:
    std::vector<int> data_;

public:
    void Push(int x) {
        data_.push_back(x);
    }

    bool Pop() {
        if (!Empty()) {
            data_.pop_back();
            return true;
        }
        return false;
    }

    int Top() const {
        return data_.back();
    }

    bool Empty() const {
        return data_.empty();
    }

    size_t Size() const {
        return data_.size();
    }
};
