/* there are 256 possible characters */

#include "compare.h"

#define STRING "AAAAABBBBCCCDDE"


unsigned int get_frequencies_compare(char *string, unsigned int *v)
{
    int r, n;

    /* n will count characters */
    for (n = 0;n < strlen(string); n++)
    {
        r = (int) string[n];
        /* one more of this character */
        v[r]++;
    }
    return n;
}

treenode *build_huffman_compare(const unsigned int *freqs)
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

void compress_compare()
{
    unsigned int freqs[NUM_CHARS];

    /* set all frequencies to zero */
    memset(freqs, 0, sizeof(freqs));

    /* open command line argument file */

    /* compute frequencies from this file */
    get_frequencies_compare(STRING, freqs);

    /* make the huffman tree */
    build_huffman_compare(freqs);

}

void test_compare(int cases)
{
    for (int i = 0; i < cases; ++i)
    {
        compress_compare();
    }
}

int compare(void)
{
    int cases = 100;
    clock_t begin;
    clock_t end;
    begin = clock();
    for (int i = 0; i < cases; ++i)
    {
        test_compare(1000);
    }
    end = clock();
    double time_spent = (double)(end - begin);
    time_spent /= (double) cases;
    printf("Program execution time is about %.2lf microseconds\n\n", time_spent);
    system("pause");
    return 0;
}
