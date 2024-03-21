#pragma once

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>

int64_t CountPairs(const std::vector<int>& data, int x) {
    int64_t count = 0;
    std::unordered_map<int, int64_t> num_index_map;
    for (size_t i = 0; i < data.size(); i++) {
        int64_t number = static_cast<int64_t>(x) - static_cast<int64_t>(data[i]);
        if (num_index_map.find(number) != num_index_map.end()) {
            count += num_index_map[number];
        }
        num_index_map[data[i]]++;
    }
    return count;
}

