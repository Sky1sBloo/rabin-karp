#pragma once
#include <string>

class RabinKarp {
public:
    RabinKarp(int base, int mod);

    std::string::const_iterator getFirstInstanceOf(const std::string& pattern, const std::string& value) const;

private:
    int _base;
    int _mod;

    char hashedChar(char c) const noexcept;

    int rollingHash(const std::string& value) const;
};
