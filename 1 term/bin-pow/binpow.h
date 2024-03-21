#pragma once

#include <stdexcept>

int BinPow(int a, int64_t b, int c) {
    int64_t res = 1;
    int64_t a_copy = a;
    while (b > 0) {
        if (b & 1) {
            res = (res % c * a_copy % c) % c;
        }
        a_copy = ((a_copy % c) * (a_copy % c)) % c;
        b >>= 1;
    }
    return res;
}
