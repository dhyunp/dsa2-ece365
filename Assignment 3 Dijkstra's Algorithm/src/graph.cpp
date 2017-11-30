/*
Donghyun Park
Prof. Sable
DSA II Assignment #3 Dijkstra's Algorithm
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <climits>
#include "graph.h"

using namespace std;

void graph::insertFile(string &file){
  ifstream infile(file);
  string line, v1, v2, edgeCost;
  node *v1p, *v2p;

  while(getline(infile, line)){
    istringstream iss(line);
    iss >> v1 >> v2 >> edgeCost;
    node encNode;
    //if the node hash not been encountered before, insert into hash table and list in order
    if(this->visitedNodes.contains(v1) == false){
      encNode.name = v1;
      encNode.p = nullptr;
      encNode.explored = false;
      encNode.i = INT_MAX;
      encNode.adjList = {};

      this->nodeList.push_back(encNode);
      this->visitedNodes.insert(v1, &this->nodeList.back());
    }
    v1p = static_cast<node*>(this->visitedNodes.getPointer(v1));

    if(this->visitedNodes.contains(v2) == false){
      encNode.name = v2;
      encNode.p = nullptr;
      encNode.explored = false;
      encNode.i = INT_MAX;
      encNode.adjList = {};

      this->nodeList.push_back(encNode);
      this->visitedNodes.insert(v2, &this->nodeList.back());
    }
    v2p = static_cast<node*>(this->visitedNodes.getPointer(v2));
    cost edge;
    edge.destination = v2p;
    edge.cost = stoi(edgeCost);
    v1p->adjList.push_back(edge); //adding destination and cost to adj list of vertex1
  }

  infile.close();
}

bool graph::checkHash(string &vertex){
  return this->visitedNodes.contains(vertex);
}

void graph::applyDijk(string &startVertex){
  node* startPoint = static_cast<node*>(this->visitedNodes.getPointer(startVertex));
  heap undiscNodes(this->nodeList.size());

  startPoint->i = 0; //starting node has distance 0
  startPoint->p = startPoint; //node initially starts pointing to itself and seeing undiscovered nodes adjacent to it

  for(list<node>::iterator it = this->nodeList.begin(); it != this->nodeList.end(); it++){  //insert all nodes in the list into a heap
    undiscNodes.insert(it->name, it->i, &(*it));
  }

  string nowName = "";  //below 3 are empty values to be over written when performing deleteMin
  int nowCost = 0;
  node *nowNode = nullptr;

  while(undiscNodes.deleteMin(&nowName, &nowCost, &nowNode) == 0){  //while the deletion of the minimum node still returns a 0
    nowNode->explored = true;

    for(list<cost>::iterator costIt = nowNode->adjList.begin(); costIt != nowNode->adjList.end(); costIt++){
      if((costIt->destination->explored == false) && (nowNode->i + costIt->cost < costIt->destination->i)){
        costIt->destination->i = costIt->cost + nowNode->i;
        undiscNodes.setKey(costIt->destination->name, costIt->destination->i);
        costIt->destination->p = nowNode;
      }
    }
  }

}

void graph::outputFile(string &file, string &startVertex){
  ofstream output(file);
  node current = *this->nodeList.begin();

  for(list<node>::iterator nodeIt = this->nodeList.begin(); nodeIt != this->nodeList.end(); nodeIt++){
    current = *nodeIt;
    string pathName = current.name;

    while(current.name != startVertex){
      if(current.p != nullptr){
        current = *current.p;
        pathName = current.name + ", " + pathName;
      }else{
        pathName =  "NO PATH\n";
        break;
      }
    }

    string outputLine;

    if(pathName == "NO PATH\n"){
      outputLine = nodeIt->name + ": " + pathName;
    }else{
      outputLine = nodeIt->name + ": " + to_string(nodeIt->i) + " [" + pathName + "]\n";
    }

    output << outputLine;
  }

  output.close();
}
