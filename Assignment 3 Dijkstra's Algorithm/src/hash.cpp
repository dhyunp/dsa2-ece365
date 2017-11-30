/*
Donghyun Park
Prof. Sable
DSA II Assignment #1 Hash Tables
*/

#include <iostream>
#include "hash.h"

//inserts hashed keys into the hash table. returns on 0 on success, 1 on failure, 2 on rehash failure.
int hashTable::insert(const std::string &key, void *pv)
{
  int hashPos = hash(key);
  int delPos = -1;

  while(data[hashPos].isOccupied)
  {
    if(data[hashPos].key == key)
    {
      if(!data[hashPos].isDeleted)
      {
        return 1;
      }else{
        data[hashPos].isDeleted = false;
        return 0;
      }
    }else{
      if(data[hashPos].isDeleted && delPos == -1)
      {
        delPos = hashPos;
      }
    }

    if(hashPos == capacity - 1)
    {
      hashPos = 0;
    }else{
      hashPos++;
    }
  }

  if(delPos != -1)
    {
      hashPos = delPos;
    }

  data[hashPos].key = key;
  data[hashPos].isOccupied = true;
  data[hashPos].isDeleted = false;
  data[hashPos].pv = pv;
  filled++;

  if((2*filled) > capacity)
  {
    if(!rehash())
    {
      return 2;
    }
  }

  return 0;
}

//checks if the key is already inserted in the hash table
bool hashTable::contains(const std::string &key)
{
  if(findPos(key) == -1)
  {
    return false;
  }

  return true;
}

//
void *hashTable::getPointer(const std::string &key, bool *b)
{
  int hashPos = findPos(key);

  if(hashPos == -1)
  {
    if(b != NULL)
    {
      *b = false;
    }
    return NULL;
  }else{
    if(b != NULL)
    {
      *b = true;
    }
  }

  return data[hashPos].pv;
}

int hashTable::setPointer(const std::string &key, void *pv)
{
  int hashPos = findPos(key);

  if(hashPos == -1)
  {
    return 1;
  }else{
    data[hashPos].pv = pv;
  }

  return 0;
}

bool hashTable::remove(const std::string &key)
{
  int hashPos = findPos(key);

  if (hashPos == -1)
  {
    return false;
  }

  data[hashPos].isDeleted = true;
  return true;
}

//hash function for keys
int hashTable::hash(const std::string& str)
{
  unsigned int hash = 0xAAAAAAAA;

  for(std::size_t i = 0; i < str.length(); i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ str[i] * (hash >> 3)) :
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }

   return hash %capacity;
}

//if key is already in the hash table, search for the position of the key
int hashTable::findPos(const std::string &key)
{
  int hashPos = hash(key);

  while(data[hashPos].isOccupied)
  {
    if(data[hashPos].key == key)
    {
      if(!data[hashPos].isDeleted)
      {
        return hashPos;
      }else{
        return -1;
      }
    }else{
      if(hashPos == capacity - 1)
      {
        hashPos = 0;
      }else{
        hashPos++;
      }
    }
  }
  return -1;
}

//if the capacity of the initial hash table has been filled more than half way, transfer data to a temp vector, rehash the hash table then transfer data in temp vector back into the new hash table
bool hashTable::rehash()
{
  int prevCapacity = capacity;
  capacity = getPrime(2*prevCapacity);

  if(capacity == 0)
  {
    return false;
  }

  std::vector<hashItem> copy = data;
  data.resize(capacity);

  if(data.size() != capacity)
  {
    return false;
  }

  for(int i = 0; i < capacity; i++)
  {
    hashItem &temp1 = data.at(i);
    temp1.key = "";
    temp1.isOccupied = false;
    temp1.isDeleted = false;
    temp1.pv = nullptr;
  }

  filled = 0;

  for(int i = 0; i < prevCapacity; i++)
  {
    hashItem temp2 = copy.at(i);

    if(temp2.isOccupied && !temp2.isDeleted)
    {
      insert(temp2.key, temp2.pv);
    }
  }

  return true;
}

//chooses a prime number for the hash table size
unsigned int hashTable::getPrime(int size)
{
  static unsigned int hashPrime[] = {98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917,
    25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

  int i = 0;
  while(hashPrime[i] < size)
  {
    i++;
  }

  return hashPrime[i];
}

//initiates the hash table properties
hashTable::hashTable(int size)
{
  capacity = getPrime(size);
  filled = 0;
  hashItem empty;

  empty.key = "";
  empty.isOccupied = false;
  empty.isDeleted = false;
  empty.pv = nullptr;

  data.resize(capacity, empty);
}
