#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result;
    for (auto& item : items) {
        result.emplace_back(std::make_unique<T>(*item));
    }
    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::unordered_map<T, std::shared_ptr<T>> map_items;
    std::vector<std::shared_ptr<T>> result;
    for (auto& item : items) {
        if (!map_items.contains(*item)) {
            map_items[*item] = std::make_shared<T>(*item);
        }
        result.push_back(map_items[*item]);
    }
    return result;
}
