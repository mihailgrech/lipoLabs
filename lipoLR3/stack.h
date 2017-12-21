#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

class Stack {
public:
    const unsigned MAX_SIZE = 100;

    void push(int i) {
        if (!this->isFull()) {
            vec.push_back(i);
        }
    }

    void pop() {
        if (!this->isEmpty()) {
            vec.pop_back();
        }
    }

    int peek() {
        if (!this->isEmpty()) {
            return vec[vec.size() - 1];
        } else {
            return -1;
        }
    }

private:
    std::vector<int> vec;

    bool isEmpty() {
        return vec.size() == 0;
    }

    bool isFull() {
        return vec.size() == MAX_SIZE;
    }
};

#endif // STACK_H
