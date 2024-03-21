#pragma once

#include <cstddef>
#include <algorithm>
#include <vector>

template <class Functor>
class ReverseUnaryFunctor {
private:
    Functor func_;

public:
    explicit ReverseUnaryFunctor(const Functor& f) : func_(f) {
    }

    template <typename T>
    bool operator()(const T& value) const {
        return !func_(value);
    }
};

template <class Functor>
class ReverseBinaryFunctor {
private:
    Functor func_;

public:
    explicit ReverseBinaryFunctor(const Functor& f) : func_(f) {
    }

    template <typename T>
    bool operator()(const T& a, const T& b) const {
        return func_(b, a);
    }
};

auto MakeReverseUnaryFunctor(auto functor) {
    return ReverseUnaryFunctor{functor};
}

auto MakeReverseBinaryFunctor(auto functor) {
    return ReverseBinaryFunctor{functor};
}

template <class Iterator>
size_t ComparisonsCount(Iterator first, Iterator last) {
    size_t count = 0;
    std::sort(first, last,
              [&count](typename std::iterator_traits<Iterator>::value_type left,
                       typename std::iterator_traits<Iterator>::value_type right) {
                  ++count;
                  return left < right;
              });
    return count;
}

