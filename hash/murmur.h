#pragma once

#include <stdlib.h>
#include <string>

using i8 = int8_t;
using u8 = uint8_t;
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;

class Murmur {
public:
    static void Hash3_128 (void const*, int const, u32 const, void*);
    static u32 hash3(std::string const&, u32 const = 0);
    static u32 hash3_x86_32 (void const* const, int const, u32 const);

private:
    static u64 rotl64 (u64 const x, i8 const r) {
        return (x << r) | (x >> (64 - r));
    }
    static u32 rotl32 (u32 const x, i8 const r) {
        return (x << r) | (x >> (32 - r));
    }
    static u64 fmix64 (u64 k) {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccd;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53;
        k ^= k >> 33;
        return k;
    }
    static u32 fmix32 (u32 h) {
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;
        return h;
    }
};
