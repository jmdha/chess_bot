#include "Headers/generic_helper_functions.h"

bool isNumber(char charToCheck)
{
    if (int(charToCheck) > 47 && int(charToCheck) < 58)
        return true;
    else
        return false;
}

int getColumnAsNumber(char column)
{
    if (isLowercase(column))
        return int(column) - 97;
    else
        return int(column) - 65;
}

bool isLowercase(char charToCheck)
{
    if (int(charToCheck) > 64 && int(charToCheck) < 91)
        return false;
    else
        return true;
}