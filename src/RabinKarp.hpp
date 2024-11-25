#pragma once
#include <string>
#include <vector>

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

    /**
     * Returns the first instance of the pattern but saves the hash comparisons
     */
    std::string::const_iterator getFirstInstanceOf(const std::string& pattern, const std::string& value, std::vector<int>& hashComparisons) const;

    /**
     * Returns a rolling hash on string based on its length
     */
    int rollingHash(const std::string& value, int length = -1) const;

private:
    int _base;
    int _mod;

    char hashedChar(char c) const noexcept;
};
