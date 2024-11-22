#pragma once
#include <string>

class RabinKarp {
public:
    /**
     * Rabin Karp constructor
     *
     * @param base Initial base multiplier for positional checking
     * @param mod (use prime number) to prevent integer overflow
     */
    RabinKarp(int base, int mod);

    /**
     * Returns an iterator of the first instance
    */
    std::string::const_iterator getFirstInstanceOf(const std::string& pattern, const std::string& value) const;

private:
    int _base;
    int _mod;

    char hashedChar(char c) const noexcept;

    int rollingHash(const std::string& value) const;
};
