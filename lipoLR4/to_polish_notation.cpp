#include "to_polish_notation.h"
using namespace std;

double ToPolishNotation::calculate() {
    stack<string> operands;
    stack<string> functions;

    unsigned i = 0;
    do {
        string t = tokenized[i];

        if (findTokens::isOperand(t)) {
            /* does 2 things at the same time: calculates the result of an expression and creates its reverse polish notation */
            tokenizedPolish.push_back(t);
            operands.push(t);
        }

        if (findTokens::isFunction(t)) {
            if (t == ")") {
                while (functions.size() > 0 && functions.top() != "(") {
                    tokenizedPolish.push_back(functions.top());

                    popFunction(operands, functions);

                }
                functions.pop();
            } else {
                while (canPop(t, functions)) {
                    tokenizedPolish.push_back(functions.top());

                    popFunction(operands, functions);

                }
                functions.push(t);
            }
        }
        i++;
    } while (i < tokenized.size());

    if (operands.size() == 1 && functions.size() == 0) {
        expressionResult = std::stod(operands.top());
        return expressionResult;
    }

    return 0;
}

void ToPolishNotation::popFunction(stack<string> &operands, stack<string> &functions) {
    if (functions.top() == "U-" || functions.top() == "U+") {
        string A = operands.top();
        operands.pop();
        if (functions.top() == "U-") {
            operands.push(std::to_string(std::stod(A)*(-1.)));
        }

        if (functions.top() == "U+") {
            operands.push(std::to_string(std::stod(A)*(1.)));
        }
    } else {
        string B = operands.top();
        operands.pop();
        string A = operands.top();
        operands.pop();

        if (functions.top() == "+") {
            operands.push(std::to_string(std::stod(A) + std::stod(B)));
        }

        if (functions.top() == "-") {
            operands.push(std::to_string(std::stod(A) - std::stod(B)));
        }

        if (functions.top() == "*") {
            operands.push(std::to_string(std::stod(A) * std::stod(B)));
        }

        if (functions.top() == "/") {
            operands.push(std::to_string(std::stod(A) / std::stod(B)));
        }

    }

    functions.pop();
}


bool ToPolishNotation::canPop(const string &op1, stack<string> &functions)
{
    if (functions.size() == 0) {
        return false;
    }

    int p1 = getPriority(op1);
    int p2 = getPriority(functions.top());

    return (p1 >= 0) && (p2 >= 0) && (p1 >= p2);
}

int ToPolishNotation::getPriority(const string &op)
{
    if (op == "(") {
        return -1;
    }

    if (op == "U+" || op == "U-") {
        return 0;
    }

    if (op == "*" || op == "/") {
        return 1;
    }

    if (op == "+" || op == "-") {
        return 2;
    }

    if (op == "=") {
        return 3;
    }

    return 100500;
}

void ToPolishNotation::parseString() {
    string re = findTokens::reOperand + string("|") + findTokens::reFunction;
    regex reMatched(re);
    std::smatch matched;

    string tempS = s;
    while (std::regex_search(tempS, matched, reMatched)) {
        tokenized.push_back(matched[0]);
        tempS = matched.suffix().str();
    }

    for (unsigned i = 0; i < tokenized.size()-1; i++) {
        /* try to find unary operation at the beginning of the string */
        if (tokenized[i] == "=") {
            if (tokenized[i+1] == "-") {
                tokenized[i+1] = "U-";
            }
            if (tokenized[i+1] == "+") {
                tokenized[i+1] = "U+";
            }
        }
        /* try to find unary operation right after open bracket */
        if (tokenized[i] == "(") {
            if (tokenized[i+1] == "-") {
                tokenized[i+1] = "U-";
            }
            if (tokenized[i+1] == "+") {
                tokenized[i+1] = "U+";
            }
        } else {
            /* try to find unary operation after * or /. In this case we must add an additional pair of brackets */
            if ((tokenized[i] == "*" || tokenized[i] == "/")) {
                if (tokenized[i+1] == "-") {
                    tokenized[i+1] = "U-";
                }
                if (tokenized[i+1] == "+") {
                    tokenized[i+1] = "U+";
                }
            } else {
                /* try to find unary operation right after + or - */
                if ((tokenized[i] == "+" || tokenized[i] == "-")) {
                    if (tokenized[i+1] == "-") {
                        tokenized[i+1] = "U-";
                    }
                    if (tokenized[i+1] == "+") {
                        tokenized[i+1] = "U+";
                    }
                }
            }
        }
    }
}
