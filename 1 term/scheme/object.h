#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <error.h>

class Object : public std::enable_shared_from_this<Object> {
public:
    virtual ~Object() = default;
    virtual std::shared_ptr<Object> Eval() = 0;
    virtual std::string Serialize() = 0;
};

class Number : public Object {
private:
    int value_;

public:
    Number(int value) : value_(value) {
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Number>(value_);
    }

    std::string Serialize() override {
        return std::to_string(GetValue());
    }

    int GetValue() const {
        return value_;
    }
};

class Function : public Object {
private:
    std::function<std::shared_ptr<Object>(std::vector<std::shared_ptr<Object>>&)> func_;

public:
    Function(std::string name);
    std::shared_ptr<Object> Eval() override {
        return nullptr;
    }

    std::string Serialize() override {
        return "";
    }

    std::shared_ptr<Object> Apply(std::vector<std::shared_ptr<Object>> args) {
        return func_(args);
    }
};

class Symbol : public Object {
private:
    std::string name_;

public:
    Symbol(std::string name) : name_(name) {
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Function>(name_);
    }

    std::string Serialize() override {
        return GetName();
    }

    const std::string& GetName() const {
        return name_;
    }
};

class Cell : public Object {
private:
    std::shared_ptr<Object> first_ = nullptr;
    std::shared_ptr<Object> second_ = nullptr;

public:
    Cell() {
    }

    std::shared_ptr<Object>& GetFirst() {
        return first_;
    }

    std::shared_ptr<Object>& GetSecond() {
        return second_;
    }

    std::shared_ptr<Object> Eval() override;
    std::string Serialize() override;
};

class Bool : public Object {
private:
    bool flag_;

public:
    Bool(std::string val) {
        if (val == "#t") {
            flag_ = true;
        } else {
            flag_ = false;
        }
    }

    Bool(bool flag) {
        flag_ = flag;
    }

    std::shared_ptr<Object> Eval() override {
        return std::make_shared<Bool>(GetFlag());
    }

    std::string Serialize() override {
        if (GetFlag()) {
            return "#t";
        } else {
            return "#f";
        }
    }

    bool GetFlag() {
        return flag_;
    }
};

class Dot : public Object {
public:
    Dot() {
    }

    std::shared_ptr<Object> Eval() override;

    std::string Serialize() override;
};

template <class T>
std::shared_ptr<T> As(const std::shared_ptr<Object>& obj) {
    return std::dynamic_pointer_cast<T>(obj);
}

template <class T>
bool Is(const std::shared_ptr<Object>& obj) {
    auto cast_ptr = std::dynamic_pointer_cast<T>(obj);
    if (cast_ptr) {
        return true;
    }
    return false;
}
