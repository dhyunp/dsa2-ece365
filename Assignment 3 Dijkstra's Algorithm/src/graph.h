#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <string>
#include "heap.h"
#include "hash.h"

class graph{
  struct cost;
  struct node;
public:

void insertFile(std::string &file); //inserts data from infile

void applyDijk(std::string &startVertex); //dijkstra's algorithm

bool checkHash(std::string &vertex); //checks if a node is already within the hash table

void outputFile(std::string &file, std::string &startVertex);

private:
  struct cost{  //struct that defines the edge costs between vertices
    node *destination; //pointer to the destination vertex
    int cost; //edge cost of the path to the destination vertex
  };

  struct node{  //struct instead of class since node only contains data, not methods
    std::string name; //name of nodes
    node *p; //points to another node
    bool explored;  //marker for whether a node has been explored
    int i;  //distance value of node from source
    std::list<cost> adjList;  //adjacency list
  };

  std::list<node> nodeList;  //linked list of encountered nodes in graph
  hashTable visitedNodes;  //hash table containing all the previously visted nodes
};

#endif //_GRAPH_H_
