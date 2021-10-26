//
// Created by Anton on 25.04.2021.
//

#ifndef HUFFMAN_CODING_LOGGING_H
#define HUFFMAN_CODING_LOGGING_H

#include <stdlib.h>
#include <stdio.h>
#include "time.h"
#include <string.h>
#include "stdarg.h"

#define INI_FILE "main.ini"

#define LOGLEVEL_FATAL 4
#define LOGLEVEL_ERROR 3
#define LOGLEVEL_WARN 2
#define LOGLEVEL_INFO 1
#define LOGLEVEL_DEBUG 0

/***
 * @result: This function reads .ini file and returns found loglevel or, if smth gone wrong,
 * default value can be returned (DEBUG - 0)
 * */
int init();

/***
 * @result: Function for logging from any program file
 * */
void LOG(int level, const char *file, const char *message, ...);

/***
 * @result: Function for logging info data
 * */
void log_info(const char *file, const char *message, va_list args);

/***
 * @result: Function for logging debug data
 * */
void log_debug(const char *file, const char *message, va_list args);

/***
 * @result: Function for logging warn data
 * */
void log_warn(const char *file, const char *message, va_list args);

/***
 * @result: Function for logging errors data
 * */
void log_error(const char *file, const char *message, va_list args);

/***
 * @result: Function for logging fatal errors data
 * */
void log_fatal(const char *file, const char *message, va_list args);

/***
 * @result: Function for writing given log message to the log file
 * */
void log_format(const char *file, const char *tag, const char *message, va_list args);

#endif //HUFFMAN_CODING_LOGGING_H
