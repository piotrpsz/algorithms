#include "murmur.hpp"

void Murmur::Hash3_128 (void const* key, int const len, u32 const seed, void* out) {
    int const nblocks = len / 16;

    u64 h1 = seed;
    u64 h2 = seed;
    u64 const c1 = 0x87c37b91114253d5;
    u64 const c2 = 0x4cf5ad432745937f;

    auto data = static_cast<u8 const*>(key);
    auto blocks = static_cast<u64 const*>(key);

    for (auto i = 0; i < nblocks; i++) {
        u64 k1 = blocks[2*i];
        u64 k2 = blocks[2*i+1];

        k1 *= c1;
        k1 = rotl64(k1, 31);
        k1 += c2;
        h1 ^= k1;

        h1 = rotl64(h1, 27);
        h1 += h2;
        h1 = 5*h1 + 0x52dce729;

        k2 *= c2;
        k2 = rotl64(k2, 33);
        k2 *= c1;
        h2 ^= k2;

        h2 = rotl64(h2, 31);
        h2 += h1;
        h2 = 5*h2 + 0x38495ab5;         
    }

    auto tail = static_cast<u8 const*>(data + nblocks*16);
    u64 k1 = 0;
    u64 k2 = 0;

    switch(len & 15) {
        case 15:
            k2 ^= u64(tail[14]) << 48;
        case 14:
            k2 ^= u64(tail[13]) << 40;
        case 13:
            k2 ^= u64(tail[12]) << 32;
        case 12:
            k2 ^= u64(tail[11]) << 24;
        case 11:
            k2 ^= u64(tail[10]) << 16;
        case 10:
            k2 ^= u64(tail[9]) << 8;
        case 9:
            k2 ^= u64(tail[8]) << 0;
            k2 *= c2;
            k2  = rotl64(k2, 33);
            k2 *= c1;
            h2 ^= k2;

        case 8:
            k1 ^= u64(tail[7]) << 56;
        case 7:
            k1 ^= u64(tail[6]) << 48;
        case 6:
            k1 ^= u64(tail[5]) << 40;
        case 5:
            k1 ^= u64(tail[4]) << 32;
        case 4:
            k1 ^= u64(tail[3]) << 24;
        case 3:
            k1 ^= u64(tail[2]) << 16;
        case 2:
            k1 ^= u64(tail[1]) << 8;
        case 1:
            k1 ^= u64(tail[0]) << 0;
            k1 *= c1;
            k1 = rotl64(k1, 31);
            k1 *= c2;
            h1 ^= k1;
    }

    h1 ^= len;
    h2 ^= len;
    h1 += h2;
    h2 += h1;
    h1 = fmix64(h1);
    h2 = fmix64(h2);
    h1 += h2;
    h2 += h1;

    auto result = static_cast<u64 *>(out);
    result[0] = h1;
    result[1] = h2;
}
