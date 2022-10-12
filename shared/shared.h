#pragma once

#include <random>
#include <vector>

class shared final {

public:
    static std::vector<uint8_t> random_bytes(int const);
};