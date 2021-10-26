//
// Created by Anton on 30.05.2021.
//

#ifndef HUFFMAN_CODING_COMPRESSION_H
#define HUFFMAN_CODING_COMPRESSION_H


/* there are 256 possible characters */

#define NUM_CHARS 255

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../logging/logging.h"

/***
 * struct describing node of huffman tree
 */
typedef struct treenode treenode;

struct treenode
{
    int freq;            /* frequency; is the priority for heap */
    unsigned char ch;    /* character, if any */
    treenode *left,      /* left child of Huffman tree (not heap!) */
             *right;     /* right child of Huffman tree */
};

/***
 * this is a priority queue implemented as a binary heap
 */
typedef struct pq
{
    int heap_size;
    treenode *A[NUM_CHARS];
} PQ;

/***
 * @result: create an empty queue
 */

void create_pq(PQ *p);

/***
 * @result: this heap node's parent
 */

int parent(int i);

/***
 * @result: this heap node's left kid
 */

int left(int i);

/***
 * @result: this heap node's right kid
 */

int right(int i);

/***
 * @result: makes the subheap with root i into a heap , assuming left(i) and
 * right(i) are heaps
 */
void heapify(PQ *p, int i);

/***
 * @result: insert an element into the priority queue.  r->freq is the priority
 */
void insert_pq(PQ *p, treenode *r);

/***
 * @param p: queue to extract from
 * @return: extracted node
 * @result: remove the element at head of the queue (i.e., with minimum frequency)
 */
treenode *extract_min_pq(PQ *p);

/***
 * @param f: File to read values from
 * @result: read the file, computing the frequencies for each character
 * and placing them in v[]
 */
unsigned int get_frequencies(FILE *f, unsigned int v[]);

/***
 * @result: make the huffman tree from frequencies in freq[] (Huffman's Algorithm)
 */
treenode *build_huffman(const unsigned int *freqs);

/***
 * @result: traverse the Huffman tree, building up the codes in codes[]
 */
void traverse(treenode *r,    /* root of this (sub)tree */
              int level,    /* current level in Huffman tree */
              char code_so_far[], /* code string up to this point in tree */
              char *codes[]);

/***
 * @var nbits: Number of bits coded
 * @var current_byte: Byte which is being coded right now
 * @var nbytes: Number of bytes coded
 * global variables, a necessary evil
 */
int nbits, current_byte, nbytes;

/***
 * @param f: file to write into
 * @param b: code, 0 or 1
 * @result: output a single bit to an open file
 */
void bitout(FILE *f, char b);

/***
 * @param infile: File to read from
 * @param outfile: File to write into coded text
 * @param codes: Codes for characters
 * @result: using the codes in codes[], encode the file in infile, writing
 * the result on outfile
 */
void encode(FILE *infile, FILE *outfile, char **codes);

/***
 * @param input: name of file to compress_compare
 * @result: Compresses file with given name
 */
void compress(const char *input, char *fname);

/***
 * @param input: File to read coded data from
 * @param output: File to write decoded data to
 * @param r: root of the huffman tree
 * @result: decodes text from given file
 */
void decode(FILE *input, FILE *output, const treenode *r, int n);

/***
 * @param input: file to read input data from
 * @result: decodes text from given file
 */
void decompress(const char *input, char *fname);

#endif //HUFFMAN_CODING_COMPRESSION_H
