#pragma once

#include <string>
#include <cstddef>
#include <memory>
#include <vector>

struct State {
    int ref_count;
    std::vector<std::string> data;

    State() : ref_count(1) {
    }
};

class COWVector {
public:
    COWVector() : state_(std::make_shared<State>()) {
    }

    COWVector(const COWVector& other) : state_(other.state_) {
        state_->ref_count++;
    }

    COWVector& operator=(const COWVector& other) {
        if (this != &other) {
            state_->ref_count--;
            if (state_->ref_count == 0) {
                state_.reset();
            }
            state_ = other.state_;
            state_->ref_count++;
        }
        return *this;
    }

    ~COWVector() {
        state_->ref_count--;
        if (state_->ref_count == 0) {
            state_.reset();
        }
    }

    size_t Size() const {
        return state_->data.size();
    }

    void Resize(size_t size) {
        if (size == this->Size()) {
            return;
        }
        if (state_->ref_count > 1) {
            state_->ref_count--;
            state_ = std::make_shared<State>(*state_);
        }
        state_->data.resize(size);
    }

    const std::string& Get(size_t at) const {
        return state_->data.at(at);
    }

    const std::string& Back() const {
        return state_->data.back();
    }

    void PushBack(const std::string& value) {
        if (state_->ref_count > 1) {
            state_->ref_count--;
            state_ = std::make_shared<State>(*state_);
        }
        state_->data.push_back(value);
    }

    void Set(size_t at, const std::string& value) {
        if (state_->ref_count > 1) {
            state_->ref_count--;
            state_ = std::make_shared<State>(*state_);
        }
        state_->data.at(at) = value;
    }

private:
    std::shared_ptr<State> state_;
};
