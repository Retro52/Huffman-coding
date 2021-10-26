//
// Created by Anton on 25.04.2021.
//

#include "logging.h"
#include "iniparser.h"

int init()
{
    static void *a;
    static int b;
    static bool initialized = false;

    /* If function is launched for the first time, initializing loglevel value (b) */
    if (!initialized)
    {
        /* Reading .ini file for loglevel value */
        int status = find_value(INI_FILE, "log", "loglevel", &a);

        /* Checking if number was written by address */
        if (status == 1)
        {
            /* Reading value by address */
            b = (int) **(double **) &a;
            if (b == 0)
            {
                printf("Loglevel value is initialized and set to %d\n", b);
            }

            /* Marking value as initialized */
            if (b >= 0 && b <= 4)
            {
                initialized = true;
            }

            /* In case if value was not found or was not red properly */
            else
            {
                if (b == -1)
                {
                    printf("[WARNING] Ini reading error - a parameter is too low or too high.\n"
                           "Check your %s file and retry again\n", INI_FILE);
                }
                b = 0;
                initialized = true;
            }
        }

        /* In case if string was written by address */
        if (status == 2)
        {
            printf("[WARNING] Unexpected argument while reading loglevel value\n"
                   "Check your %s file and retry again\n", INI_FILE);
            initialized = true;
            b = 0;
        }

        /* In case if .ini reading error was returned */
        if (status != 1 && status != 2)
        {
            printf("[WARNING] Failed to read %s file, Loglevel set to debug (0)", INI_FILE);
            initialized = true;
            b = 0;
        }

        /* Returning initialized value */
        return b;
    }
    else
    {
        /* Returning value if it was already initialized */
        return b;
    }

}


void LOG(int level, const char *file, const char *message, ...)
{
    /* Initializing arguments list */
    va_list args;
    va_start(args, message);
    int log_level = init();

    /* Checking global log level */
    if (log_level > -1)
    {
        if (level == 0 && level >= log_level)
        {            
            log_debug(file, message, args);
        }
        if (level == 1 && level >= log_level)
        {            
            log_info(file, message, args);
        }
        if (level == 2 && level >= log_level)
        {            
            log_warn(file, message, args);
        }
        if (level == 3 && level >= log_level)
        {            
            log_error(file, message, args);
        }
        if (level == 4 && level >= log_level)
        {            
            log_fatal(file, message, args);
        }
    }

    /* Ending writing arguments to list*/
    va_end(args);
}

void log_format(const char *file, const char *tag, const char *message, const va_list args)
{

    /* Try to open or create log file */
    FILE *log_file;
    char *fname = init_logpath();
    if ((log_file = fopen(fname, "a+")) != NULL)
    {
        /* current time for correct logging */
        time_t now;
        time(&now);
        char *date = ctime(&now);
        date[strlen(date) - 1] = '\0';

        /* defining array sized for string with first part of log info - DATE [LOG_LEVEL] */
        char log_info[200];

        /*
         * sprintf function returns number of characters written to array (in this case log_info[80]),
         * so we can use this value as an analog of strlen(). Len is needed to add '\0' at the correct place, so
         * log info will be written as string value correctly and without any errors
         */

        int len = sprintf(log_info, "%s [%s] [%s] ", date, file, tag);
        log_info[len - 1] = '\0';

        /* writing log info to file */
        fprintf(log_file, "%s - ", log_info);
        vfprintf(log_file, message, args);
        fprintf(log_file, "\n");

        /* closing file */
        fclose(log_file);
    }
    else
    {
        printf("Cannot open or create a file for logs\n");
    }
}

void log_info(const char *file, const char *message, const va_list args)
{
    log_format(file, "info", message, args);
}

void log_debug(const char *file, const char *message, const va_list args)
{
    log_format(file, "debug", message, args);
}

void log_warn(const char *file, const char *message, const va_list args)
{
    log_format(file, "warning", message, args);
}

void log_error(const char *file, const char *message, const va_list args)
{
    log_format(file, "error", message, args);
}

void log_fatal(const char *file, const char *message, const va_list args)
{
    log_format(file, "fatal", message, args);
}
