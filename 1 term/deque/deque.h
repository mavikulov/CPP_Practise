#pragma once

#include <cstddef>
#include <initializer_list>
#include <algorithm>

class Node {
private:
    const size_t node_size_ = 512;
    int* data_ = nullptr;

public:
    Node() {
        data_ = new int[node_size_];
    }

    ~Node() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }

    Node(int value) : Node() {
        for (size_t ind = 0; ind < node_size_; ++ind) {
            data_[ind] = value;
        }
    }

    int& operator[](size_t index) {
        return data_[index];
    }

    int operator[](size_t index) const {
        return data_[index];
    }

    Node(const Node& second) : Node() {
        for (size_t ind = 0; ind < node_size_; ++ind) {
            data_[ind] = second.data_[ind];
        }
    }

    Node& operator=(Node& second) {
        delete[] data_;
        data_ = new int[node_size_];
        for (size_t ind = 0; ind < node_size_; ++ind) {
            data_[ind] = second.data_[ind];
        }
        return *this;
    }

    Node& operator=(int value) {
        delete[] data_;
        data_ = new int[node_size_];
        for (size_t ind = 0; ind < node_size_; ++ind) {
            data_[ind] = value;
        }
        return *this;
    }
};

class Deque {
private:
    size_t size_ = 0;
    const size_t chunk_size_ = 512;
    Node** data_ptr_ = nullptr;
    size_t start_ = 0;
    size_t chunks_count_ = 0;

    auto ReallocateFront(size_t prev_count) {
        auto memory = new Node*[chunks_count_ + prev_count];
        if (data_ptr_ != nullptr) {
            for (size_t ind = 0; ind < chunks_count_; ++ind) {
                memory[prev_count + ind] = data_ptr_[ind];
            }
            delete[] data_ptr_;
        }
        for (size_t i = 0; i < prev_count; ++i) {
            memory[i] = new Node(0);
        }
        return memory;
    }

    auto Reallocate(size_t prev_count) {
        auto memory = new Node*[chunks_count_ + prev_count];
        if (data_ptr_ != nullptr) {
            for (size_t i = 0; i < chunks_count_; ++i) {
                memory[i] = data_ptr_[i];
            }
            delete[] data_ptr_;
        }
        for (size_t i = chunks_count_; i < chunks_count_ + prev_count; ++i) {
            memory[i] = new Node(0);
        }
        return memory;
    }

public:
    Deque() = default;

    Deque(size_t size) : size_(size), data_ptr_(nullptr), start_(0) {
        bool flag = size_ % chunk_size_ != 0;
        chunks_count_ = size_ / chunk_size_ + flag;
        data_ptr_ = new Node*[chunks_count_];
        for (size_t i = 0; i < chunks_count_; ++i) {
            data_ptr_[i] = new Node(0);
        }
    }

    ~Deque() {
        if (data_ptr_ != nullptr) {
            for (size_t ind = 0; ind < chunks_count_; ++ind) {
                delete data_ptr_[ind];
            }
            delete[] data_ptr_;
        }
        start_ = 0;
        data_ptr_ = nullptr;
        chunks_count_ = 0;
        size_ = 0;
    }

    void Clear() {
        this->~Deque();
    }

    size_t Size() const {
        return size_;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void PopFront() {
        if (size_ > 0) {
            --size_;
            ++start_;
        }
    }

    int& operator[](size_t index) {
        size_t i = (start_ + index) % chunk_size_;
        size_t j = (start_ + index) / chunk_size_;
        return (*data_ptr_[j])[i];
    }

    int operator[](size_t index) const {
        size_t i = (start_ + index) % chunk_size_;
        size_t j = (start_ + index) / chunk_size_;
        return (*data_ptr_[j])[i];
    }

    Deque(const std::initializer_list<int>& list) : size_(list.size()), data_ptr_(nullptr) {
        bool flag = size_ % chunk_size_ != 0;
        chunks_count_ = size_ / chunk_size_ + flag;
        data_ptr_ = new Node*[chunks_count_];
        for (size_t i = 0; i < chunks_count_; ++i) {
            data_ptr_[i] = new Node();
        }
        size_t iterator = 0;
        for (const auto& elem : list) {
            (*this)[iterator] = elem;
            ++iterator;
        }
    }

    void Swap(Deque& second) {
        std::swap(size_, second.size_);
        std::swap(start_, second.start_);
        std::swap(data_ptr_, second.data_ptr_);
        std::swap(chunks_count_, second.chunks_count_);
    }

    Deque(const Deque& second)
        : size_(second.size_),
          data_ptr_(nullptr),
          start_(second.start_),
          chunks_count_(second.chunks_count_) {
        data_ptr_ = new Node*[chunks_count_];
        for (size_t i = 0; i < chunks_count_; ++i) {
            data_ptr_[i] = new Node(*(second.data_ptr_[i]));
        }
    }

    Deque& operator=(const Deque& second) {
        if (this == &second) {
            return *this;
        }
        Clear();
        data_ptr_ = new Node*[second.chunks_count_];
        for (size_t ind = 0; ind < second.chunks_count_; ++ind) {
            data_ptr_[ind] = new Node(*(second.data_ptr_[ind]));
        }
        size_ = second.size_;
        start_ = second.start_;
        chunks_count_ = second.chunks_count_;
        return *this;
    }

    Deque(Deque&& second) : Deque() {
        Swap(second);
    }

    Deque& operator=(Deque&& second) {
        Clear();
        Swap(second);
        return *this;
    }

    void PushBack(int value) {
        if (start_ + size_ != chunk_size_ * chunks_count_) {
            (*this)[size_] = value;
            ++size_;
            return;
        }
        size_t prev_count = ((chunks_count_ != 0) ? chunks_count_ : 1);
        data_ptr_ = Reallocate(prev_count);
        (*this)[size_] = value;
        ++size_;
        chunks_count_ += prev_count;
    }

    void PushFront(int value) {
        if (start_ != 0) {
            --start_;
            (*this)[0] = value;
            ++size_;
            return;
        }
        size_t prev_count = ((chunks_count_ != 0) ? chunks_count_ : 1);
        start_ += prev_count * chunk_size_;
        data_ptr_ = ReallocateFront(prev_count);
        chunks_count_ += prev_count;
        --start_;
        (*this)[0] = value;
        ++size_;
    }
};

