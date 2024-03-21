#pragma once

#include <stdexcept>

template <class Iterator, class Predicate>
constexpr Iterator Find(Iterator first, Iterator last, Predicate pred) {
    for (; first != last; first++) {
        if (!pred(*first)) {
            return first;
        }
    }
    return last;
}

template <class Iterator, class Predicate>
Iterator Partition(Iterator first, Iterator last, Predicate pred) {
    first = Find(first, last, pred);
    if (first == last) {
        return first;
    }
    for (auto i = std::next(first); i != last; ++i) {
        if (pred(*i)) {
            std::swap(*i, *first);
            ++first;
        }
    }
    return first;
}
