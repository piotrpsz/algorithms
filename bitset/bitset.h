#pragma once

#include <cstdint>
#include <memory>
#include <iostream>
#include <vector>


using pack = uint8_t;
using namespace std;

class Bitset final {
    vector<pack> data_;
    ssize_t const block_size = 8 * sizeof(pack);
    uint m_;

public:

    /**
    * @brief Construct a new Bitset object
    * @param m - requested number of bits
    */
    Bitset(uint const m) : m_(m - 1) {
        ssize_t n = m / block_size;
        if (m % block_size)
            ++n;
        data_ = vector<pack>(n, 0);
    }

    /**
     * @brief sets nth bit
     * @param idx bit position
     */
    int set(int const idx) noexcept {
        if (idx < 0 || idx > m_)
            return 0;

        auto const block_number = idx / block_size;
        auto const shift = (block_size - 1) - (idx - block_number * block_size);
        data_[block_number] |= (1 << shift);
        return 1;
    }

    /**
     * @brief clears nth bit
     * @param idx bit position
     */
    int unset(int const idx) noexcept {
        if (idx < 0 || idx > m_)
            return 0;

        auto const block_number = idx / block_size;
        auto const shift = (block_size - 1) - (idx - block_number * block_size);
        data_[block_number] &= ~(1 << shift);
        return 1;
    }

    /**
     * @brief toggles nth bit
     * @param idx bit position
     */
    int toggle(int const idx) noexcept {
        if (idx < 0 || idx > m_)
            return 0;

        auto const block_number = idx / block_size;
        auto const shift = (block_size - 1) - (idx - block_number * block_size);
        data_[block_number] ^= 1 << shift;
        return 1;
    }

    /**
     * @brief checks if nth bit is set
     * @param idx bit position
     */
    int is_set(int const idx) const noexcept {
        if (idx < 0 || idx > m_)
            return 0;

        auto const block_number = idx / block_size;
        auto const shift = (block_size - 1) - (idx - block_number * block_size);
        auto const bit = (data_[block_number] >> shift) & 1;
        return bit;
    }

    friend std::ostream& operator<<(std::ostream&, Bitset const&);
};


