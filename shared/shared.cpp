#include "shared.h"
#include <array>
#include <algorithm>
#include <iostream>

using namespace std;

vector<uint8_t> shared::random_bytes(int const n) {
    random_device rd;
    array<int, mt19937::state_size> seed_data{};
    generate(begin(seed_data), end(seed_data), ref(rd));
    seed_seq seq (begin(seed_data), end(seed_data));
    
    auto mtgen = mt19937{seq};
    auto ud = uniform_int_distribution<>{0, 255};

    vector<uint8_t> data;
    data.reserve(n);
    
    for (auto i = 0; i < n; i++) {
        data.push_back(static_cast<uint8_t>(ud(mtgen)));
    }
    return data;
}