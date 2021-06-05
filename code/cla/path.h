//
// Created by Anton on 25.04.2021.
//

#ifndef HUFFMAN_CODING_PATH_H
#define HUFFMAN_CODING_PATH_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include "../logging/logging.h"

/***
 * @param DirName: Name of directory, in which file will be located
 * @param FileName: Name of file to create into directory
 * @return NULL: Any error while creating directory/file
 * @return String: Path to the file
 * @result: Created new directory (if needed) and created a file in it
 * */
char *path(const char *DirName, const char *FileName);

#endif //HUFFMAN_CODING_PATH_H
