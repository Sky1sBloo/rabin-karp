#include "RabinKarp.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Incorrect arguments: " << "Usage: rabin-karp [text] [pattern]" << std::endl;
        return 1;
    }

    const std::string text = argv[1];
    const std::string pattern = argv[2];
    RabinKarp patternFinder(283, 113);

    const auto& it = patternFinder.getFirstInstanceOf(pattern, text);
    if (it == text.end()) {
        std::cerr << "Cannot find pattern: " << pattern << std::endl;
        return 1;
    }
    std::cout << "Pattern found at " << std::distance(text.begin(), it) << std::endl;
}
