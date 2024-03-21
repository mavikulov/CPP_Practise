#pragma once

#include <string>
#include <string>
#include <iostream>

class WeakPtr;

struct Block {
    int strong = 0;
    int week = 0;
};

class SharedPtr {
    friend class WeakPtr;

public:
    SharedPtr() {
        data_ = nullptr;
        counter_ = nullptr;
    }

    SharedPtr(std::string* data) : data_(data), counter_(new Block({1, 0})) {
    }

    SharedPtr(const WeakPtr& ptr);

    SharedPtr(const SharedPtr& second) {
        data_ = second.data_;
        counter_ = second.counter_;
        if (counter_) {
            ++(counter_->strong);
        }
    }

    SharedPtr(SharedPtr&& second) {
        data_ = second.data_;
        counter_ = second.counter_;
        second.data_ = nullptr;
        second.counter_ = nullptr;
    }

    ~SharedPtr() {
        if (!counter_) {
            return;
        }
        if (--(counter_->strong) == 0) {
            delete data_;
            if (counter_->week == 0) {
                delete counter_;
            }
        }
    }

    SharedPtr& operator=(const SharedPtr& second) {
        if (second.data_ == data_ && second.counter_ == counter_) {
            return *this;
        }
        SharedPtr copy(second);
        std::swap(data_, copy.data_);
        std::swap(counter_, copy.counter_);
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& second) {
        if (second.data_ == data_ && second.counter_ == counter_) {
            return *this;
        }
        std::swap(second.counter_, counter_);
        std::swap(second.data_, data_);
        return *this;
    }

    void Reset(std::string* ptr) {
        if (counter_ && counter_->strong == 1) {
            delete data_;
            data_ = ptr;
        } else {
            --(counter_->strong);
            data_ = ptr;
            counter_ = new Block({1, 0});
        }
    }

    std::string& operator*() const {
        return *data_;
    }

    std::string* operator->() const {
        return data_;
    }

    std::string* Get() const {
        return data_;
    }

private:
    std::string* data_ = nullptr;
    Block* counter_ = nullptr;
};

class WeakPtr {
public:
    WeakPtr() = default;

    WeakPtr(const SharedPtr& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        if (counter_) {
            ++counter_->week;
        }
    }

    bool IsExpired() const {
        if (counter_) {
            return counter_->strong <= 0;
        }
        return true;
    }

    SharedPtr Lock() {
        SharedPtr result;
        if (!IsExpired()) {
            result.counter_ = counter_;
            result.data_ = data_;
            ++counter_->strong;
        }
        return result;
    }

    WeakPtr(const WeakPtr& second) : data_(second.data_), counter_(second.counter_) {
        if (counter_) {
            ++counter_->week;
        }
    }

    WeakPtr(WeakPtr&& second) : data_(second.data_), counter_(second.counter_) {
        second.data_ = nullptr;
        second.counter_ = nullptr;
    }

    WeakPtr& operator=(const WeakPtr& second) {
        WeakPtr new_ptr(second);
        std::swap(data_, new_ptr.data_);
        std::swap(counter_, new_ptr.counter_);
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& second) {
        std::swap(second.counter_, counter_);
        std::swap(second.data_, data_);
        return *this;
    }

    ~WeakPtr() {
        if (counter_) {
            --counter_->week;
            if (counter_->week == 0 && counter_->strong == 0) {
                delete counter_;
            }
        }
    }

    std::string& operator*() const {
        return *data_;
    }

    std::string* operator->() const {
        return data_;
    }

    std::string* Get() const {
        return data_;
    }

    Block* GetBlock() const {
        return counter_;
    }

private:
    std::string* data_ = nullptr;
    Block* counter_ = nullptr;
};

SharedPtr::SharedPtr(const WeakPtr& ptr) : data_(ptr.Get()), counter_(ptr.GetBlock()) {
    if (ptr.IsExpired()) {
        data_ = nullptr;
    }
    if (counter_) {
        ++(counter_->strong);
    }
}
