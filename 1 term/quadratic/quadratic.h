#pragma once

#include <stdexcept>
#include <cmath>

enum class RootCount { kZero, kOne, kTwo, kInf };

struct Roots {
    RootCount count;
    double first;
    double second;
};

Roots SolveQuadratic(int a, int b, int c) {
    Roots result;
    if (a == 0 && b == 0 && c == 0) {
        result.count = RootCount::kInf;
        return result;
    }

    if (c != 0 && a == 0 && b == 0) {
        result.count = RootCount::kZero;
        return result;
    }

    if (a != 0 && b == 0 && c == 0) {
        result.count = RootCount::kOne;
        result.first = 0;
        return result;
    }

    if (a == 0 && b != 0 && c != 0) {
        result.count = RootCount::kOne;
        result.first = static_cast<double>(-c) / static_cast<double>(b);
        return result;
    }

    int64_t d = b * b - 4 * a * c;
    if (d < 0) {
        result.count = RootCount::kZero;
        return result;
    }

    if (d == 0) {
        result.count = RootCount::kOne;
        result.first = (-b + sqrt(d)) / (2 * a);
        return result;
    }

    result.count = RootCount::kTwo;
    double first_root = static_cast<double>(-b - sqrt(d)) / static_cast<double>(2 * a);
    double second_root = static_cast<double>(-b + sqrt(d)) / static_cast<double>(2 * a);
    result.first = std::min(first_root, second_root);
    result.second = std::max(first_root, second_root);
    return result;
}

