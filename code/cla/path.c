//
// Created by Anton on 25.04.2021.
//

#include "path.h"

char *path(const char *DirName, const char *FileName)
{
    /* Arguments check */
    if (!FileName || !DirName)
    {
        return NULL;
    }

    /* variable declaration */
    int iFd;
    char *chDirName = NULL;
    char *chFileName = NULL;
    char *chFullPath = NULL;

    struct stat sfileInfo;

    /* Argument Validation */
    chDirName = (char *) calloc(200, sizeof(char));
    chFileName = (char *) calloc(200, sizeof(char));
    chFullPath = (char *) calloc(200, sizeof(char));

    chDirName = strcpy(chDirName, DirName);
    chFileName = strcpy(chFileName, FileName);

    /* create full path of file */
    sprintf(chFullPath, "%s/%s", chDirName, chFileName);

    //check directory exists or not
    if (stat(chDirName, &sfileInfo) == -1)
    {
        mkdir(chDirName);
    }

    /* create file inside given directory */
    iFd = creat(chFullPath, 0644);

    if (iFd == -1)
    {
        free(chDirName);
        free(chFileName);
        free(chFullPath);
        return NULL;
    }
    else
    {
        /* close resources */
        close(iFd);
        free(chDirName);
        free(chFileName);
        return chFullPath;
    }
}
