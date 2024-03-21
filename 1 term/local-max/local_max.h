#pragma once

#include <stdexcept>

template <class Iterator>
Iterator LocalMax(Iterator first, Iterator last) {
    if (first == last) {
        return last;
    }
    Iterator current = first;
    ++current;
    if (current == last) {
        return first;
    }
    if (*current < *first) {
        return first;
    }
    while (current != last) {
        if (*first < *current) {
            auto tmp = current;
            tmp++;
            if (tmp == last) {
                return current;
            }
            if (current == last || *tmp < *current) {
                return current;
            }
        }
        ++first;
        ++current;
    }
    return last;
}

