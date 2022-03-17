#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "stack.h"
#include "functions.h"

using namespace std;

/*
Use stack:
Add member to stack
Start adding to stack at first 0

If 2 numbers are the same, add them and add 0 to stack

*/




int main(int argc, char* argv[]) {

  ArgumentManager am(argc, argv);

  const string input = am.get("input");
  const string output = am.get("output");
  const string command = am.get("command");
  
  std::ifstream inFile(input);
  std::ifstream commandFile(command);
  std::ofstream outFile(output);

  //std::ifstream inFile("input33.txt");
  //std::ofstream outFile("output33.txt");
  
  std::string line;
  getline(inFile, line);

  int k = stoi(line);
  Stack s;
  int ** arr = new int*[k];
  for (int i=0; i<k; i++) // create 2d array
    arr[i] = new int[k];

  // temp, read inputs
  readInput(arr, inFile, k, s);

  std::string result="";
  int bestRunVal = 13;
  int* bestRun = &bestRunVal;
  bool merged = false;

  findPath(arr, k, result, s, bestRun, 0 , 0);

  if (result.empty()) outFile << 0;
  else outFile << result;
  
  deleteArr(arr, k);

  // end of file
  /*
  commandFile.clear();
  commandFile.seekg(0);

  outFile.flush();
  outFile.close();
  */
  return 0;
}