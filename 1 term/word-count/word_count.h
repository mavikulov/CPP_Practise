#pragma once

#include <string>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <unordered_set>

int DifferentWordsCount(const std::string& string) {
    bool empty = true;
    for (const auto& letter : string) {
        if (isalpha(letter)) {
            empty = false;
        }
    }
    if (empty) {
        return 0;
    }

    std::unordered_set<std::string> words;
    std::string word;
    for (char c : string) {
        if (std::isalpha(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            words.insert(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        words.insert(word);
    }

    return words.size();
}
