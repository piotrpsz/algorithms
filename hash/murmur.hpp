#pragma once

#include <stdlib.h>

using i8 = int8_t;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;

class Murmur {
public:
    static void Hash3_128 (void const*, int const, u32 const, void*);

private:
    static u64 rotl64 (u64 const x, i8 const r) {
        return (x << r) | (x >> (64 - r));
    }
    static u64 fmix64 (u64 k) {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccd;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53;
        k ^= k >> 33;
        return k;
    }
};
