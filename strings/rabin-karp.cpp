#include "rabin-karp.hpp"

namespace RabinKarp {
    using namespace std;

    uint32_t hash(string const& text) {
        uint32_t sum = 0;

        for (auto i = 0; i < text.size(); i++)
            sum += text[i];

        return sum;
    }

    bool contains(string const& text, string const& subtext, int const from_pos) {
        return index_of(text, subtext, from_pos) != -1;
    }

    int index_of(string const& text, string const& subtext, int const from_pos) {
        auto const n = subtext.size();  // window size
        auto const subhash = hash(subtext);
        auto window_hash = hash(text.substr(from_pos, n));

        for (auto i = from_pos; i < text.size(); i++) {
            if (window_hash == subhash)
                return i;
            window_hash -= text[i];
            window_hash += text[i + n];
        }

        return -1;
    }
}