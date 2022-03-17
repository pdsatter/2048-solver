# 2048-solver
Finds solution to 2048 board in least amount of moves

## Author: pdsatter
## Time of creation: 3/17/2022
## Language used: C++

## Disclaimer-
I am not responsible for the creation of the test.sh file or the argumentmanager.h file. I cannot give away the rights to use those files. I am solely responsible for the following files:
* Functions.cpp / functions.h
* Main.cpp
* Stack.h / Stack.cpp

**These files are allowed to be used, however using these files to cheat on homeworks is not permitted.** 

# Detailed Description of project
## Rules:
* 2048 never moves, and acts as a wall.
* The solution is 13 moves or less.
* No new blocks are added
## Goal:
Solve 2048 board in least moves possible, if impossible output "Impossible". No new blocks are added like the original 2048 game

## Implementation:
A recursive depth first search function is used.  It finds the best solution, max limit is 13 moves to solve a puzzle.  This function calls for shifting the puzzle: up, right, down, and left.  If the board is solved, then it saves the path and saves the number of moves made.  It continues looking for solutions that require LESS moves than the first solution.  This means if the puzzle can be solved in an equal amout of moves by shifting right for the last move vs left for the last move, it will choose right as the last move.  Due to the search having the order: up, right, down, left.

## Checks
* If puzzle is solved: This is checked if there is only 1 number left in the puzzle, excluding 0's and 2048.
* If better solution is available: if a solution is found in k moves, there is no point in searching for a solution >= k.
* If puzzle has passed 12 moves: Problem assumes that a solution will be found in 12 moves.
* If puzzle has repeated: if solution makes move k or more times, where k by k is the size of the puzzle, then the solution could be done in less moves.  If puzzle has a height of k, then it can only merge k-1 times at most.
* If puzzle repeats:  If puzzle moves in a direction, but doesn't merge, then moving in same (or opposite) direction would result in a repeating puzzle.  Example: if puzzle is shifted left, but doesn't merge, then shifting either right or left will result in a board that was already created.
* Is unsolveable
  * Check 1: Checks if there are still numbers that can be combined.  Sorts array and checks if there are 2 numbers that are the same.  If there are 2 numbers that are the same, that means that it COULD be possible to solve it.  However if every number is unique in the puzzle (excluding 0 and 2048), then it is NEVER possible to solve it.
  * Check 2: Checks that rows/ cols can become unique.  A board that looks like figure 1 would be impossible to solve, as it cannot create a unique board. Check 2 waits until at least two moves are made so that the board has a chance to move everything to the sides.  The function will not work as intended if it is checked on move one, due to figure 2 thinking that the rows and cols are the same size.  Figure 3 shows an edge case that is covered in my solution.  It may be possible for a puzzle to BECOME unsolvable, however it can still be possible to solve. (If figure 3 is shifted up, it is unsolvable, however if shfited right it is solvable in 2 moves)
 
 Figure 1:                             Figure 2:                                 Figure 3:
 2 4 2                                 2 0 0                                     2 0 2
 0 0 0                                 0 2 0                                     0 4 0
 0 0 0                                 0 0 0                                     0 0 0

## Possible errors:
* A row/col of 2048's will act as a wall, and won't pass the unsolvable checks.
