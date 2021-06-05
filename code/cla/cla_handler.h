//
// Created by Anton on 25.04.2021.
//

#ifndef HUFFMAN_CODING_CLA_HANDLER_H
#define HUFFMAN_CODING_CLA_HANDLER_H

/***
 * @param argc: Number of command line arguments
 * @param argv: Command line arguments
 * @return -3: argc[1] ,matched '--compare'
 * @return -2: argv[1] matched '--help'
 * @return -1: argc[1] ,matched '--test'
 * @return 0: Normal program booting
 * @result: Checked given by user arguments
 * */
int handler(int argc, const char **argv);

/***
 * @params: No params needed
 * @return String: path to the log file
 * @result: Reads .ini file and creates path by read values,
 * if error occurs creates another path by const values (Folder Huffman logs, file logs.txt)
 * */
char *init_logpath();

/***
 * @param argument: index to matrix (list of strings) to get needed file name
 * @param argc: number of given cla arguments
 * @param argv: cla arguments
 * @return names[0]: Path to log file
 * @return names[1]: Given file name in cla (optional)
 * @result: Checks cla, if matches any acts necessarily, initializes logpath and writes it to names[0]
 * */
char *files_init(int argument, int argc, const char **argv);

#endif //HUFFMAN_CODING_CLA_HANDLER_H
