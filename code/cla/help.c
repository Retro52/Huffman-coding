//
// Created by Anton on 25.04.2021.
//

#include "help.h"

void print_help()
{
    printf("Use '*program name*'  %32s to launch program without additional arguments\n"
           "Use '*program name*'  %10s %20s  to compress chosen file\n"
           "Use '*program name*'  %10s %20s  to de-compress file\n"
           "Use '*program name*'  %10s %20s  to run program tests\n"
           "Use '*program name*'  %10s %20s  to run python and C algorithms comparison\n"
           "You also can use optional argument output=*file name* to set output file name",
           "",
           "-c",
           " *filename*",
           "-d",
           " *filename.huf*",
           "--test",
           "",
           "--compare",
           "");
}
