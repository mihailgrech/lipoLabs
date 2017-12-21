#include "create_asm_by_polish.h"
using namespace std;

node* CreateAsmCodeByPolish::tree(vector<string> postfix) {
    node *stack = new node;
    stack = nullptr;

    for (auto i: postfix) {
        node *newNode = new node;
        newNode->token = i;

        /* if it's a function we create new node, connect it with 2 last elements in stack and push this new node into stack */
        if (i == "+" || i == "-" || i == "*" || i == "/" || i == "=") {
            newNode->right = stack;
            newNode->left = stack->next;
            newNode->next = stack->next->next;
            stack = newNode;
        } else {
            /* if it's an unary operator we create new node, take an element from stack and push this new node into stack */
            if (i == "U+" || i == "U-") {
                if (i == "U-") {
                    newNode->right = nullptr;
                    newNode->left = stack;
                    newNode->next = stack->next;
                    stack = newNode;
                }
            } else {
                /* if it's just operand, push it into stack */
                newNode->left = nullptr; // it's a leaf
                newNode->right  = nullptr;

                newNode->next = stack;
                stack = newNode;
            }
        }
    }
    return stack;
}

void CreateAsmCodeByPolish::postorderTreeTraversal(node *p, int k) {
    if (p->left != nullptr) {
        postorderTreeTraversal(p->left, k+1);
    }

    if (p->right != nullptr) {
        postorderTreeTraversal(p->right, k+1);
    }

    task1(p);
    task2(p);
    task3(p);
    task4(p);
    task5(p);
    task6(p);

    if (p->token == "=") {
        asmCode = asmCode + "mov " + polishTokens[0] + ", eax\n";
    }
}

void CreateAsmCodeByPolish::task1(node *p) {
    if (findTokens::isFunction(p->token) && p->left != nullptr && p->right != nullptr &&
            findTokens::isOperand(p->left->token) && findTokens::isOperand(p->right->token)) {

        asmCode = asmCode + "mov eax, " + p->left->token + "\n";
        asmCode += chooseAsmStringByFunction(p->token);
        asmCode = asmCode + " eax, " + p->right->token + "\n";
    }
}

void CreateAsmCodeByPolish::task2(node *p) {
    if (findTokens::isFunction(p->token) && p->left != nullptr && p->right != nullptr &&
            findTokens::isFunction(p->left->token) && findTokens::isOperand(p->right->token)) {

        asmCode += chooseAsmStringByFunction(p->token);
        asmCode = asmCode + " eax, " + p->right->token + "\n";
    }
}

void CreateAsmCodeByPolish::task3(node *p) {
    if ((p->token == "+" || p->token == "*") && p->left != nullptr && p->right != nullptr &&
            findTokens::isFunction(p->right->token) && findTokens::isOperand(p->left->token))
    {
        if (p->token == "+") {
            asmCode += "sum";
        }

        if (p->token == "*") {
            asmCode += "imul";
        }

        asmCode = asmCode + " eax, " + p->left->token + "\n";
    }
}

void CreateAsmCodeByPolish::task4(node *p) {
    if ((p->token == "-" || p->token == "/") && p->left != nullptr && p->right != nullptr &&
            findTokens::isOperand(p->left->token) && findTokens::isFunction(p->right->token)) {
        asmCode = asmCode + "mov edx, " + p->left->token + "\n";
        asmCode = asmCode + "xchg eax, edx\n";

        if (p->token == "-") {
            asmCode += "sum";
        }
        if (p->token == "/") {
            asmCode += "idiv";
        }

        asmCode += " eax, edx\n";
    }
}

void CreateAsmCodeByPolish::task5(node *p) {
    if (findTokens::isFunction(p->token) && p->left != nullptr && p->right != nullptr &&
            findTokens::isFunction(p->left->token) && findTokens::isFunction(p->right->token)) {
        // we push "push" into asm code after all, because we cant see here if the parent of node has both 2 functions or not.
        asmCode += "pop edx\n";
        asmCode += chooseAsmStringByFunction(p->token);
        asmCode += " eax, edx\n";
    }
}

void CreateAsmCodeByPolish::task6(node *p) {
    if (findTokens::isFunction(p->token) && p->right == nullptr && p->left != nullptr &&
            findTokens::isOperand(p->left->token)) {
        asmCode += "mov eax " + p->left->token + "\n";
        asmCode += "neg eax\n";
    }

    if (findTokens::isFunction(p->token) && p->right == nullptr && p->left != nullptr &&
            p->left->token == "U-") {

        asmCode += "neg eax\n";
    }
}

string CreateAsmCodeByPolish::chooseAsmStringByFunction(string token) {
    string res;
    if (token == "+") {
        res = "sum";
    }

    if (token == "-") {
        res = "sub";
    }

    if (token == "*") {
        res = "imul";
    }

    if (token == "/") {
        res = "idiv";
    }

    return res;
}
