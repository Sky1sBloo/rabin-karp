#include <cmath>
#include <string>
#include <iostream>
#define MOD 113
#define BASE 10

char hashedChar(char c)
{
    return c - 'A' + 1;
}

int hashValue(const std::string& value)
{
    int output = 0;
    for (int i = 0; i < value.length(); i++) {
        output += hashedChar(value[i]) * std::pow(BASE, value.length() - 1 - i);
    }
    return output % MOD;
}
int rabinKarp(const std::string& value, const std::string& pattern)
{
    if (value.length() < pattern.length()) {
        return -1;
    }

    int targetHash = hashValue(pattern);
    int newHash = hashValue(value.substr(0, pattern.length()));
    std::cout << newHash << "-" << targetHash <<'\n';

    int power = std::pow(BASE, pattern.length() - 1);

    for (int i = 1; i < value.length(); i++) {
        if (i < value.length() - pattern.length()) {
            int prevCharHash = hashedChar(value[i - 1]) * power % MOD;
            int prevCharDifference = ((newHash - prevCharHash + MOD) * BASE) % MOD;
            newHash = (prevCharDifference + hashedChar(value[i + pattern.length() - 1])) % MOD;
        }
        if (newHash == targetHash) {
            return i;
        }
    }
    return -1;
}

int rabinKarp2(const std::string& value, const std::string& pattern, int prevHash = 0, int iStart = 0)
{
    int targetHash = hashValue(pattern);
    if (iStart == 0) {
        int startHash = 0;
        for (int i = 0; i < pattern.length(); i++) {
            startHash += hashedChar(value[i]) * std::pow(BASE, pattern.length() - 1 - i);
        }
        return rabinKarp2(value, pattern, startHash, 1);
    }
    if (iStart >= value.length()) {
        return -1;
    }
    int newCharHash = static_cast<int>(hashedChar(value[iStart - 1]) * std::pow(BASE, pattern.length() - 1)) % MOD;
    int prevHashDifference = (prevHash - newCharHash) * BASE % MOD;
    int newHash = prevHashDifference + hashedChar(value[iStart + pattern.length() - 1]) % MOD;
    std::cout << newCharHash << std::endl;
    if (newHash == targetHash) {
        return iStart;
    }
    return rabinKarp2(value, pattern, newHash, iStart + 1);
} 

int test()
{
    const std::string text = "The quick brown fox";
    const std::string pattern = "ick";

    int value = rabinKarp(text, pattern);
    return value;
}
