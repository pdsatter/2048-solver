#include "functions.h"

// splits input line into numbers
void parseLine(int *arr, std::string line){
  std::stringstream ss(line); 
  std::string str; 
  int i = 0;
  while (std::getline(ss, str, ' ')) { 
    arr[i] = stoi(str); 
    i++;
  }
  
}

// reads input from file
 
void readInput(int **arr, std::ifstream& inFile, int k, Stack& s)
{
  std::string line, str;
  for (int i=0; i<k; i++){
    std::getline(inFile, line);
    parseLine(arr[i], line);
  }
}

// Prints Array
 
void printArr(int **arr, int k){
  for(int i=0; i<k; i++){
    for (int j=0; j<k; j++){
      std::cout<< arr[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

// creates an array from the combined numbers stack.
// Made for the shift left function
void addToArrayLeft(Stack &s, int arr[], int start, int end){
  for (int i=start; i<=end; i++){
    if (!s.isempty()) {
      if (s.peek() == 0) {
        s.pop();
        i--;
        continue;
      }
      arr[i] = s.pop();
      
    }
    else arr[i] = 0;
  }
}

// creates an array from the combined numbers stack.
// Made for the shift right function
void addToArrayRight(Stack &s, int arr[], int start, int end){
  for (int i=end; i>=start; i--){
    if (!s.isempty()) {
      if (s.peek() == 0) {
        s.pop();
        i++;
        continue;
      }
      arr[i] = s.pop();
      
    }
    else arr[i] = 0;
  }
}

// reveres stack, using 2 other stacks.
// not most effecient function, more efficient function would use 1 new stack, and set s to equal the new stack
void reverseStack(Stack &s){
  Stack temp;
  Stack temp2;
  while(!s.isempty())temp.push(s.pop());
  while(!temp.isempty())temp2.push(temp.pop());
  while(!temp2.isempty()) {
    s.push(temp2.pop());}
}

// prints stack and restores it
void printStack(Stack& s){
  Stack temp;
  while(!s.isempty()){ 
    temp.push(s.pop()); 
  }
  while (!temp.isempty()) s.push(temp.pop());
}

// recursive
// combines numbers if they are same #
// 2048 acts as a wall
// Stack may not be the same size (removes some 0's), this is taken care of in the addToArray(Left/Right) functions.
void combineNums(Stack &s, bool& merged){
  if (s.isempty()){return;}
  if (s.peek() == 0){ // if first num is 0, recurse
    s.pop(); 
    combineNums(s, merged);
    s.push(0); // adds 0 back to stack at end of recursive function
  }
  
  int num = s.pop(); // sets first number to be checked for combining
  while(!s.isempty() && s.peek() == 0) s.pop(); // removes 0 from between numbers. Stack 2 0 0 2 -> 2 2
  if (s.isempty()) { // only 1 value left in stack
    s.push(num); // pushes num back onto stack
    return; // returns since num was the last (nonzero) number in the stack
  }
  // if there's more than 1 num on stack, proceed
  int num2 = s.pop(); // sets num2, will never be 0 due to while loop above

  if (num == num2){ // if nums ==, combine them and make num 2
    num = 2*num;
    num2 = 0;
    merged = true; // sets merged bool
  }
  else { // if nums don't combine, add num2 to stack. Num will be added to stack at end of recurision (line 121)
    s.push(num2);
  }
  combineNums(s, merged); // recurse
  s.push(num); // removed num temporarily, readds to stack here
}


// Shifts the array left
// Steps:
// add all to stack
// combine
// shift

// Shifts a row left
void shiftRowLeft(int arr[], int k, bool& merged){
  // add everything to stack
  Stack s;
  int startpoint = k-1;
  for (int i=k-1; i>=0; i--){
    if (arr[i]!=2048) s.push(arr[i]); // adds everything except 2048 to stack
    
    else if (arr[i] == 2048) // combine if 2048 is found
    {
      combineNums(s, merged);
      addToArrayLeft(s, arr, i+1, startpoint); // after 2048->end
      arr[i] = 2048; // keeps 2048 at same location
      startpoint = i-1; // continues after 2048
      continue;
    }

    // combine at max length
    if (i == 0) 
    {  
      combineNums(s, merged); 
      addToArrayLeft(s, arr, i, startpoint);
    }
    
  }
  
}

// add all to stack
// combine
// shift

// shifts right
void shiftRowRight(int arr[], int k, bool& merged){
  Stack s;
  int startpoint = 0;
  for (int i=0; i<k; i++){
    if (arr[i]!=2048) s.push(arr[i]); // adds to stack if number is not 2048
    
    else if (arr[i] == 2048) // combine if 2048 is found
    {
      reverseStack(s); // reverses stack (for layout reasons, would be possible to change for loop in other function(s) too, but this is convenient)
      combineNums(s, merged);
      addToArrayRight(s, arr, startpoint, i-1); // i-1 is num before 2048
      arr[i] = 2048;  // keeps 2048 at same location
      startpoint = i+1; 
      continue;
    }

    // combine at max length
    if (i == k-1) 
    {
      //reverseStack(s); not needed here
      combineNums(s, merged); 
      addToArrayRight(s, arr, startpoint, i);
    }
    
  }
  
}

// rotates the array 90 degrees right
 
void rotateRight(int **arr, int k){
  
  Stack nums;
  for(int j=0; j<k; j++){ // adds nums to stack, by cols
    for(int i=0; i<k; i++){
      nums.push(arr[i][j]);
    }
  }

  for(int i=k-1; i>=0; i--){ //adds cols back to rows
    for (int j=0; j<k; j++){ // first col is top row
      arr[i][j] = nums.pop();
    }
  }
  
}

// rotates array 90 degrees left
 
void rotateLeft(int **arr, int k){

  Stack nums;
  for(int j=0; j<k; j++){ // adds nums to stack, by cols
    for(int i=0; i<k; i++){ // top to bottom
      nums.push(arr[i][j]);
    }
  }

  for(int i=0; i<k; i++){ //adds cols back to rows
    for (int j=k-1; j>=0; j--){ // first col is last row
      arr[i][j] = nums.pop();
    }
  }
  
}

 
int** shiftLeft(int **arr, int k, Stack& s, bool& merged){
  int **newArr = new int*[k];
  for (int i=0; i<k; i++){ // copies 2d arr
    newArr[i] = new int[k];
    for (int j=0; j<k; j++){
      newArr[i][j] = arr[i][j];
    }
  }
  for (int i=0; i<k; i++){
    shiftRowLeft(newArr[i], k, merged);
  }
  return newArr;
}

 
int** shiftRight(int **arr, int k, Stack& s, bool& merged){
  int **newArr = new int*[k];
  for (int i=0; i<k; i++){
    newArr[i] = new int[k];
    for (int j=0; j<k; j++){
      newArr[i][j] = arr[i][j];
    }
  }
  
  for (int i=0; i<k; i++){
    shiftRowRight(newArr[i], k, merged);
  }
  return newArr;
}

 
int** shiftUp(int **arr, int k, Stack& s, bool& merged){
  int **newArr = new int*[k];
  for (int i=0; i<k; i++){ // copy arr
    newArr[i] = new int[k];
    for (int j=0; j<k; j++){
      newArr[i][j] = arr[i][j];
    }
  }
  rotateLeft(newArr,k); // rotates left so you can shift left

  for (int i=0; i<k; i++){
    shiftRowLeft(newArr[i], k, merged);
  }
  rotateRight(newArr,k); // rotates right to restore
  return newArr;
  
}

 
int** shiftDown(int **arr, int k, Stack& s, bool& merged){
  int **newArr = new int*[k];
  for (int i=0; i<k; i++){ // copy arr
    newArr[i] = new int[k];
    for (int j=0; j<k; j++){
      newArr[i][j] = arr[i][j];
    }
  }
  
  rotateLeft(newArr,k); // rotate left so you can shift right
  for (int i=0; i<k; i++){
    shiftRowRight(newArr[i], k, merged);
  }
  rotateRight(newArr, k); // rotate right to restore
  return newArr;
}

// Deletes 2d Dynamic Array
void deleteArr(int ** arr, int k){
  for (int i=0; i<k; i++){
      delete[] arr[i];
  }
  delete arr;
}

// figures out if puzzle is solved
 
bool solved(int **arr, int k){
  int count = 0;
  for(int i=0; i<k; i++){
    for (int j=0;j<k;j++){
      if (arr[i][j]!=0 && arr[i][j] != 2048) count ++;
      if (count > 1) {return false;}
    }
  }
  return true;
}

// sorts array
// insertion sort
void sort(int *arr, int k){
  // put max values in front
  int max;
  for(int i=0; i<(k*k); i++){
    max = arr[i];
    for (int j=i+1; j<k*k; j++){
      if (arr[j] > max){
        max = arr[j];
        std::swap(arr[j],arr[i]);
      }
    }
  }
}

// checks if there's pairs of nums
bool isUnsolvableCheck1(int** arr, int k)
{
  int* sortedArr = new int[k*k];
  
  for(int i=0; i<k; i++){ // copies arr to sorted arr
    for (int j=0; j<k; j++){
      sortedArr[i*k +j] = arr[i][j];
    }
  }
  
  sort(sortedArr,k);
  for(int i=0; i<(k*k-1); i++){
    if (sortedArr[i] == 0) return true; // no nums to combine
    if (sortedArr[i] == sortedArr[i+1]) return false;
  }
  return false;
}

// Checks if all rows and call cols have same length
// also checks if theres nums next to eachother in arr
// ex: 2 4 2 , all moves together, so cant merge 2's
bool isUnsolvableCheck2(int **arr, int k)
{
  int rows=0, rowsize=0, colsize=0, col=0, num1=0, num2=0;
  int savedSize=0;
  
  for (int i=0;i<k;i++){
    
    if (rowsize!= 0 && savedSize !=0 && savedSize != rowsize){ 
      return false;
    }
    if (rowsize!=0) savedSize=rowsize;
    
    rowsize = 0;
    num1=0, num2=0;
    for (int j=0; j<k; j++){
      if (arr[i][j]!= 0 && arr[i][j] != 2048){
        if (rowsize % 2 == 0) num1 = arr[i][j];
        else num2 = arr[i][j];
        if (num1 == num2) {
          return false;
        } // can merge nums
        rowsize++;
      }
    }
    
  }
  savedSize = 0;
  num1=0;
  num2=0;
  for (int i=0;i<k;i++){

    if (colsize!= 0 && savedSize !=0 && savedSize != colsize){ 
      return false;
    }
    if (colsize!=0) savedSize=colsize;
    colsize=0;
    num1=0, num2=0;
    for (int j=0; j<k; j++){
      if (arr[j][i] != 0 && arr[j][i] != 2048){
        if (colsize % 2 == 0) num1 = arr[j][i];
        else num2 = arr[j][i];
        if (num1 == num2) {
          return false;
        }
        colsize++;
      }
    }
  }
  
  return true;
}


// Checks if game is unsolvable
bool isUnsolvable (int **arr, int k){
  bool result = isUnsolvableCheck1(arr, k);
  if (isUnsolvableCheck1(arr, k) == true) return true;
  
  result = isUnsolvableCheck2(arr, k);
  return isUnsolvableCheck2(arr, k); // last check to do
  
}

////////////// ***************************** /////////////////
/////////// finds shortest path with recursion ////////////
////////////// ***************************** /////////////////

void findPath(int **arr, int k, std::string& output, Stack& s, int* bestRun, int path, int numRec, bool merged, int numRepeats)
{
  if (numRepeats >= k) return; // not most efficient if repeats direction k times
  if (numRec > 12) return; // can't go past 12 recursions
  if (numRec >= *bestRun) return;
  if (solved(arr, k) == true){ // if arr is solved
    
    *bestRun = numRec;
    output="";
    
    Stack copyStack; // used to copy values
    while (!s.isempty()){
      copyStack.push(s.pop());
    }
    
    while (!copyStack.isempty()){ 
      s.push(copyStack.pop()); // adds values back to stack
      output += std::to_string(s.peek()); //adds stack to output
    }
    return;
  }
  bool check1 = isUnsolvableCheck1(arr,k);
  bool check2 = isUnsolvableCheck2(arr,k);

  if (check1){
    output = "Impossible";
    *bestRun = numRec;
    return;
  }
  if (numRec >= 2 && (check2)) {
    if (output.empty()) output = "Impossible";
    return;
  }

  // makes it so it doens't go in same direction more than k-1 times

  // checks to see if it merged
  bool mergedUp = false, mergedRight = false;
  bool mergedLeft = false, mergedDown = false;
  
  if ((path != 1 && path!=3) || merged == true){ // wont move same way twice unless merged on last move
    s.push(1); // up, adds to stack to keep track of path
    merged = false; // resets merged
    
    int ** tmpArrUp = new int*[k];
    tmpArrUp = shiftUp(arr, k, s, merged); // shifts tmp arr
    
    findPath(tmpArrUp, k, output, s, bestRun, 1,
      numRec+1, merged, numRepeats); // recurse
    deleteArr(tmpArrUp, k); // deletes tmp arr to save space
    s.pop(); // removes 1 from stack to keep track of path
    mergedUp = merged; // checks if it was merged when it shifted up or not
  }
  
  if ((path != 2 && path!= 4) || merged == true) { // CHECK ABOVE TO SEE FUNCTIONALITY (LINE 464 - 476)
    s.push(2); // right
    merged = false; // resets merged
    
    int ** tmpArrRight = new int*[k];
    tmpArrRight = new int*[k];

    tmpArrRight = shiftRight(arr, k, s, merged);
    
    findPath(tmpArrRight, k, output, s, bestRun, 2,
      numRec+1, merged, numRepeats); // updates merged 
    
    deleteArr(tmpArrRight, k);
    s.pop();
    mergedRight=merged;
  }
 
  if ((path != 3 && path!=1 ) || merged == true){ // CHECK ABOVE TO SEE FUNCTIONALITY (LINE 464 - 476)
    s.push(3); // down
    merged = false; // resets merged
    
    int ** tmpArrDown = new int*[k];
    tmpArrDown = new int*[k];
    
    tmpArrDown = shiftDown(arr, k, s, merged);
    findPath(tmpArrDown, k, output, s, bestRun, 3, 
      numRec+1, merged, numRepeats);
    
    deleteArr(tmpArrDown, k);
    s.pop();
    mergedDown = merged;
  }
  
  if ((path != 4 && path!=2) || merged == true){ // CHECK ABOVE TO SEE FUNCTIONALITY (LINE 464 - 476)
    s.push(4); // left
    merged = false; // resets merged
    
    int ** tmpArrLeft = new int*[k];
    tmpArrLeft = new int*[k];
    
    tmpArrLeft = shiftLeft(arr, k, s, merged);
    findPath(tmpArrLeft, k, output, s, bestRun, 4,
      numRec+1, merged, numRepeats);
    deleteArr(tmpArrLeft, k);
    s.pop();
    mergedLeft = merged;
  }

}

// helper function
void findPath(int **arr, int k, std::string& output, Stack& s,
  int* bestRun, int path, int numRec)
{
  findPath(arr, k, output, s, bestRun, path,
    numRec, true, 0);
}

