#pragma once

#include <vector>
#include <stdexcept>

void Solve(std::vector<int>& nums, std::vector<int>& output, std::vector<std::vector<int>>& ans,
           int index, std::vector<int> used) {
    if (output.size() == nums.size()) {
        ans.push_back(output);
        return;
    }

    for (size_t i = 0; i < nums.size(); i++) {
        if (!used[i]) {
            used[i] = 1;
            output.push_back(nums[i]);
            Solve(nums, output, ans, (index + 1) % nums.size(), used);
            output.pop_back();
            used[i] = 0;
        }
    }
}

std::vector<std::vector<int>> GeneratePermutations(size_t len) {
    std::vector<int> first_perm;
    for (size_t i = 0; i < len; i++) {
        first_perm.push_back(i);
    }
    std::vector<int> output;
    std::vector<int> used(first_perm.size(), 0);
    std::vector<std::vector<int>> result;
    Solve(first_perm, output, result, 0, used);
    return result;
}
