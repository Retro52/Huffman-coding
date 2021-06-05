//
// Created by Anton on 01.06.2021.
//

#ifndef HUFFMAN_CODING_TEST_H
#define HUFFMAN_CODING_TEST_H
/***
 * @result:tests iniparser functions
 * */
void test_parser();
/***
 * @result:tests compression feature
 * */
void test_compression();
/***
 * @result:tests decompression feature
 * */
void test_decompression();
/***
 * @result:compares compressed & decompressed files
 * */
void test_functionality();
/***
 * @result:tests decompression feature with huge file
 * */
void test_compression_huge();
/***
 * @result:tests decompression feature with huge file
 * */
void test_decompression_huge();
/***
 * @result:compares compressed & decompressed huge files
 * */
void test_functionality_huge();
/***
 * @result:tests cla_handler functions
 * */
void test_cla();
/***
 * @result:tests path functions
 * */
void test_path();
/***
 * @result:tests runs all tests functions
 * */
void test();
/***
 * @result:tests runs all tests functions
 * */
int run_tests(void);

#endif //HUFFMAN_CODING_TEST_H
