#ifndef CREATEASMCODEBYPOLISH_H
#define CREATEASMCODEBYPOLISH_H

#include "find_operands_and_functions.h"
#include <iostream>
#include <vector>
#include <string>

/* a tree is built from these nodes */
struct node {
    std::string token;
    node *left;
    node *right;
    node *next;
};

class CreateAsmCodeByPolish
{
public:
    /* input: a vector of expression tokens in reverse polish notation(RPN) e.g. {"1", "3", "+"} */
    CreateAsmCodeByPolish(std::vector<std::string> polishTokens) {
        this->polishTokens = polishTokens;

        node *t = new node;
        t = tree(this->polishTokens);
        postorderTreeTraversal(t, 1);
    }

    std::vector<std::string> getVectorAsmCode() {
        for (size_t p = 0, q = 0; p != asmCode.npos; p = q) {
            splittedS.push_back(asmCode.substr(p+(p!=0), (q=asmCode.find('\n', p+1))-p-(p!=0)));
        }

        for (size_t i = 1; i < splittedS.size(); i++) {
            if (splittedS[i].substr(0, 7) == "mov eax") {
                splittedS[i-1] += "\npush eax";
            }
        }

        return splittedS;
    }

private:
    std::string asmCode;
    std::vector<std::string> splittedS;
    std::vector<std::string> polishTokens;

    /* build tree from RPN */
    node* tree(std::vector<std::string> postfix);

    /* generate asm code */
    void postorderTreeTraversal(node *p, int k);
    std::string chooseAsmStringByFunction(std::string token);

    // both left and right are operands
    // mov eax, id1/iconst1
    // op еах, id2/iconst2
    void task1(node *p);

    // left is function and right is operand
    // op eax, id2/iconst2
    void task2(node *p);

    // right is function and left is operand for + and *
    // op еах, id1/iconst1
    void task3(node *p);

    // right is function and left is operand for - and /
    // mov edx, id2/iconst2
    // xchg eax,edx
    // op eax,edx
    void task4(node *p);

    // both left and right are functions
    // push aex
    // pop edx
    // op eax, edx
    void task5(node *p);

    // right is nullptr
    // left is operand
    // neg eax
    void task6(node *p);
};
#endif // CREATEASMCODEBYPOLISH_H
