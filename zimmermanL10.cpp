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

void buildTree(BinarySearchTree<int>* myBst, vector<int> & vectorA, int & n);

int main(){

  BinarySearchTree<int> * myBst = new BinarySearchTree<int>();
  vector <int> vectorA;
  int n = 0;
  // Step 1 2 and 3 inside buildTree function
  buildTree(myBst, vectorA, n);

  // Step 4
  vector <int> vectorB;
  myBst->inOrderTrav(vectorB);

  n = myBst->getSize();



  // This is from when i tried returning a node for KeyOfRank, i think i was close to making it work but not quite
  //BinarySearchTree<int>::BinaryNode * test = new BinarySearchTree<int>::BinaryNode();
  //test = myBst->KeyOfRank(n/2);
  //cout << test->getElement() << endl;

  //Step 5
  int num = myBst->KeyOfRank(n/2);
  cout << "KeyOfRank(n/2) is: " << num << endl;
  if(num == vectorB[(n/2) - 1]){
    cout << "Step 5: Key of rank test successful" << endl;
  }
  else{
    cout << "Step 5: Key of rank test not successful" << endl;
  }

  // Step 6
  int k = myBst->RankOfKey(vectorA[n/2]);
  if(k > 0){
    if(vectorA[n/2] == vectorB[k-1]){
      cout << "step 6: rank of key test successful" << endl;
    }
    else{
      cout << "step 6: rank of key test not successful" << endl;
    }
  }

  high_resolution_clock::time_point t1 = high_resolution_clock::now();
  // Step 7
  for(int i = n/2; i < n; i++){
    myBst->deletee(vectorA[i]);
  }
  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  cout << "step 7: Delete keys from n/2 through n-1, deletion took: " << time_span.count()
  << " seconds" << endl;

  // Step 8
  cout << "step 8: The height is now: " << myBst->Treeheight();
  cout << " and the size is now: " << myBst->getSize() << endl;

  //Step 9
  vector <int> vectorC;
  myBst->inOrderTrav(vectorC);
  bool sorted = true;
  for(int i = 0; i < vectorC.size()-1; i++){
    if(vectorC[i] < vectorC[i+1]){
      sorted = true;
    }
    else{
      sorted = false;
      break;
    }
  }
  if(sorted){
    cout << "Step 9: sort test successful" << endl;
  }
  else{
    cout << "Step 9: sort test not successful" << endl;
  }

  //Step 10 key of rank
  int num2 = myBst->KeyOfRank(n/4);
  if(num2 == vectorC[(n/4) - 1]){
    cout << "Step 10: Key of rank test successful" << endl;
  }
  else{
    cout << "Step 10: Key of rank test not successful" << endl;
  }

  //Step 11 rank of key
  int key = myBst->RankOfKey(vectorA[n/4]);
  if(vectorA[n/4] == vectorC[key-1]){
    cout << "Step 11: Rank of key test successful" << endl;
  }
  else{
    cout << "Step 11: Rank of key test not successful" << endl;
  }

  return 0;
}



void buildTree(BinarySearchTree<int>* myBst, vector<int> & vectorA, int & n){

  while(true){

    cout << "Please enter a file name that contains distinct integers: " << endl;
    string inFile;
    cin >> inFile;
    int number;
    fstream myFile(inFile);
    if(myFile.is_open() ){
      while(myFile >> number){
        n++;
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
    //cout << vectorA[i] << " ";
    myBst->insert(vectorA[i]);
  }
  cout << endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  cout << "Step 3: Bst size is: " << myBst->getSize() << endl;
  cout << "Bst height is: " << myBst->Treeheight() << endl;
  cout << "CPU time to build tree: " << time_span.count() << " seconds." << endl;

} // End buildTree
