    //
    // Created by Anton on 25.04.2021.
    //

    #include "iniparser.h"
    #include "ctype.h"


    int find_value(const char *file_name, const char *section, const char *value, void **address)
    {
        /* defining local variables */
        char *strval = NULL;

        /* keep defining local variables */
        FILE *file;
        static double dval = 0;

        /* trying to open a file */
        if ((file = fopen(file_name, "r")) != NULL)
        {
            /* File was opened */
            /* Looking for section */
            if (!find_section(section, file))
            {
                /* Section found in file */
                /* Reading value */
                strval = read_value(value, file);
            }
            else
            {
                /* Section not found */
                fclose(file);
                return -1;
            }

            /* Checking str val if it is NULL */
            if (strval == NULL)
            {
                fclose(file);
                return -1;
            }
        }

        /* Couldn`t open file */
        else
        {
            /* Closing resources */
            if (strval)
            {
                free(strval);
            }
            fclose(file);
            return -1;
        }

        /* If string can be converted into double */
        if (convertable(strval))
        {
            /* Conversion */
            dval = strtod(strval, &strval);
            *address = &dval;

            /* Closing resources */
            fclose(file);
            return 1;
        }
        else
        {
            /* Returns a string */
            edit_str(strval);
            *address = strval;
            fclose(file);
            return 2;
        }
    }

    int find_section(const char *section, FILE *file)
    {
        char sect[100];
        while (1)
        {
            /* Checks if file is over */
            if (feof(file))
            {
                return -1;
            }
            char c = (char) getc(file);

            /* Meets new section */
            if (c == '[')
            {
                /* Checks section name */
                fgets(sect, 100, file);
                edit_str(sect);
                sect[(int) strlen(sect) - 1] = '\0';
                if (!strcmp(sect, section))
                {
                    /* Section found, return code */
                    return 0;
                }
            }
            if (c == ';' || c == '#')
            {
                /* Commented string, scip it */
                fgets(sect, 100, file);
                continue;
            }
        }
    }

    char *read_value(const char *value, FILE *file)
    {
        char val[100];
        char *strval = calloc(100, sizeof(char));
        int i = 0;
        while (1)
        {
            /* Check if file is over */
            if (feof(file))
            {
                return NULL;
            }
            char c = (char) getc(file);
            if (c == '[')
            {
                /* Current section is over */
                return NULL;
            }
            if (c == '\n')
            {
                /* New row, move index to start to re-write value name in val */
                i = 0;
                continue;
            }
            if (c == ';' || c == '#')
            {
                /* Commented string, scip it */
                fgets(val, 100, file);
                continue;
            }
            else
            {
                /* Writing found value */
                val[i] = c;
            }
            if (c == '=')
            {
                /* Value name declared, c is followed by value */
                val[i] = '\0';
                edit_str(val);

                /* Comparing var names */
                if (!strcmp(val, value))
                {
                    char p;
                    int j;

                    /* Reads value */
                    for (j = 0; j < 100 && (p = (char) getc(file)) != '\n'  && !feof(file); ++j)
                    {
                        strval[j] = p;
                        strval[j + 1] = '\0';
                    }

                    /* 'Cleaning' of value */
                    edit_str(strval);
                    return strval;
                }
            }

            /* Read next symbol */
            i++;
        }
    }

    bool convertable(const char *string)
    {
        /*
         * Reads string right from the start,
         * if meets a letter or smth like that - string not convertable
         */
        int len = (int) strlen(string);
        bool convertable;
        for (int i = 0; i < len; ++i)
        {
            if (isdigit(string[i]) || string[i] == '.' || string[i] == '\0' || string[i] == '\n' || string[i] == ' ')
            {
                convertable = true;
            }
            else
            {
                convertable = false;
                break;
            }
        }
        return convertable;
    }

    void edit_str(char str[])
    {
        /* Deleting '=' at the start if there is one */
        int length = (int) strlen(str);
        if (str[0] == '=')
        {
            for (int j = 0; j < length; ++j)
            {
                str[j] = str[j + 1];
            }
            length--;
        }
        str[length] = '\0';

        /* Deleting ' ' at the start if there is one */
        if (str[0] == ' ')
        {
            for (int j = 0; j < length; ++j)
            {
                str[j] = str[j + 1];
            }
            length--;
        }
        str[length] = '\0';

        /* Removing unnecessary '\n' at the end */
        if (str[length - 1] == '\n' || str[length - 1] == ' ')
        {
            str[length - 1] = '\0';
        }
    }
