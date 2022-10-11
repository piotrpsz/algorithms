#pragma once

#include <cmath>
#include <string>
#include "../bitset/bitset.h"

class BloomFilter final {
public:
    BloomFilter (uint const n, double const f)
    : n_ {n}
    , f_ {f}
    , m_ {how_many_bits()}
    , k_ {how_many_hash_functions()}
    , bs_ {m_}
    {}

    ~BloomFilter () = default;
    BloomFilter (BloomFilter const&) = delete;
    BloomFilter (BloomFilter&&) = delete;
    BloomFilter& operator= (BloomFilter const&) = delete;
    BloomFilter& operator= (BloomFilter&&) = delete;

    void insert (std::string const&);
    bool contains (std::string const&);

private:
    uint how_many_bits() {
        return static_cast<uint>(-log(f_) * n_ / pow(log(2), 2));
    }
    uint how_many_hash_functions() {
        return static_cast<uint>(m_ * log(2) / n_);
    }

private:
    uint n_;        // number of elements
    double f_;      // false positive rate
    uint m_;        // number of bits int a Bloom filter
    uint k_;        // number of hash functions
    Bitset bs_;     // bit set

    friend std::ostream& operator<<(std::ostream&, BloomFilter const&);
};
