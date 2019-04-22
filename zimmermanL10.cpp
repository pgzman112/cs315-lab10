// Preston Zimmerman
// 4/22/19
// Lab 10

#include "BinarySearchTree.h"
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std::chrono;

void buildTree(BinarySearchTree<int>* myBst, vector<int> & vectorA);

int main(){

  BinarySearchTree<int> * myBst = new BinarySearchTree<int>();
  vector <int> vectorA;
  buildTree(myBst, vectorA);

  vector <int> vectorB;
  myBst->inOrderTrav(vectorB);
  for(int i = 0; i < vectorB.size(); i++){
    cout << vectorB[i] << " ";
  }
  cout << endl;

   int k = myBst->RankOfKey(vectorA[5]);
  if(k > 0){
    if(vectorA[5] == vectorB[k-1]){
      cout << "rank of key test successful" << endl;
    }
    else{
      cout << "rank of key test not successful" << endl;
    }
  }

  return 0;
}



void buildTree(BinarySearchTree<int>* myBst, vector<int> & vectorA){

  while(true){

    cout << "Please enter a file name that contains distinct integers: " << endl;
    string inFile;
    cin >> inFile;
    int number;
    fstream myFile(inFile);
    if(myFile.is_open() ){
      while(myFile >> number){
        vectorA.push_back(number);
      }
      myFile.close();
      break;
    }
    else {
      cout << "File not found, try again: " << endl;
    }
  }// End While

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  for (int i = 0; i < vectorA.size(); i++){
    cout << "inserting: " << vectorA[i] << endl;
    myBst->insert(vectorA[i]);
  }

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  cout << "Bst size is: " << myBst->getSize() << endl;
  cout << "Bst height is: " << myBst->Treeheight() << endl;
  cout << "CPU time to build tree: " << time_span.count() << " seconds." << endl;

} // End buildTree
