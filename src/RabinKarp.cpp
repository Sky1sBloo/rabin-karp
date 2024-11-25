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

int RabinKarp::rollingHash(const std::string& value, int length) const
{
    if (length < 0) {
        length = value.length();
    }
    int output = 0;
    for (int i = 0; i < length; i++) {
        output += hashedChar(value[i]) * std::pow(_base, length - 1 - i);
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

    const int targetHash = rollingHash(pattern);
    int newHash = rollingHash(value, pattern.length());
    if (newHash == targetHash) {
        return value.cbegin();
    }

    const int power = std::pow(_base, pattern.length() - 1);

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
std::string::const_iterator RabinKarp::getFirstInstanceOf(const std::string& pattern, const std::string& value, std::vector<int>& hashComparisons) const
{
    if (value.length() < pattern.length() || value.empty() || pattern.empty()) {
        return value.cend();
    }
    if (value == pattern) {
        return value.cbegin();
    }

    const int targetHash = rollingHash(pattern);
    int newHash = rollingHash(value, pattern.length());
    hashComparisons.push_back(newHash);
    if (newHash == targetHash) {
        return value.cbegin();
    }

    const int power = std::pow(_base, pattern.length() - 1);

    for (int i = 1; i < value.length(); i++) {
        if (i <= value.length() - pattern.length()) {
            int prevCharHash = hashedChar(value[i - 1]) * power % _mod;
            int prevCharDifference = ((newHash - prevCharHash + _mod) * _base) % _mod;
            newHash = (prevCharDifference + hashedChar(value[i + pattern.length() - 1])) % _mod;
            hashComparisons.push_back(newHash);
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
