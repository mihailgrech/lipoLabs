#include "to_polish_notation.h"
#include "create_asm_by_polish.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    /* Catching exceptions in the calculate function must be added before
     * trying to generate asm code for expressions with letters */
    string s =
    //"1 + 2 - 5 * 3 / 8"
     "-22 + 11 - (-5) * 55"
    // "+3 * (-22) + (-33) * (+1+1+1    -2   +  1) *  -1"
    // "-3 * (-22) + (-33) * (1+1+1    -2   +  1) *  -1"
    // "3 * (22) + (33) * (1+1+1 -2 + 1) * 1"
    // "(100 + -3) * -5"
    // "1*2 + 3*4"
    // "ALPHA=2 + 1 - 6 / (1 + 2)"
    // "A = A2 + 10 - B / (-32 + K)"
    // "A = -B+(C-D)*2+(E+100)*3"
    // "A1 = D1*C1+(C2+2)*5-7"
    // "X = Y*Z*(B-C)*2+7"
    // "Y = (F1+F22)*10+7*(F13-F333)"
    // "Z100=Z1*(Z2+Z3)-Z4*(Z5-Z6)"
            ;

    ToPolishNotation pol(s);
    cout << "expression: " << s << endl;

    vector<string> pn = pol.getPolishTokens();
    cout << "expression in polish notation: ";
    for (auto i: pn) {
        cout << i << " ";
    }
    cout << endl;
    cout << "calculated: " << pol.getExpressionResult() << endl;

    cout << "\ngenerated asm code:\n";
    CreateAsmCodeByPolish toAsm(pn);
    vector<string> asmS = toAsm.getVectorAsmCode();

    for (auto i: asmS) {
        cout << i << endl;
    }

    return 0;
}
