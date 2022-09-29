
#include "bitset.hpp"
#include <sstream>
#include <bitset>

using namespace std;

ostream& operator<<(ostream& s, Bitset const& bs) {
    stringstream ss;

    for (auto const& item : bs.data_) {
        bitset<8> const b{item};
        ss << b.to_string() << " ";
    }
    s << ss.str() << endl;

    auto i = 0;
    for (auto const& item : bs.data_) {
        bitset<8> const b{item};
        s << "[" << i++ << "] " << b.to_string() << endl;
    }
    return s;
}