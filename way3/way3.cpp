#include "way3.hpp"
#include <sys/random.h>
#include <memory>

/*------- static constants:
-------------------------------------------------------------------*/
u32 const Way3::ERCON[12] = {0x0b0b, 0x1616, 0x2c2c, 0x5858, 0xb0b0, 0x7171, 0xe2e2, 0xd5d5, 0xbbbb, 0x6767, 0xcece, 0x8d8d};
u32 const Way3::DRCON[12] = {0xb1b1, 0x7373, 0xe6e6, 0xdddd, 0xabab, 0x4747, 0x8e8e, 0x0d0d, 0x1a1a, 0x3434, 0x6868, 0xd0d0};

Way3::Way3(void const* const key, const int nbytes) {
    if (nbytes != KEY_SIZE) {
        throw std::length_error("invalid key length");
    }

    memcpy(k, key, KEY_SIZE);
    memcpy(ki, key, KEY_SIZE);
    mu(theta(ki));
}

Way3::~Way3() {
    clear_bytes(k, KEY_SIZE);
    clear_bytes(ki, KEY_SIZE);
}

/**
 * \brief block encryption.
 * 
 * \param src 
 * \param dst 
 */
void Way3::encrypt_block(u32 const* const src, u32* const dst) const noexcept {
    u32 a[3];
    memcpy(a, src, BLOCK_SIZE);

    for (int i = 0; i < NMBR; i++) {
        a[0] ^= (k[0] ^ (ERCON[i] << 16));
        a[1] ^= k[1];
        a[2] ^= (k[2] ^ ERCON[i]);
    }
    a[0] ^= (k[0] ^ (ERCON[NMBR] << 16));
    a[1] ^= k[1];
    a[2] ^= (k[2] ^ ERCON[NMBR]);

    memcpy(dst, theta(a), BLOCK_SIZE);
}

/**
 * \brief block decryption
 * 
 * \param src 
 * \param dst 
 */
void Way3::decrypt_block(const u32* const src, u32* const dst) const noexcept {
    u32 a[3];
    mu((u32*)memcpy(a, src, BLOCK_SIZE));

    for (int i = 0; i < NMBR; i++) {
        a[0] ^= ki[0] ^ (DRCON[i] << 16);
        a[1] ^= ki[1];
        a[2] ^= ki[2] ^ DRCON[i];
        rho(a);
    }
    a[0] ^= ki[0] ^ (DRCON[NMBR] << 16);
    a[1] ^= ki[1];
    a[2] ^= ki[2] ^ DRCON[NMBR];

    memcpy(dst, mu(theta(a)), BLOCK_SIZE);
}


/********************************************************************
 *                                                                  *
 *                         P R I V A T E                            *
 *                                                                  *
 *******************************************************************/

u32* Way3::gamma(u32* const data) const noexcept {
    u32 const a0 = data[0];
    u32 const a1 = data[1];
    u32 const a2 = data[2];

    data[0] = (~a0) ^ ((~a1) & a2);
    data[1] = (~a1) ^ ((~a2) & a0);
    data[2] = (~a2) ^ ((~a0) & a1);

    return data;
}

u32* Way3::mu(u32* const data) const noexcept {
    u32 a0 = data[0];
    u32 a1 = data[1];
    u32 a2 = data[2];
    u32 b0 = 0;
    u32 b1 = 0;
    u32 b2 = 0;

    for (int i = 0; i < 32; i++) {
        b0 <<= 1; b1 <<= 1; b2 <<= 1;
        b0 |= (a2 & 1);
        b1 |= (a1 & 1);
        b2 |= a0 & 1;
        a0 >>= 1; a1 >>= 1; a2 >>= 1;
    }

    data[0] = b0;
    data[1] = b1;
    data[2] = b2;
    return data;
}

u32* Way3::theta(u32* const data) const noexcept {
    u32 const a0 = data[0];
    u32 const a1 = data[1];
    u32 const a2 = data[2];

    data[0] = a0 ^
            (a0 >> 16) ^ (a1 << 16) ^
            (a1 >> 16) ^ (a2 << 16) ^
            (a1 >> 24) ^ (a2 <<  8) ^
            (a2 >>  8) ^ (a0 << 24) ^
            (a2 >> 16) ^ (a0 << 16) ^
            (a2 >> 24) ^ (a0 <<  8);

    data[1] = a1 ^
            (a1 >> 16) ^ (a2 << 16) ^
            (a2 >> 16) ^ (a0 << 16) ^
            (a2 >> 24) ^ (a0 <<  8) ^
            (a0 >>  8) ^ (a1 << 24) ^
            (a0 >> 16) ^ (a1 << 16) ^
            (a0 >> 24) ^ (a1 << 8);

    data[2] = a2 ^
            (a2 >> 16) ^ (a0 << 16) ^
            (a0 >> 16) ^ (a1 << 16) ^
            (a0 >> 24) ^ (a1 <<  8) ^
            (a1 >>  8) ^ (a2 << 24) ^
            (a1 >> 16) ^ (a2 << 16) ^
            (a1 >> 24) ^ (a2 << 8);

    return data;
}

u32* Way3::pi_1(u32* const data) const noexcept {
    u32 const a0 = data[0];
    u32 const a2 = data[2];

    data[0] = (a0 >> 10) ^ (a0 << 22);
    data[2] = (a2 <<  1) ^ (a2 >> 31);

    return data;
}

u32* Way3::pi_2(u32* const data) const noexcept {
    u32 const a0 = data[0];
    u32 const a2 = data[2];

    data[0] = (a0 <<  1) ^ (a0 >> 31);
    data[2] = (a2 >> 10) ^ (a2 << 22);

    return data;
}

u32* Way3::rho(u32* const data) const noexcept {
    return pi_2(gamma(pi_1(theta(data))));
}


void Way3::clear_bytes(void* const data, int const nbytes) const {
    auto const buffer = new u8[4 * nbytes];
    random_bytes(buffer, 4 + nbytes);
    for (int i = 0, idx = 0; i < 4; i++, idx += nbytes) {
        std::memcpy(data, buffer + idx, nbytes);
    }
    delete []buffer;

    memset(data, 0x55, nbytes);
    memset(data, 0xaa, nbytes);
    memset(data, 0xff, nbytes);
    memset(data, 0x00, nbytes);
}

void Way3::random_bytes(u8* const buffer, int const nbytes) const {
    while (getentropy(buffer, nbytes));
} 
