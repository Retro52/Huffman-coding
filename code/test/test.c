#include "../logging/logging.h"
#include "../cla/help.h"
#include "../cla/cla_handler.h"
#include "../tasks/compression.h"
#include "../logging/iniparser.h"
#include "../cla/path.h"

/*
 * Function to test .ini parser functions
 */
void test_parser()
{
    int res;
    void *test = NULL;

    /* Passing as an argument file, which does not exist */
    res = find_value("Not exist", "log", "loglevel", &test);
    if (res != -1)
    {
        printf("Error [parser]: expected code %d, got instead %d", -1, res);
        exit(1);
    }

    /* Passing as an argument a section, which is not at file */
    res = find_value(INI_FILE, "not exist", "instead", &test);
    if (res != -1)
    {
        printf("Error [parser]: expected code %d, got instead %d", -1, res);
        exit(2);
    }

    /* Passing as an argument a value name which is not in file */
    res = find_value(INI_FILE, "log", "not_exist", &test);
    if (res != -1)
    {
        printf("Error [parser]: expected code %d, got instead %d", -1, res);
        exit(3);
    }

    /* Trying to read a digit from .ini file */
    res = find_value(INI_FILE, "log", "loglevel", &test);
    if (res != 1)
    {
        printf("Error [parser]: expected code %d, got instead %d", 1, res);
        exit(4);
    }

    /* Trying to read a string from file */
    res = find_value(INI_FILE, "log", "logpath", &test);
    if (res != 2)
    {
        printf("Error [parser]: expected code %d, got instead %d", 1, res);
        exit(5);
    }

    /* All tests passed */
    printf("All parser tests passed!\n");
}

void test_compression()
{
    compress("new");
}

void test_decompression()
{
    decompress("new.huf");
}

void test_functionality()
{
    FILE *new = fopen("new", "r");
    FILE *decompressed = fopen("new.txt", "r");
    if (!new || !decompressed)
    {
        printf("Error [functional test]: One of files does not exist");
        exit(6);
    }
    char a, b;
    long int word_count = 0;
    int rows_count = 0;
    while (!feof(new) && ! feof(decompressed))
    {
        a = (char) fgetc(new);
        b = (char) fgetc(decompressed);
        if (a == -1 || b == -1)
        {
            break;
        }

        if (a != b)
        {
            printf("Error [functionality test]: row %d letter %ld does not match\n"
                   "a == %c, b == %c", rows_count, word_count, a, b);
            exit(7);
        }
        if (a == '\n')
        {
            rows_count++;
        }
        word_count++;
    }
    printf("Functionality test passed!\n");
}

void test_compression_huge()
{
    compress("huge");
}

void test_decompression_huge()
{
    decompress("huge.huf");
}

void test_functionality_huge()
{
    FILE *new = fopen("huge", "r");
    FILE *decompressed = fopen("huge.txt", "r");
    if (!new || !decompressed)
    {
        printf("Error [functional test]: One of files does not exist");
        exit(8);
    }
    char a, b;
    long int word_count = 0;
    int rows_count = 0;
    while (!feof(new) && ! feof(decompressed))
    {
        a = (char) fgetc(new);
        b = (char) fgetc(decompressed);
        if (a == -1 || b == -1)
        {
            break;
        }

        if (a != b)
        {
            printf("Error [functionality test]: row %d letter %ld does not match\n"
                   "a == %c, b == %c", rows_count, word_count, a, b);
            exit(9);
        }
        if (a == '\n')
        {
            rows_count++;
        }
        word_count++;
    }
    printf("Huge functionality test passed!\n");
}

void test_cla()
{
    char **argv = calloc(3, sizeof(char *));
    for (int i = 0; i < 3; ++i)
    {
        argv[i] = calloc(200, sizeof(char));
    }

    strcpy(argv[1], "--help");
    int res = handler(0,(const char **) argv);
    if (res != 0)
    {
        printf("Error [cla]: expected %d, got %d\n", 0, res);
        exit(10);
    }

    strcpy(argv[1], "--help");
    res = handler(2,(const char **) argv);
    if (res != -2)
    {
        printf("Error [cla]: expected %d, got %d\n", -2, res);
        exit(10);
    }

    strcpy(argv[1], "--test");
    res = handler(2,(const char **) argv);
    if (res != -1)
    {
        printf("Error [cla]: expected %d, got %d\n", -1, res);
        exit(10);
    }

    strcpy(argv[1], "--compare");
    res = handler(2,(const char **) argv);
    if (res != -3)
    {
        printf("Error [cla]: expected %d, got %d\n", -3, res);
        exit(10);
    }

    printf("All cla test passed!\n");
}

void test_path()
{
    char *Test;
    Test = path(NULL, NULL);
    if (Test != NULL)
    {
        printf("Error [path]: NULL expected, got %p instead\n", Test);
    }
    Test = path("Directory", NULL);
    if (Test != NULL)
    {
        printf("Error [path]: NULL expected, got %p instead\n", Test);
    }
    Test = path(NULL, "File");
    if (Test != NULL)
    {
        printf("Error [path]: NULL expected, got %p instead\n", Test);
    }
    Test = path("Dir", "file.txt");
    if (strcmp(Test, "Dir/file.txt") != 0)
    {
        printf("Error [path]: 'Dir/file.txt' expected, got %s instead\n", Test);
    }
    printf("All path tests passed!\n");
}

void test()
{
    printf("Testing started: \n");
    test_cla();
    test_path();
    test_parser();
    printf("Functional test started: \n");
    test_compression();
    test_decompression();
    test_functionality();
    printf("Text with ~100`000 symbols compressed & decompressed successfully\n");
    test_compression_huge();
    test_decompression_huge();
    test_functionality_huge();
    printf("Text with ~2`500`000 symbols compressed & decompressed successfully\n");
    printf("Load test started: \n");
    for (int i = 0; i < 50; ++i)
    {
        printf("Test #%d:\n", i + 1);
        test_compression();
        test_decompression();
        test_functionality();
    }
    printf("Load test passed!: \n");
    printf("All tests passed!\n");
}

int run_tests(void)
{
    test();
    return 0;
}