#ifndef MPAUTO_H
#define MPAUTO_H

#include "stack.h"
#include <string>

class PrimitiveMpAuto
{
public:
    static bool isStringCorrect(std::string str);
};

class NonPrimitiveMpAuto
{
public:
    static std::string convertString(std::string str);
};

#endif // MPAUTO_H
