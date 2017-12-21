#ifndef FINDOPERANDSANDFUNCTIONS_H
#define FINDOPERANDSANDFUNCTIONS_H

#include <iostream>
#include <regex>
#include <string>

class findTokens {
public:
    static bool isOperand(std::string s) {
        std::regex re(reOperand);
        return std::regex_match(s, re);
    }

    static bool isFunction(std::string s) {
        std::regex re(reFunction);
        return std::regex_match(s, re);
    }

    static constexpr const char *reOperand = "[a-zA-Z0-9]+|\\d+(\\.\\d+)?";
    static constexpr const char *reFunction = "\\+|-|\\*|\\/|\\(|\\)|U\\+|U-|="; //@TODO create a new regex for U+ and U-
};

#endif // FINDOPERANDSANDFUNCTIONS_H
