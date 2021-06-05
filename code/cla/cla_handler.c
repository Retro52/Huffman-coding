//
// Created by Anton on 25.04.2021.
//

#include "path.h"
#include <stdbool.h>
#include "stdlib.h"
#include "string.h"
#include "cla_handler.h"
#include "../logging/iniparser.h"
#include "../tasks/compression.h"

int handler(const int argc, const char **argv)
{
    /* Checks if any args were given */
    if (argc > 1)
    {
        /* Comparison launched */
        if (!strcmp(argv[1], "--compare"))
        {
            return -3;
        }
        /* Checks --help argument */
        /* Comparison between '--help' and given argument */
        if (!strcmp(argv[1], "--help"))
        {
            /* --help is equal to argv[1] */
            return -2;
        }

        /* Checks --test argument */
        /* Comparison between '--test' and given argument */
        if (!strcmp(argv[1], "--test"))
        {
            /* --test is equal to argv[1] */
            return -1;
        }
        else
        {
            /* If argv[1] didn`t match --help launches files initialization */
            files_init(0, argc, argv);
            return 0;
        }
    }
    else
    {
        /* If there is no additional arguments simply launches files initialization */
        files_init(0, argc, argv);
        return 0;
    }
}

char *init_logpath()
{
    static char *pString;
    static bool init = false;

    /* Checks if value is already initialized */
    if (!init)
    {
        pString = malloc(100 * sizeof(char));

        void *logdir = NULL;
        void *logfile = NULL;

        /*
         * status -1 means that function couldn't open .ini file
         */

        int status = find_value(INI_FILE, "log", "logpath", &logdir);

        /* In case if logpath value not found */
        if (status == -1)
        {
            printf("[ERROR] Couldn't read .ini file. directory for logs will be created automatically\n");
        }

        status = find_value(INI_FILE, "log", "logfile", &logfile);

        /* In case if logfile value not found */
        if (status == -1)
        {
            printf("[ERROR] Couldn't read .ini file. Name for logs file will be created automatically\n");
        }

        /* Checking what was found in .ini file and written by given address */
        if (logdir && logfile)
        {
            pString = path((char *) logdir, (char *) logfile);
        }
        if (!logdir && logfile)
        {
            pString = path("Huffman logs", (char *) logfile);
        }
        if (logdir && !logfile)
        {
            pString = path((char *) logdir, "log.txt");
        }
        if (!logdir && !logfile)
        {
            pString = path("Huffman logs", "logs.txt");
        }

        /* Marking pString as initialized and returning it */
        init = true;
        return pString;
    }
    else
    {
        /* If value is already initialized returns it */
        return pString;
    }
}

char *files_init(const int argument, const int argc, const char **argv)
{
    static char **names;
    static bool initialized = false;

    if (!initialized)
    {
        /* Creates a matrix for files which will be read */
        names = (char **) malloc(3 * sizeof(char *));
        for (int k = 0; k < 2; k++)
        {
            names[k] = (char *) malloc(200 * sizeof(char));
        }

        /* First file is a path to the logs file */
        names[0] = init_logpath();

        switch (argc)
        {
            /* One argument detected, but he didn't match --help */
            case 2:
                printf("[WARNING] Wrong command line arguments.\n"
                       "Consider using 'program.exe --help' for additional info");
                names[1] = NULL;
                break;

            case 3:

                /* Checks if there are valid arguments */
                if (!strcmp((char *) argv[1], "-c"))
                {
                    /* Compress argument matches */
                    compress(argv[2]);
                    exit(0);
                }
                else if (!strcmp((char *) argv[1], "-d"))
                {
                    /* Decompress argument matches */
                    decompress(argv[2]);
                    exit(0);
                }
                else
                {
                    /* Three cla given but none of them is valid */
                    printf("[WARNING] Wrong command line arguments.\n"
                           "Consider using 'program.exe --help' for additional info");
                    names[1] = NULL;
                }
                break;

            default:
                /* For case with no command line arguments or when there is more than 4 of them */
                printf("[INFO] No valuable command line arguments given\n");
                names[1] = NULL;
                break;
        }

        /* Marking files as initialized */
        initialized = true;

        /* Additional check for argument to be in range */
        if (argument < 2 && argument >= 0)
        {
            return names[argument];
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        /* Additional check for argument to be in range */
        if (argument < 2 && argument >= 0)
        {
            return names[argument];
        }
        else
        {
            return NULL;
        }
    }
}
