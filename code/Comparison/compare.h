//
// Created by Anton on 01.06.2021.
//

#ifndef HUFFMAN_CODING_COMPARE_H
#define HUFFMAN_CODING_COMPARE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "../tasks/compression.h"

unsigned int get_frequencies_compare(char *string, unsigned int *v);

treenode *build_huffman_compare(const unsigned int *freqs);

void compress_compare();

void test_compare(int cases);

int compare(void);
#endif //HUFFMAN_CODING_COMPARE_H
