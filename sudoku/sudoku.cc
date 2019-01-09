#include <iostream>
#include "stack.h"
#include "sudokuboard.h"

using namespace std;

// this function does what needed when backtracking. All parameters are passed
// by reference so that I don't need to return anything. 
void backtrack(sudokuboard & board, size_t * empty_spots, 
              size_t & empty_spots_index, stack & record, size_t & prev_num) {

  // record.top() gives the number put into the last entry. That will be the 
  // number where the next while loop start testing the result. 
  prev_num = record.top();
  record.pop();
  // moving to the last empty spot solved by moving back 2 positions in the 
  // array that contains the row and column numbers for all empty spots. 
  empty_spots_index -= 2; 
  // remove the element at the last solved empty spots. 
  board.remove(empty_spots[empty_spots_index], 
              empty_spots[empty_spots_index + 1]); 
}

int main() {

  // get the input and start a sodukoboard. 
  string example[9];
  for (size_t i = 0; i < 9; i++)

    cin >> example[i];

  sudokuboard board(example);

  // find all the spots that have 
  size_t index = 0;
  // 162 is the maximum numbers of row and column numbers if the entire board
  // is empty.
  size_t empty_spots[162];

  // these two for loops go through each entry on the board. 
  for (size_t r = 0; r < 9; r++)

    for (size_t c = 0; c < 9; c++)

      if (board.get(r,c) == '_') {

        // record the row and column number for the empty spot. 
        empty_spots[index] = r;
        empty_spots[index + 1] = c;
        index += 2;
      }

  // start solving:

  // preparation:
  // Empty_spots is an array that contains the 
  // coordinates of the empty spots in the board (r1,c1,r2,c2,r3,c3 ...)
  // empty_spots_index is a number that represents the index of the current 
  // empty entry the following loop is working on. pre_num represents the 
  // index of the number (1,2,3,4,5,6 .. or 9) that the current loop should 
  // start trying. 
  size_t empty_spots_index = 0;
  // initialize record. 
  stack record;
  // pre_num keeps tracks of the last number succeded in solving the last entry.
  size_t prev_num = 0;
  // This is the numbers that will be tested. 
  char numbers[9] = {'1','2','3','4','5','6','7','8','9'};

  // This loop will continue as long as the board is not solved. This loop
  // represents the process of solving each empty entry on the board. 
  while (!board.solved()) {  
    
    // r and c are row and column numbers of the given empty spot this while 
    // loop is currently working on. 
    size_t r = empty_spots[empty_spots_index];
    size_t c = empty_spots[empty_spots_index + 1];
    // this for loop tests each number for the given entry. 
    for (size_t i = prev_num; i < 9; i++) {

      // If we can place this in a board, we go ahead and do it. 
      if (board.canPlace(r,c, numbers[i])) {

        // things needed to do: place the number, put the number on the record,
        // and advance to the next empty spot by add 2 to the empty_spots_index.
        // The next loop will start testing at 0 beacuse it's a brand new entry. 
        board.place(r,c,numbers[i]);
        record.push(i + 1);
        empty_spots_index += 2;
        prev_num = 0;
        // break from this for loop and another while loop will start to test
        // the next entry.
        break;
      }

      // If all the number is not suited to put on the board, we need to back
      // track. 
      if (i == 8) {

        // backtrack
        backtrack(board,empty_spots,empty_spots_index,record, prev_num);
          // if number that is going to start testing for the last empty spot is 
          // is 9, we need to backtrack again until the number that the last 
          // empty spot is going to test is not 9. 
          while (prev_num == 9) {

            // backtrack
            backtrack(board,empty_spots,empty_spots_index,record, prev_num);
          }
        // Break the for loop to start get another while loop to start solving
        // the last empty spot. 
        break;
      }
    }
  }

  // print the board when solved. 
  board.print();
}