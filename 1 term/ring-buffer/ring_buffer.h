#pragma once

#include <cstddef>
#include <vector>

class RingBuffer {
private:
    std::vector<int> buffer_;
    int size_;
    int front_;
    int rear_;
    int count_;

public:
    explicit RingBuffer(size_t capacity) {
        this->size_ = capacity;
        this->buffer_.resize(size_);
        this->front_ = 0;
        this->rear_ = -1;
        this->count_ = 0;
    }

    bool TryPush(int element) {
        if (count_ == size_) {
            return false;
        }
        rear_ = (rear_ + 1) % size_;
        buffer_[rear_] = element;
        count_++;
        return true;
    }

    size_t Size() const {
        return count_;
    }

    bool Empty() const {
        return count_ == 0;
    }

    bool TryPop(int *element) {
        if (count_ == 0) {
            return false;
        }
        *element = buffer_[front_];
        front_ = (front_ + 1) % size_;
        count_--;
        return true;
    }
};

