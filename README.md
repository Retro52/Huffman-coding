# Huffman-coding

This program is my implementation of the Huffman Coding algorithm for text file compression and decompression.
You are free to use it for your projects, but it`s going to be great to leave a link to this repo as in your references.

Project structure:
    Folder "bin" - a pre-build project with ready-to-test files ("new" 
    and "huge") and *.ini files for testing.

    Folder "code" - program source code:
        Folder "cla" - part of the program responsible for command- 
    	line arguments
    
        Folder "tasks" - part with Huffman coding algorithm, 
    	compression and decompression algorithms, priority queue 
    	implementation.
    	
        Folder "logging" - files for program logs and my implementation 
    	of *.ini files parser
    	
        Folder "compare" - runs time and memory comparison between  
    	python and C implementations of Huffman coding algorithm
    	
        Folder "test" - for running unit, functional, and load testing to 
    	program.

# Instructions

Use argument:
--help for instructions;

--test for running tests;

--compare to start comparision;

-c *filename* to compress file *filename*;

-d *filename.huf* to decompress file *filename.huf*;

