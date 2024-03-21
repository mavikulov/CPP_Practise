#pragma once

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

class StaticMap {
private:
    std::vector<std::pair<std::string, std::string>> hash_map_;

public:
    explicit StaticMap(const std::vector<std::pair<std::string, std::string>>& items) {
        hash_map_ = items;
        std::sort(hash_map_.begin(), hash_map_.end());
    }

    bool Find(const std::string& key, std::string* value) const {
        auto pos = std::lower_bound(hash_map_.begin(), hash_map_.end(),
                                    std::make_pair(key, std::string("")));
        if (pos != hash_map_.end() && (*pos).first == key) {
            (*value) = (*pos).second;
            return true;
        }
        return false;
    }
};
