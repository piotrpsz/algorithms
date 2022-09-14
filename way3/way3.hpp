#ifndef way3_hpp
#define way3_hpp

#include <cstdint>
#include <string>
#include <vector>

using u32 = uint32_t;
using u8 = uint8_t;

class Way3 final {
    static int const NMBR       = 11; // number of rounds
    static int const BLOCK_SIZE = 12; // in bytes (3 x uint32)
    static int const KEY_SIZE   = 12; // in bytes;
    static u32 const ERCON[12];
    static u32 const DRCON[12];

    u32 k[3];
    u32 ki[3];

public:
    explicit Way3(std::vector<u8> const& key) : Way3(key.data(), key.size()) {}
    explicit Way3(std::string const& key) : Way3(key.c_str(), key.size()) {}
    ~Way3();

    void encrypt_block(u32 const* const, u32* const) const noexcept;
    void decrypt_block(u32 const* const, u32* const) const noexcept;
    
private:
    Way3(void const* const, const int);

    u32* gamma(u32* const data) const noexcept;
    u32* mu(u32* const) const noexcept;
    u32* theta(u32* const) const noexcept;
    u32* pi_1(u32* const) const noexcept;
    u32* pi_2(u32* const) const noexcept;
    u32* rho(u32* const) const noexcept;

    void clear_bytes(void* const, int const) const;
    void random_bytes(u8* const, int const) const;
};

#endif // way3.hpp

