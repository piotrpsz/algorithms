#include "roman.hpp"
#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

map<char, int> const Roman::ROMAN = {
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    {'I', 1}
};

/**
 * \brief Converts roman number to integer value.
 * 
 * \param text roman number
 * \return pair<bool, int> status flag and value
 */
pair<bool, int> Roman::integer(string const& text) {
    if (text.empty()) 
        return make_pair(false, -1);

    int previous = 0;
    int value = 0;

    auto const it = ROMAN.find(text[0]);
    if (it == ROMAN.end())
        return make_pair(false, -1);
    
    previous = it->second;
    for (int i = 1; i < text.size(); i++) {
        auto const it = ROMAN.find(text[i]);
        if (it == ROMAN.end())
            return make_pair(false, -1);

        auto const current = it->second;
        value += (previous < current) ? -previous : previous;
        previous = current;
    }

    return make_pair(true, previous + value);
}

/**
 * /brief Converts integer value to roman number.
 * 
 * @param n value to convert
 * @return string roman number
 */
string Roman::roman(int n) {
    if (n <= 0) return "";

    stringstream ss;
    
    while(n >= 1000) {
        n -= 1000;
        ss << 'M';
    }

    static char const mdc[3][3] {
        {'X', 'V', 'I'},
        {'C', 'L', 'X'},
        {'M', 'D', 'C'} 
    };

    auto order = 2;
    auto v9 = 900;
    auto v5 = 500;
    auto v4 = 400;
    auto v1 = 100;

    while (n && order >= 0) {
        auto const [m, d, c] = mdc[order];
        
        if (n/v1 == 9) {
            n -= v9;
            ss << c << m;
        }
        if (n/v1 == 4) {
            n -= v4;
            ss << c << d;
        }
        if ((n/v1 >= 5) && (n/v1 <= 8)) {
            n -= v5;
            ss << d;
        }
        while (n >= v1) {
            n -= v1;
            ss << c;
        }

        v9 /= 10;
        v5 /= 10;
        v4 /= 10;
        v1 /= 10;
        --order;
    }

    return ss.str();
}

void Roman::test_integer() {
    struct Data_ {
        string rom;
        int expected;
    } const tt [] = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"VII", 7},
        {"VIII", 8},
        {"IX", 9},
        {"X", 10},
        {"XI", 11},
        {"XII", 12},
        {"XIII", 13},
        {"XIV", 14},
        {"XV", 15},
        {"XVI", 16},
        {"XVII", 17},
        {"XVIII", 18},
        {"XIX", 19},
        {"XX", 20},
        {"XXX", 30},
        {"XL", 40},
        {"XLIV", 44},
        {"L", 50},
        {"LVI", 56},
        {"LXXX", 80},
        {"DCC", 700},
        {"CMII", 902},
        {"CMXCIX", 999},
        {"MCCXXXIV", 1234},
        {"MCDXLVI", 1446},
        {"MCMXCIV", 1994},
        {"MMVI", 2006},
    };

    auto const n = sizeof(tt) / sizeof(tt[0]);
    for (int i = 0; i < n; i++) {
        const auto [ok, v] = integer(tt[i].rom);
        if (!ok) {
            cout << "ERROR: invalid roman digit" << endl;
        }
        else if (v != tt[i].expected) {
            cout << "ERROR: expected: " << tt[i].expected << " is " << v << endl;
        }
    }
}

void Roman::test_roman() {
    struct Data_ {
        string expected;
        int value;
    } const tt[] = {
        {"I", 1},
        {"II", 2},
        {"III", 3},
        {"IV", 4},
        {"V", 5},
        {"VI", 6},
        {"VII", 7},
        {"VIII", 8},
        {"IX", 9},
        {"X", 10},
        {"XI", 11},
        {"XII", 12},
        {"XIII", 13},
        {"XIV", 14},
        {"XV", 15},
        {"XVI", 16},
        {"XVII", 17},
        {"XVIII", 18},
        {"XIX", 19},
        {"XX", 20},
        {"XXX", 30},
        {"XL", 40},
        {"XLIV", 44},
        {"L", 50},
        {"LVI", 56},
        {"LXXX", 80},
        {"DCC", 700},
        {"CMII", 902},
        {"CMXCIX", 999},
        {"MCCXXXIV", 1234},
        {"MCDXLVI", 1446},
        {"MCMXCIV", 1994},
        {"MMVI", 2006},
    };

    auto const n = sizeof(tt) / sizeof(tt[0]);
    for (int i = 0; i < n; i++) {
        const auto s = roman(tt[i].value);
        if (s != tt[i].expected) {
            cout << "ERROR: expected: " << tt[i].expected << " is " << s << endl;
        }
    }
}
