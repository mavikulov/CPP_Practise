#pragma once

#include <vector>
#include <stdexcept>

void FilterEven(std::vector<int>* data) {
    int rp = 0, wp = 0, sz = data->size();
    for (; rp < sz; ++rp) {
        if ((*data)[rp] % 2 == 0) {
            (*data)[wp] = (*data)[rp];
            wp++;
        }
    }
    data->resize(wp);
}
