/*
Donghyun Park
Prof. Sable
DSA II Assignment #2 Priority Queue: Binary Heap Implementation
N.B. switched to a different indentation style because the previous one took too much space for no real benefit
*/

#include <iostream>
#include "heap.h"

//constructs a heap of given size
heap::heap(int capacity){
  heapCapacity = capacity;
  heapSize = 0;
  node empty;

  empty.id = "";
  empty.key = 0;
  empty.pointData = nullptr;

  heapData.resize(heapCapacity+1, empty);
  allocate = new hashTable(2*heapCapacity);
}

//inserts node into heap
int heap::insert(const std::string &id, int key, void *pv){
  if(heapSize >= heapCapacity){
    return 1;
  }else if(allocate->contains(id)){
    return 2;
  }else{

    node temp;
    temp.id = id;
    temp.key = key;
    temp.pointData = pv;

    heapSize++; //binary heap's initial node is at index 1 not 0.
    heapData[heapSize] = temp;
    node *ptr = &(heapData[heapSize]);
    allocate->insert(id, ptr);
    percolateUp(getPos(ptr));

    return 0;
  }
}

//sets key value to a node given a string id
int heap::setKey(const std::string &id, int key){
  bool b = true;
  int prevKey, nodePos;

  node *temp = static_cast<node *>(allocate->getPointer(id, &b));

  if(b == false){
    return 1;
  }else{
    prevKey = temp->key;
    temp->key = key;
    nodePos = getPos(temp);

    if(prevKey > key){
      percolateUp(nodePos);
    }else if(prevKey < key){
      percolateDown(nodePos);
    }
    return 0;
  }
}

//removes the node with the minimum key value
int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
  if(heapSize == 0){
    return 1;
  }else{
    node min = heapData[1];

    if(pId != NULL){
      *pId = min.id;
    }
    if(pKey != NULL){
      *pKey = min.key;
    }
    if(ppData !=NULL){
      *(static_cast<void **> (ppData)) = min.pointData;
    }

    heapData[1] = heapData[heapSize];
    heapSize--;
    percolateDown(1);
    allocate->remove(min.id);

    return 0;
  }
}

//removes node given a string id
int heap::remove(const std::string &id, int *pKey, void *ppData){
  bool b = true;
  int prevKey, nextKey, nodePos;

  node *temp = static_cast<node *>(allocate->getPointer(id, &b));

  if(b == false){
    return 1;
  }else{
    if(pKey != NULL){
      *pKey = temp->key;
    }
    if(ppData != NULL){
      *(static_cast<void **> (ppData)) = temp->pointData;
    }

    prevKey = temp->key;
    *temp = heapData[heapSize];
    heapSize--;
    nextKey = temp->key;
    nodePos = getPos(temp);

    if(prevKey > nextKey){
      percolateUp(nodePos);
    }else if(prevKey < nextKey){
      percolateDown(nodePos);
    }

    allocate->remove(id);

    return 0;
  }
}

//percolating up function
void heap::percolateUp(int pos){
  int parent;

  node temp = heapData[pos];

  while(pos > 1){
    parent = pos/2;

    if(temp.key < heapData[parent].key){
      heapData[pos] = heapData[parent];
      allocate->setPointer(heapData[pos].id, &heapData[pos]);
    }else{
      break;
    }
    pos = parent;
  }

  heapData[pos] = temp;
  allocate->setPointer(heapData[pos].id, &heapData[pos]);
}

//percolating down function
void heap::percolateDown(int pos){
  int child;

  node temp = heapData[pos];

  while((child = 2*pos) <= heapSize){
    if((child < heapSize) && (heapData[child].key > heapData[child+1].key)){
      child++;
    }

    if(temp.key > heapData[child].key){
      heapData[pos] = heapData[child];
      allocate->setPointer(heapData[pos].id, &heapData[pos]);
    }else{
      break;
    }
    pos = child;
  }

  heapData[pos] = temp;
  allocate->setPointer(heapData[pos].id, &heapData[pos]);
}

//getting the position index of a node
int heap::getPos(node *node){
  int pos = node - &heapData[0];
  return pos;
}
