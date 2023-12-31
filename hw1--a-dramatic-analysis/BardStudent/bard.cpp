#include "bard.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <cstring>

#include <typeinfo>

using namespace std;

int main(int argc, char** argv){
    if (argc < 3) {
        throw invalid_argument("Need input and output file. Example: ./bard input.txt output.txt");
    
    }
    ifstream in;
    ofstream out;
    string word;

    in.open("shakespeare-cleaned5.txt");
    LinkedList l;
    int largestLen = 10;
    LinkedList* rankedWords = new LinkedList[largestLen];
    while (getline(in,word)) {    
        if ((int)word.length()-4 > largestLen) {
          int oldLen = largestLen;
          largestLen = word.length()-4;
          LinkedList* increasedSize = new LinkedList[largestLen];
          for (int i = 0; i < oldLen; i++) {
            increasedSize[i] = rankedWords[i];
          }
          delete[] rankedWords;
          rankedWords = increasedSize;
        }  
        rankedWords[word.length()-5].insert(word);
    }
    for (int i = 0; i < largestLen; i++){
      rankedWords[i].sort();
    }
    in.close();

    in.open(argv[1]);
    out.open(argv[2]);
    char* cstr;
    int length;
    int rank;

    while (getline(in,word)) {
      cstr = strdup(word.c_str());
      length = stoi(strtok(cstr, " "));
      rank = stoi(strtok(NULL, "\n"));
      WordNode* n = (rank > -1 && length <= largestLen+4 && length > 4) ? rankedWords[length-5].getHead() : NULL;
      for (int i = 0; n && i < rank; i++) {
        n = n->next;
      }
      out << (n ? n->data : "-") << endl;
      free(cstr);
    }
    for (int i = 0; i < largestLen; i++) {
      rankedWords[i].deleteList();
    }
    delete[] rankedWords;
    return 0;
}