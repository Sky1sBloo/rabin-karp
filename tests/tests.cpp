#include "RabinKarp.hpp"
#include <array>
#include <iostream>
#include <string>

class FailedTest : std::exception {
public:
    FailedTest(const std::string& pattern, const std::string& text, bool expectFail = false)
    {
        if (expectFail) {
            _message = "Found " + pattern + " at where expected fail at text: " + text;
        } else {
            _message = "Cannot find " + pattern + " at text: " + text;
        }
    }
    FailedTest(const std::string& pattern, const std::string& text, int returnedPos, int expectedPos)
    {
        _message = "Found " + pattern + " but position doesn't match. Expected: " + std::to_string(expectedPos) + " but got: " + std::to_string(returnedPos) + " at text: " + text;
    }

    const char* what() const noexcept override
    {
        return _message.c_str();
    }

private:
    std::string _pattern;
    std::string _text;
    std::string _message;
};
struct StringMatcher {
    const std::string text;
    const std::string pattern;
    bool expectSuccess;
    int expectPos = -1;
};

int main()
{
    std::string longStr(10000000, 'e');
    longStr.push_back('f');

    const std::array<StringMatcher, 13> testCases = { { { "xxxabcddd", "abc", true, 3 },
        { "hello", "idot", false },
        { "together", "ther", true, 4},
        { "", "woo", false },
        { "woont", "", false },
        { "short", "a very long value", false },
        { "equal", "equal", true, 0 },
        { "bahahaha", "ha", true, 2 },
        { "w@* is this sh*t?", "h*t?", true, 13 },
        { "bananza", "z", true, 5 },
        { "waTW", "W", true, 3 },
        { longStr, "ef", true, 9999999 },
        { "ooooooooh", "o", true, 0 } } };

    RabinKarp patternFinder(283, 113);

    try {
        for (const StringMatcher& strMatch : testCases) {
            const auto& it = patternFinder.getFirstInstanceOf(strMatch.pattern, strMatch.text);
            if (strMatch.expectSuccess) {
                if (it == strMatch.text.end()) {
                    throw FailedTest(strMatch.pattern, strMatch.text);
                }
                if (std::distance(strMatch.text.begin(), it) != strMatch.expectPos) {
                    throw FailedTest(strMatch.pattern, strMatch.text, std::distance(strMatch.text.begin(), it), strMatch.expectPos);
                }
            } else if (it != strMatch.text.end()) {
                throw FailedTest(strMatch.pattern, strMatch.text, true);
            }
        }
    } catch (FailedTest ex) {
        std::cerr << "Failed test: " << ex.what() << std::endl;
        return 1;
    }
    std::cout << "Success" << std::endl;
}
