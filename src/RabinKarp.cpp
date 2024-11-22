#include "RabinKarp.hpp"
#include <cmath>

RabinKarp::RabinKarp(int base, int mod)
    : _base(base)
    , _mod(mod)
{
}

char RabinKarp::hashedChar(char c) const noexcept
{
    return c - ' ' + 1;
}

int RabinKarp::rollingHash(const std::string& value) const
{
    int output = 0;
    for (int i = 0; i < value.length(); i++) {
        output += hashedChar(value[i]) * std::pow(_base, value.length() - 1 - i);
    }
    return output % _mod;
}

std::string::const_iterator RabinKarp::getFirstInstanceOf(const std::string& pattern, const std::string& value) const
{
    if (value.length() < pattern.length() || value.empty() || pattern.empty()) {
        return value.cend();
    }
    if (value == pattern) {
        return value.cbegin();
    }

    int targetHash = rollingHash(pattern);
    int newHash = rollingHash(value.substr(0, pattern.length()));
    if (newHash == targetHash) {
        return value.cbegin();
    }

    int power = std::pow(_base, pattern.length() - 1);

    for (int i = 1; i < value.length(); i++) {
        if (i <= value.length() - pattern.length()) {
            int prevCharHash = hashedChar(value[i - 1]) * power % _mod;
            int prevCharDifference = ((newHash - prevCharHash + _mod) * _base) % _mod;
            newHash = (prevCharDifference + hashedChar(value[i + pattern.length() - 1])) % _mod;
        } else {
            break;
        }
        if (newHash == targetHash) {
            if (value.substr(i, pattern.length()) == pattern) {
                return value.cbegin() + i;
            }
        }
    }
    return value.cend();
}
