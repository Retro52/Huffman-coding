#include "logging/logging.h"
#include "cla/help.h"
#include "cla/cla_handler.h"
#include "stdbool.h"
#include "tasks/compression.h"
#include "logging/iniparser.h"
#include "test/test.h"
#include "Comparison/compare.h"

#define LF_MAIN "main.c"

int input_int(char *text, int upper_bound, int lower_bound)
{
    int error, chr, truncated;
    double res;
    bool choose = true;
    while (choose == true)
    {
        printf("%s", text);
        error = scanf("%lf", &res);
        truncated = (int) res;
        while ((chr = getchar()) != '\n' && chr != EOF) {}
        if (error != 1 || truncated != res)
        {
            printf("You entered wrong type of variable. Try again: \n");
        }
        else
        {
            if (res > upper_bound || res < lower_bound)
            {
                printf("The number cannot be higher than the specified number - %d - or lower than %d. "
                       "Try again:\n", upper_bound, lower_bound);
            }
            else
            {
                choose = false;
            }
        }
    }
    return (int) res;
}

int main(const int argc, const char **argv)
{
    /* checking what command line arguments were given */
    int a = handler(argc, argv);
    LOG(LOGLEVEL_DEBUG, LF_MAIN, "Program is loaded and ready to work!");

    LOG(LOGLEVEL_DEBUG, LF_MAIN, "Command line arguments given: %d", argc);


    /* Comparison option */
    if (a == -3)
    {
        printf("C code algorithm: \n");
        compare();
        printf("Python code algorithm: \n");
        system("py ../Comparison/compare.py");
        exit(0);
    }

    /* checking entered command line arguments */
    if (a == -2)
    {
        print_help();
        fputc('\n', stdout);
        system("pause");
        exit(0);
    }

    if (a == -1)
    {
        run_tests();
        exit(0);
    }

    while (1)
    {
        int menu = input_int("\nWelcome!\n"
                             "  1. Compress file\n"
                             "  2. Decompress file\n"
                             "  3. Exit\n", 3, 1);
        switch (menu)
        {
            case 1:
                printf("Enter file name to compress: \n");
                LOG(LOGLEVEL_DEBUG, "main.c", "First task");
                char f1[50];
                fgets(f1, 50, stdin);
                edit_str(f1);
                LOG(LOGLEVEL_DEBUG, "main.c", "File name for first task is: %s", f1);
                compress(f1);
                break;
            case 2:
                printf("Enter file name to decompress: \n");
                LOG(LOGLEVEL_DEBUG, LF_MAIN, "Second task launched task");
                char f2[50];
                fgets(f2, 50, stdin);
                edit_str(f2);
                decompress(f2);
                break;
            case 3:
                LOG(LOGLEVEL_INFO, "main.c", "Program finished");
                exit(0);
            default:
                break;
        }
    }
}
