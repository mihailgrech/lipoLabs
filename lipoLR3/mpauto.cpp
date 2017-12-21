#include "mpauto.h"
using namespace std;

/* strings like 1*0* and len(1*) > len(0*) */
bool PrimitiveMpAuto::isStringCorrect(string str) {
    str += "\n";

    enum States {
        state1,
        state2
    };

    States currentState = state1;
    Stack stack;

    for (unsigned i = 0; i < str.size(); i++) {
        if (currentState == state1) {
            if (str[i] == '1') {
                stack.push(1);
            }

            if (str[i] == '0') {
                currentState = state2;
            }


            if (str[i] == '\n') {
                return true;
            }
        }

        if (currentState == state2) {
            if (str[i] == '0') {
                stack.pop();
            }

            if (str[i] == '1') {
                return false;
            }

            if (str[i] == '\n') {
                if (stack.peek() == 1) {
                    return true;
                }
                return false;
            }
        }
    }
}

/* 0n 1m INTO 0 1^(2n) 0^(2m) 0 */
string NonPrimitiveMpAuto::convertString(string str)
{
    str += "\n";

    string res;
    Stack stack;

    res += "0"; // put 0 at the beginning of the output string
    for (unsigned i = 0; i < str.size(); i++) {
        if (str[i] == '0') {
            if (stack.peek() == 1) {
                return "ERROR";
            }
            res += "11";
        }

        if (str[i] == '1') {
            stack.push(1);
        }

        if (str[i] == '\n') {
            while (stack.peek() == 1) {
               stack.pop();
               res += "00";
            }
        }
    }

    res += "0"; // add 0 at the end of the output string
    return res;
}
