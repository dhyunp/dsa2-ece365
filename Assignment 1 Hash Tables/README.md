Hash Tables
=======

Construction of a Hash Table data structure to build a dictionary and then spell check a file

## Description ##

The objective for this assignment was to create a data structure that would initialize and create a hash table class that would take in strings and pass it through a hash function and allocate it to a table of given size. The hash table uses linear probing as its iterating method, in the case that a spot created by hash function proved to be occupied or lazy-deleted(as in not an actual delete, just marking as deleted). Once the table is created, the program takes in a text file, a dictionary file, and compares the two together and creates an output file that specifies where a 'non-valid' word or 'too-long' of a word is located.

## Compilation ##

To compile, type the following command:

`# make`
