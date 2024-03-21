#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

std::unordered_map<int, std::string> ReverseMap(const std::unordered_map<std::string, int>& map) {
    std::unordered_map<int, std::string> result;
    for (const auto& pair : map) {
        result[pair.second] = pair.first;
    }
    return result;
}
