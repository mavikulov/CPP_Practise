#pragma once

#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class LruCache {
public:
    explicit LruCache(size_t max_size) : max_size_(max_size) {
    }
    LruCache(const LruCache&) = delete;
    LruCache& operator=(const LruCache&) = delete;

    void Set(const std::string& key, const std::string& value) {
        if (cache_map_.find(key) != cache_map_.end()) {
            cache_map_[key]->second = value;
            cache_list_.splice(cache_list_.begin(), cache_list_, cache_map_[key]);
        } else {
            if (cache_map_.size() >= max_size_) {
                auto it = cache_list_.end();
                it--;
                cache_map_.erase(it->first);
                cache_list_.pop_back();
            }
            cache_list_.push_front({key, value});
            cache_map_[key] = cache_list_.begin();
        }
    }

    bool Get(const std::string& key, std::string* value) {
        if (cache_map_.find(key) == cache_map_.end()) {
            return false;
        }
        cache_list_.splice(cache_list_.begin(), cache_list_, cache_map_[key]);
        *value = cache_map_[key]->second;
        return true;
    }

private:
    size_t max_size_;
    std::unordered_map<std::string,
                       typename std::list<std::pair<std::string, std::string>>::iterator>
        cache_map_;
    std::list<std::pair<std::string, std::string>> cache_list_;
};
