//
// Created by Anton on 26.10.2021.
//

#include "customString.h"

bool startsWith(const String string, const String start, int stringl, int startl)
{
    for (int i = 0; i < startl && i < stringl; ++i)
    {
        if (start[i] != string[i])
        {
            return false;
        }
    }
    return true;
}