//
// Created by Anton on 25.04.2021.
//

#ifndef HUFFMAN_CODING_INIPARSER_H
#define HUFFMAN_CODING_INIPARSER_H

#include "stdbool.h"
#include "logging.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "time.h"
#include "../cla/cla_handler.h"

/***
 * @param file_name: .ini file name, which need to be red
 * @param section: section in .ini file, where variable is supposed to be
 * @param value: variable name
 * @param address: pointer to pointer of type void *, by this address found value will be written
 * @return -1: error while reading ini file (couldn't open file / couldn`t close / didn`t find value, ect.)
 * @return 1: returned a number
 * @return 2: returned a string
***/
int find_value(const char *file_name, const char *section, const char *value, void **address);

/***
 * @param section: name of section to find
 * @param file: opened .ini file
 * @return -1: any error while reading file
 * @return 0: section found
 * */
int find_section(const char *section, FILE *file);

/***
 * @param value: name of value to find
 * @param file: opened .ini file
 * @return NULL: any error
 * @return Not NULL pointer: red value as string
 * */
char *read_value(const char *value, FILE *file);

/***
 * @param str: string to edit
 * @return: Nothing to return, function just removes all unnecessary characters from string
 * */
void edit_str(char str[]);

/***
 * @param string: a string to check
 * @return true: string can be converted to double
 * @return false: string can not be converted
 * */
bool convertable(const char *string);

#endif //HUFFMAN_CODING_INIPARSER_H
