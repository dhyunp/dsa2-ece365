/*
Donghyun Park
Prof. Sable
DSA II Assignment #3 Dijkstra's Algorithm
*/

#include <iostream>
#include <time.h>
#include "graph.h"

using namespace std;

int main(){
  string file;
  string vertex;
  string output;
  clock_t timer;

  cout << "Enter name of graph file: ";
  cin >> file;
  cout << "Enter a valid vertex id for the starting vertex: ";
  cin >> vertex;

  graph graph;
  graph.insertFile(file);

  while(!graph.checkHash(vertex)){
    cout<< "Please enter a valid vertex id for the starting vertex: ";
    cin >> vertex;
  }
  timer = clock();
  graph.applyDijk(vertex);
  timer = clock() - timer;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << ((float)timer)/CLOCKS_PER_SEC << endl;
  cout << "Enter name of output file: ";
  cin >> output;

  graph.outputFile(output, vertex);
  return 0;
}
