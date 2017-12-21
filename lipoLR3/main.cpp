#include "mpauto.h"
#include <iostream>
using namespace std;

int main()
{
    string s = "1111000";
    string s2 = "00111";

    cout << "String: " << s << endl;
    cout << "First task: " << PrimitiveMpAuto::isStringCorrect(s) << endl;

    cout << endl << "String 2: "<< s2 << endl;
    cout << "Second task: " << NonPrimitiveMpAuto::convertString(s2);
    return 0;
}
