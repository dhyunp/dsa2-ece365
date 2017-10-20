Heaps
=======

Construction of a priority queue using a binary heap implementation

## Description ##

The objective for this assignment was to create a data structure that would combine the previous assignemnt of hash tables and create a priority queue. A heap class and hash table class are initialized, where a string id, integer key and a pointer are indicated by the heap. A vector would hold these actual values, while the string id would be sent through a hash function to obtain a pointer that would indicate the key value to achieve efficient allocation of values in the heap. A percolate up and down strategy was implemented in reorganization of the heap, and removal of a specific value given a string id or an automatic removal of the lowest key value were implemented as well. Also the user would have the ability to set the values of the keys when indicating a string id within the heap, causing percolating movement to reorganize the data.

## Compilation ##

To compile, type the following command:

`# make`
