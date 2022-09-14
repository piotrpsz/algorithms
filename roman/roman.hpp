#ifndef ROMAN_HPP
#define ROMAN_HPP

#include <map>
#include <string>
#include <tuple>


class Roman final {
    static std::map<char, int> const ROMAN;
public:
    static std::pair<bool, int> integer(std::string const&);
    static std::string roman(int);

    static void test_integer();
    static void test_roman();
};

#endif