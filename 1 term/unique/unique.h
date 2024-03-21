#pragma once

#include <vector>
#include <stdexcept>
#include <set>

std::vector<int> Unique(const std::vector<int>& data) {
    std::set<int> unique_elements(data.begin(), data.end());
    return std::vector<int>(unique_elements.begin(), unique_elements.end());
}
