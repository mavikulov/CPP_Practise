#pragma once

#include <stdexcept>

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& value) {
    if (first == last) {
        return first;
    }
    Iterator result = last;
    --last;
    if (first == last) {
        if (*last == value) {
            return first;
        } else {
            return result;
        }
    }
    while (last != first) {
        if (*last == value) {
            return last;
        }
        --last;
    }
    return result;
}
