/*
Donghyun Park
Prof. Sable
DSA II Assignment #1 Hash Tables
*/

#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

//takes the dictionary file name and opens it to take into hash table
void buildDict(ifstream &dictionary)
{
  string dictName;
  cout << "Enter name of dictionary: ";
  cin >> dictName;
  dictionary.open(dictName.c_str());
}

//takes the lines from the opened dictionary file and inserts it into the hash table using the hash equation
void loadDict(hashTable &HashTable, ifstream &dictionary)
{
  clock_t time1, time2;
  double timeMeasure;

  string lines;

  time1 = clock();
  while(getline(dictionary, lines))
  {
    transform(lines.begin(), lines.end(), lines.begin(), ::tolower);
    HashTable.insert(lines);
  }
  time2 = clock();

  timeMeasure = (double(time2) - double(time1)) / CLOCKS_PER_SEC;

  cout << "Total time (in seconds) to load dictionary: " << timeMeasure << endl;
}

//opening input and output file for comparision and writing out the differences respectively
void getInputOutput(ifstream &input, ofstream &output, bool inout)
{
  string inputName, outputName;
  if(inout == true)
  {
    cout << "Enter name of input file: ";
    cin >> inputName;
    input.open(inputName.c_str());
  }else if(inout == false){
    cout << "Enter name of output file: ";
    cin >> outputName;
    output.open(outputName.c_str());
  }
}

//performs spellcheck on the input document with the hashtable'd dictionary while considering constitution of a word
void spellCheck(hashTable &HashTable, ifstream &input, ostream &output)
{
  enum class varState {inputWord, wordSeparator, longWord};
  varState state = varState::inputWord;
  long lineNum = 1;
  string buf = "";
  char ascii;

  clock_t time1, time2;
  double timeMeasure;

  time1 = clock();

  while(input.get(ascii))
  {
    ascii = tolower(ascii);

    switch(state)
    {
      case varState::inputWord:
        //lowercase letter, number digit, hyphen, apostrophe
        if((ascii == 39) || (ascii == 45) || ((ascii >= 48) && (ascii <= 57)) || ((ascii >= 97) && (ascii <= 122)))
        {
          if(buf.length() >= 20)
          {
            output << "Long word at line " << lineNum << ", starts: " << buf << endl;
            buf = "";
            state = varState::longWord;
          }else{
            buf.push_back(ascii);
          }
        }else{
          if(!any_of(buf.begin(), buf.end(), ::isdigit) && !HashTable.contains(buf) && (buf.length() > 0))
          {
            output << "Unknown word at line " << lineNum << ": " << buf << endl;
          }
          buf = "";
          state = varState::wordSeparator;
        }

        break;

      case varState::wordSeparator:
        if((ascii == 39) || (ascii == 45) || ((ascii >= 48) && (ascii <= 57)) || ((ascii >= 97) && (ascii <= 122)))
          buf.push_back(ascii);
          state = varState::inputWord;
        break;

      case varState::longWord:
        if(!((ascii == 39) || (ascii == 45) || ((ascii >= 48) && (ascii <= 57)) || ((ascii >= 97) && (ascii <= 122))))
        {
          state = varState::wordSeparator;
        }

        break;
    }

    if (ascii == '\n')
    {
      lineNum++;
    }


  }
  time2 = clock();

  timeMeasure = (double(time2) - double(time1)) / CLOCKS_PER_SEC;

  cout << "Total time (in seconds) to check document: " << timeMeasure << endl;
}

int main()
{
  hashTable table(10);
  ifstream dictionary, input;
  ofstream output;

  buildDict(dictionary);
  loadDict(table, dictionary);

  getInputOutput(input, output, true);
  getInputOutput(input, output, false);

  spellCheck(table, input, output);

  dictionary.close();
  input.close();
  output.close();

  return 0;
}
