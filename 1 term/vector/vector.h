#pragma once

#include <iterator>
#include <cstddef>

class Vector {
private:
    int* data_;
    size_t size_;
    size_t capacity_;

public:
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = ptrdiff_t;
        using pointer = int*;
        using reference = int&;
        pointer ptr_;

        Iterator() {
        }

        Iterator(int* pointer) : ptr_(pointer) {
        }

        int& operator*() const {
            return *ptr_;
        }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        int* operator->() {
            return ptr_;
        }

        Iterator operator++(value_type) {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(value_type) {
            Iterator temp = *this;
            --ptr_;
            return temp;
        }

        friend Iterator operator+(const Iterator& other, const difference_type num) {
            return Iterator(other.ptr_ + num);
        }

        Iterator& operator+=(difference_type val) {
            ptr_ += val;
            return *this;
        }

        friend Iterator operator-(const Iterator& other, const difference_type num) {
            return Iterator(other.ptr_ - num);
        }

        Iterator& operator-=(difference_type val) {
            ptr_ -= val;
            return *this;
        }

        difference_type operator-(const Iterator& other) const {
            return ptr_ - other.ptr_;
        }

        value_type& operator[](int index) const {
            return *(ptr_ + index);
        }

        friend Iterator operator+(int val, const Iterator& iter) {
            return Iterator(iter.ptr_ + val);
        }

        bool operator<(const Iterator& other) const {
            return ptr_ < other.ptr_;
        }

        bool operator==(const Iterator& other) const {
            return ptr_ == other.ptr_;
        }

        bool operator<=(const Iterator& other) const {
            return ptr_ <= other.ptr_;
        }

        bool operator>=(const Iterator& other) const {
            return ptr_ >= other.ptr_;
        }

        bool operator>(const Iterator& other) const {
            return ptr_ > other.ptr_;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr_;
        }
    };

    Iterator begin() {
        return Iterator(data_);
    }

    Iterator end() {
        return Iterator(data_ + size_);
    }

    Vector() : data_(nullptr), size_(0), capacity_(0) {
    }

    Vector(size_t size) : size_(size), capacity_(size) {
        data_ = new int[capacity_]();
    }

    Vector(std::initializer_list<int> list) : size_(list.size()), capacity_(list.size()) {
        data_ = new int[capacity_]();
        int* ptr = data_;
        for (const int& elem : list) {
            *ptr = elem;
            ++ptr;
        }
    }

    Vector(const Vector& second) : size_(second.size_), capacity_(second.capacity_) {
        data_ = new int[capacity_]();
        for (size_t index = 0; index < second.size_; ++index) {
            data_[index] = second.data_[index];
        }
    }

    Vector(Vector&& second) noexcept
        : data_(second.data_), size_(second.size_), capacity_(second.capacity_) {
        second.data_ = nullptr;
        second.size_ = 0;
        second.capacity_ = 0;
    }

    Vector& operator=(const Vector& second) {
        if (this != &second) {
            delete[] data_;
            size_ = second.size_;
            capacity_ = second.capacity_;
            data_ = new int[capacity_]();
            for (size_t index = 0; index < second.size_; ++index) {
                data_[index] = second.data_[index];
            }
        }
        return *this;
    }

    Vector& operator=(Vector&& second) noexcept {
        if (this != &second) {
            delete[] data_;
            data_ = second.data_;
            size_ = second.size_;
            capacity_ = second.capacity_;
            second.data_ = nullptr;
            second.size_ = 0;
            second.capacity_ = 0;
        }
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector& second) {
        std::swap(data_, second.data_);
        std::swap(size_, second.size_);
        std::swap(capacity_, second.capacity_);
    }

    int& operator[](size_t index) const {
        return data_[index];
    }

    int& operator[](size_t index) {
        return data_[index];
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        int* temp = new int[new_capacity]();
        for (size_t i = 0; i < size_; i++) {
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = new_capacity;
    }

    void PushBack(int value) {
        if (size_ == capacity_ && capacity_ == 0) {
            Reserve(capacity_ * 2 + 1);
        } else if (size_ == capacity_) {
            Reserve(capacity_ * 2);
        }

        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }
};
