#pragma once

#include <stdexcept>

void Swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void Sort3(int* a, int* b, int* c) {
    if (*a <= *b) {
        if (*b <= *c) {
            return;
        } else {
            if (*a <= *c) {
                Swap(b, c);
            } else {
                Swap(a, c);
                Swap(b, c);
            }
        }
    } else {
        if (*b <= *c) {
            if (*a <= *c) {
                Swap(a, b);
            } else {
                Swap(a, b);
                Swap(b, c);
            }
        } else {
            Swap(a, c);
        }
    }
}
