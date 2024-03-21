#pragma once
#include <vector>

struct Sum {
    template <class T>
    T operator()(const T& first, const T& second) const {
        return first + second;
    }
};

struct Prod {
    template <class T>
    T operator()(const T& first, const T& second) const {
        return first * second;
    }
};

struct Concat {
    template <class T>
    std::vector<T> operator()(const std::vector<T>& first, const std::vector<T>& second) const {
        std::vector<T> result = first;
        result.insert(result.end(), second.begin(), second.end());
        return result;
    }
};

class Length {
private:
    std::size_t* length_;

public:
    Length(std::size_t* len) : length_(len) {
    }

    template <class T>
    T operator()(const T&, const T&) const {
        (*length_)++;
        return T{};
    }
};

template <class Iterator, class T, class BinaryOp>
T Fold(Iterator first, Iterator last, T init, BinaryOp func) {
    for (Iterator it = first; it != last; ++it) {
        init = func(init, *it);
    }
    return init;
}

