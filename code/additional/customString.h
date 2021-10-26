//
// Created by Anton on 26.10.2021.
//

#ifndef MAIN_PY_CUSTOMSTRING_H
#define MAIN_PY_CUSTOMSTRING_H
#include "stdbool.h"


#define String char *

bool startsWith(const String string, const String start, int stringl, int startl);

#endif //MAIN_PY_CUSTOMSTRING_H
