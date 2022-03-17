#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "stack.h"

// use template for size of array
void readInput(int **arr, std::ifstream& inFile, 
  int k, Stack& s);
 
int** shiftLeft(int **arr, int k, Stack & s, bool& merged);
 
int** shiftRight(int **arr, int k, Stack & s, bool& merged);
 
int** shiftUp(int **arr, int k, Stack & s, bool& merged);
 
int** shiftDown(int **arr, int k, Stack & s, bool& merged);
 
void printArr(int **arr, int k);

void parseLine(int *arr, std::string line);


void findPath(int **arr, int k, std::string& output, Stack& s,
  int* bestRun, int path, int numRec);

void deleteArr(int ** arr, int k);
///////////////////// Implement ///////////////////////////

