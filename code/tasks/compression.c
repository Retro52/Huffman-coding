//
// Created by Anton on 30.05.2021.
//

#include "compression.h"

#define LF_COMPR "compression.c"

void create_pq(PQ *p)
{
    p->heap_size = 0;
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return i * 2 + 1;
}

int right(int i)
{
    return i * 2 + 2;
}

void heapify(PQ *p, int i)
{
    int l, r, smallest;
    treenode *t;

    l = left(i);
    r = right(i);

    /* find the smallest of parent, left, and right */

    if (l < p->heap_size && p->A[l]->freq < p->A[i]->freq)
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }
    if (r < p->heap_size && p->A[r]->freq < p->A[smallest]->freq)
    {
        smallest = r;
    }

    /* swap the parent with the smallest, if needed. */

    if (smallest != i)
    {
        t = p->A[i];
        p->A[i] = p->A[smallest];
        p->A[smallest] = t;
        heapify(p, smallest);
    }
}

void insert_pq(PQ *p, treenode *r)
{
    int i;

    p->heap_size++;
    i = p->heap_size - 1;

    /*
     * Om this step we would like to place r at the end of the array,
     * but this might violate the heap property. That means,
     * we will start at the end and work our way up
     */
    while ((i > 0) && (p->A[parent(i)]->freq > r->freq))
    {
        p->A[i] = p->A[parent(i)];
        i = parent(i);
    }
    p->A[i] = r;
}

treenode *extract_min_pq(PQ *p)
{
    treenode *r;

    if (p->heap_size == 0)
    {
        printf("[ERROR] Heap underflow!\n");
        LOG(LOGLEVEL_ERROR, LF_COMPR, "Heap underflow! Unable to build a huffman tree!\n");
        exit(1);
    }

    /* get return value out of the root */
    r = p->A[0];

    /* take the last and stick it in the root (just like heapsort) */
    p->A[0] = p->A[p->heap_size - 1];

    /* one less thing in queue */
    p->heap_size--;

    /* left and right are a heap, make the root a heap */
    heapify(p, 0);
    return r;
}

unsigned int get_frequencies(FILE *f, unsigned int v[])
{
    int r, n;

    /* n will count characters */
    for (n = 0;; n++)
    {

        /* fgetc() gets an unsigned char, converts to int */
        r = fgetc(f);

        /* no more?  get out of loop */
        if (feof(f))
        {
            break;
        }

        /* one more of this character */
        v[r]++;
    }
    return n;
}

treenode *build_huffman(const unsigned int *freqs)
{
    int i, n;
    treenode *x, *y, *z;
    PQ p;

    /* make an empty queue */
    create_pq(&p);

    /*
     * For each character, make a heap/tree node with its value
     * and frequency
     */
    for (i = 0; i < NUM_CHARS; i++)
    {
        if (freqs[i] != 0)
        {
            x = malloc(sizeof(treenode));
            /* its a leaf of the Huffman tree */
            x->left = NULL;
            x->right = NULL;
            x->freq = (int) freqs[i];
            x->ch = (char) i;

            /* put this node into the heap */
            insert_pq(&p, x);
        }
    }

    /* at this point, the heap is a "forest" of singleton trees */

    n = p.heap_size - 1;

    /*
     * If we insert two things and remove one each time,
     * at the end of heap_size - 1 iterations, there will be
     * one tree left in the heap
     */
    for (i = 0; i < n; i++)
    {

        /*
         * Parental node for two smaller ones
         * Make a new node z from the two least frequent nodes x and y
         */
        z = malloc(sizeof(treenode));
        x = extract_min_pq(&p);
        y = extract_min_pq(&p);
        /*
         * Small bugfix - if we will get a node with 0 frequency on left and non 0 on right z will be created
         * We don`t need that, so we are better stop building a tree on this step
         */

        if (x->freq == 0 && y->freq != 0)
        {
            z = y;
            insert_pq(&p, z);
        }

        else
        {
            z->left = x;
            z->right = y;
            /* z's frequency is the sum of x and y */
            z->freq = x->freq + y->freq;
            /* put this back in the queue */
            insert_pq(&p, z);
        }
    }

    /* return the only thing left in the queue, the whole Huffman tree */
    return extract_min_pq(&p);
}

void traverse(treenode *r,        /* root of this (sub)tree */
              int level,          /* current level in Huffman tree */
              char code_so_far[], /* code string up to this point in tree */
              char *codes[])      /* array of codes */
{
    /* if we're at a leaf node, */
    if ((r->left == NULL) && (r->right == NULL))
    {
        /* put in a null terminator */
        code_so_far[level] = 0;

        /* make a copy of the code and put it in the array */
        codes[r->ch] = strdup(code_so_far);
    }
    else
    {
        /* not at a leaf node.  go left with bit 0 */
        code_so_far[level] = '0';
        traverse(r->left, level + 1, code_so_far, codes);

        /* go right with bit 1 */
        code_so_far[level] = '1';
        traverse(r->right, level + 1, code_so_far, codes);
    }
}

void    bitout(FILE *f, char b)
{
    /* shift current byte left one */
    current_byte <<= 1;

    /* put a one on the end of this byte if b is '1' */
    if (b == '1')
    {
        current_byte |= 1;
    }

    /* one more bit */
    nbits++;

    /* enough bits?  write out the byte */
    if (nbits == 8)
    {
        fputc(current_byte, f);
        fflush(f);
        nbytes++;
        nbits = 0;
        current_byte = 0;
    }
}

void encode(FILE *infile, FILE *outfile, char **codes)
{
    unsigned char ch;
    char *s;

    /* initialize globals for bitout() */
    current_byte = 0;
    nbits = 0;
    nbytes = 0;

    /* continue until end of file */
    for (;;)
    {

        /* get a char */
        ch = fgetc(infile);
        if (feof(infile))
        {
            break;
        }

        /* put the corresponding bitstring on outfile */
        for (s = codes[ch]; *s; s++)
        {
            bitout(outfile, *s);
        }
    }

    /* finish off the last byte */
    while (nbits)
    {
        bitout(outfile, '0');
    }
}

void compress(const char *input)
{
    FILE *f, *g;
    treenode *r;
    unsigned int n, freqs[NUM_CHARS];
    char *codes[NUM_CHARS], code[NUM_CHARS], fname[100];

    /* set all frequencies to zero */
    memset(freqs, 0, sizeof(freqs));

    /* open command line argument file */
    f = fopen(input, "r");
    if (!f)
    {
        perror(input);
        LOG(LOGLEVEL_ERROR, LF_COMPR,
            "Input file for compression not found. Compression terminated");
        return;
    }

    /* compute frequencies from this file */
    n = get_frequencies(f, freqs);
    fclose(f);

    /* make the huffman tree */
    r = build_huffman(freqs);

    /* traverse the tree, filling codes[] with the codes */
    traverse(r, 0, code, codes);

    /* name the output file something.huf */
    sprintf(fname, "%s.huf", input);
    g = fopen(fname, "wb");
    if (!g)
    {
        perror(fname);
        LOG(LOGLEVEL_ERROR, LF_COMPR,
            "Output file %s opening error\n Compression terminated",
            fname);
        return;
    }

    /* write frequencies to file so they can be reproduced */
    fwrite(freqs, NUM_CHARS, sizeof(int), g);

    /* write number of characters to file as binary int */
    fwrite(&n, 1, sizeof(int), g);

    /* open input file again */
    f = fopen(input, "r");
    if (!f)
    {
        perror(input);
    }

    /* encode f to g with codes[] */
    encode(f, g, codes);
    fclose(f);
    fclose(g);

    /* brag */
    LOG(LOGLEVEL_INFO, LF_COMPR, "File compressed successfully\n");
    printf("File compressed successfully and %s is %0.2f%% of %s\n",
           fname, ((float) nbytes / (float) n) * 100.0, input);
}

void decode(FILE *input, FILE *output, const treenode *r, int n)
{
    treenode *temp = (treenode *) r;
    while (n > 0)
    {
        int codded = fgetc(input);
        if (codded == -1)
        {
            return;
        }
        int received[8];
        for (int i = 0; i < 8; ++i)
        {
            received[i] = codded & 1;
            codded = codded >> 1;
        }
        for (int j = 0; j < 8; ++j)
        {
            if (n == 0)
            {
                return;
            }
            if (received[7 - j] == 1 && temp->right != NULL)
            {
                temp = temp->right;
                if (temp->left == NULL && temp->right == NULL)
                {
                    fputc(temp->ch, output);
                    n--;
                    temp = (treenode *) r;
                }
            }
            else if (received[7 - j] == 0 && temp->left != NULL)
            {
                temp = temp->left;
                if (temp->left == NULL && temp->right == NULL)
                {
                    fputc(temp->ch, output);
                    n--;
                    temp = (treenode *) r;
                }
            }
            else
            {
                temp = (treenode *) r;
            }
        }
    }
}

void decompress(const char *input)
{
    FILE *f, *g;
    treenode *r;
    unsigned int n, freqs[NUM_CHARS];
    char fname[100];

    /* set all frequencies to zero */
    memset(freqs, 0, sizeof(freqs));

    int len = (int) strlen(input);

    /* Checking if file extension is correct */
    if (input[len - 4] != '.' || input[len - 3] != 'h' || input[len - 2] != 'u' || input[len - 1] != 'f')
    {
        fputs(input, stderr);
        fputs(": wrong file format", stderr);
        LOG(LOGLEVEL_ERROR, LF_COMPR, "Input file has wrong encoding\n");
        return;
    }

    f = fopen(input, "rb");
    if (!f)
    {
        perror(input);
        LOG(LOGLEVEL_ERROR, LF_COMPR, "Input file for decmopression not found. Compression terminated", input);
        return;
    }


    sprintf(fname, "%s", input);
    fname[(int) strlen(input) - 4] = '\0';
    sprintf(fname, "%s.txt", fname);
    g = fopen(fname, "w");

    if (!g)
    {
        perror(fname);
        LOG(LOGLEVEL_ERROR, LF_COMPR, "Output file for decompression opening error. Decompression terminated", fname);
        return;
    }

    /* read frequencies from this file */
    fread(freqs, sizeof(unsigned int), NUM_CHARS, f);
    fread(&n, sizeof(unsigned int), 1, f);

    /* make the huffman tree */
    r = build_huffman(freqs);

    /* name the output file something.huf */
    decode(f, g, r, (int) n);

    /* brag */
    fclose(f);
    fclose(g);

    LOG(LOGLEVEL_INFO, LF_COMPR, "File compressed successfully\n");

    printf("\nFile decompressed successfully!\n");
}
