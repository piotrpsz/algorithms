#include "bloom.h"
#include "../hash/murmur.h"
#include <iostream>

void BloomFilter::insert (std::string const& text) {
    for (int i = 0; i < k_; i++) {
        auto const index = Murmur::hash3(text, i) % m_;
        bs_.set(index);
    }
}

bool BloomFilter::contains (std::string const& text) {
    for (int i = 0; i < k_; i++) {
        auto const index = Murmur::hash3(text, i) % m_;
        if (!bs_.is_set(index))
            return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& s, BloomFilter const& bf) {
    s   << "      number of elements: " << bf.n_ << endl
        << "     false positive rate: " << bf.f_ << endl
        << "             bits number: " << bf.m_ << endl
        << "number of hash functions: " << bf.k_ << endl;
    return s;
}