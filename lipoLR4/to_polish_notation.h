#ifndef TOPOLISHNOTATION_H
#define TOPOLISHNOTATION_H

#include "find_operands_and_functions.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>

class ToPolishNotation
{
public:
    ToPolishNotation(std::string s) {
        /* we must add "(" at the beginning and ")" at the end to make this algorithm work correctly */
        s.insert(s.begin(), '(');
        s.push_back(')');
        this->s = s;

        parseString();
        calculate();
    }

    double getExpressionResult() { return expressionResult; }
    std::vector<std::string> getPolishTokens() {return tokenizedPolish; }
private:
    double calculate();

    std::string s;
    std::vector<std::string> tokenized;
    std::vector<std::string> tokenizedPolish;
    double expressionResult;

    void parseString();
    void popFunction(std::stack<std::string> &operands, std::stack<std::string> &functions);
    bool canPop(const std::string &op1, std::stack<std::string> &functions);
    int getPriority(const std::string &op);
};
#endif // TOPOLISHNOTATION_H
