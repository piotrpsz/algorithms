#pragma once

#include <random>
#include <vector>

using u8 = uint8_t;
using u64 = uint64_t;

class shared final {

public:
    static std::vector<u8> random_bytes(int const);
    static void random_uint64_to_file(int const, std::string const);
    static std::string home_dir();
};