#pragma once

#include <stdexcept>
#include <vector>
#include <cstddef>

size_t Gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return Gcd(b, a % b);
    }
}

void Rotate(std::vector<int>* data, size_t shift) {
    if (data->empty()) {
        return;
    }
    size_t n = data->size();
    shift = shift % n;
    size_t gcd = Gcd(shift, n);
    for (size_t i = 0; i < gcd; i++) {
        int tmp = data->at(i);
        int j = i;
        while (true) {
            size_t k = j + shift;
            if (k >= n) {
                k = k - n;
            }
            if (k == i) {
                break;
            }
            data->at(j) = data->at(k);
            j = k;
        }
        data->at(j) = tmp;
    }
}
