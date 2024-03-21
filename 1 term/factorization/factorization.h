#pragma once

#include <utility>
#include <vector>
#include <stdexcept>
#include <cmath>

std::vector<std::pair<int64_t, int>> Factorize(int64_t x) {
    std::vector<std::pair<int64_t, int>> factors;
    for (int i = 2; i <= sqrt(x); i++) {
        int count = 0;
        while (x % i == 0) {
            count++;
            x /= i;
        }
        if (count != 0) {
            factors.emplace_back(std::make_pair(i, count));
        }
    }
    if (x != 1) {
        factors.emplace_back(x, 1);
    }
    return factors;
}

