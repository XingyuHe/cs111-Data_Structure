#include <iostream>
#include "stack.h"
#include "sudokuboard.h"

using namespace std;

// First, I will address the parameters of this function. 
// board is the sudokuboard. Empty_spots is an array that contains the 
// coordinates of the empty spots in the board (r1,c1,r2,c2,r3,c3 ...)
// empty_spots_index is a number that represents the index of the current 
// empty entry this function is working on. start_index represents the index
// of the number (1,2,3,4,5,6 .. or 9) that the current function should try. 

// Second, let me address the methodology of solving the sudoku puzzle. 
// I use a recursive method to backtrack. Each recursive call is to find the 
// appropriate number for one empty entry on the board. In each recursive call
// character 1 through 9 is tried to see if one of them can be put on the board.
// If none of them can be put on that entry, a recursive call happens again to
// find another appropriate character for the previous entry. In each recursive 
// call, if an appropriate character number is found, another recursive call 
// happens to solve the next empty entry. 
void solve(sudokuboard & board, size_t empty_spots[], 
                  size_t empty_spots_index, size_t  start_index = 0) {
  cout << "top of solve" << endl;
  size_t drew = empty_spots_index;
  cout << drew << endl;
  // here are the possible numbers put into the empty entry
  char numbers[9] = {'1','2','3','4','5','6','7','8','9'};

  // r and c is the row and column number for the current empty entry this 
  // function is working on. 
  cout << "access r and c" << endl;
  size_t r = empty_spots[empty_spots_index];
  size_t c = empty_spots[empty_spots_index + 1];
  // pre_row and pre_col are the row and column numbers for the previous 
  // entry that is solved before the current empty entry. 
  cout << "access pre c and pre r" << endl;
  size_t prev_row = empty_spots[empty_spots_index - 2];
  size_t prev_col = empty_spots[empty_spots_index - 1];

  // this for loop goes through all the possible numbers and tries each one of 
  // them to see if there is an appropriate number. Further, start_index tells
  // the for loop where to start. This is useful for backtracking. If the 
  // previous called has checked 1 to 3 and figured out 3 is an approriate 
  // number of that empty entry and if the next recursive call fails to fit
  // any of the numbers, the next recursive will try to fit 4, 5,6,7,8,9 into
  // the previous empty spot. 
  for (size_t i = start_index; i < 9; i++) {
    cout << "function called again" << endl;

    // check if the number can be placed. 
    if (board.canPlace(r, c, numbers[i])) {
      cout << "place a number!";

      // place the number on the board. 
      cout << numbers[i] << endl;
      board.place(r, c, numbers[i]);

      cout << "solve check" << endl;
      // check if the board is solved. If so, return the board. 
      if (board.solved())
        return;
      // if the board is not solved, go to the next empty spot and 
      cout << "recursive call" << endl;
      cout << numbers[i] << endl;
      board.print();
      cout << "before solved" << endl;
      cout << empty_spots_index << endl;
      cout << empty_spots_index + 2 << endl;
      cout << empty_spots[empty_spots_index + 2] << endl;
      cout << "before solved" << endl;
      size_t temp = empty_spots_index + 2;
      cout << temp << "temp" << endl;
      for (size_t i = 0; i < 116; i++)
        cout << empty_spots[i] << ",";
      cout << endl;
      solve(board, empty_spots, temp);
    }
    // cout << numbers[i];
    if (numbers[i] == '9') {
      backtrack();
    }
  }

  if (start_index == 9){
    backtrack();
  }
  return;
}


int main(){

  string example[9];

  for (size_t i = 0; i < 9; i++)
    cin >> example[i];

  sudokuboard board(example);

  // board.empty();
  cout << board.empty_spots_length();

  // size_t * empty_spots = board.empty();
  // cout << board.empty_spots_length() << endl;


  // size_t empty_spots[162];
  size_t index = 0;
  size_t length = 0;

  size_t empty_spots[162];
  for (size_t r = 0; r < 9; r++)
    for (size_t c = 0; c < 9; c++)
      if (board.get(r,c) == '_') {
        empty_spots[index] = r;
        empty_spots[index + 1] = c;
        index += 2;
        cout << length << endl;
        length += 2;
      }

  // _empty_spots_length = length - 2;

  for (size_t i = 0; i < 116 ; i++)
    cout << empty_spots[i] << ",";

  size_t empty_spots_index = 0;
  // size_t * empty_spots = board.empty();
  if (board.solved())
    board.print();
  else {
    solve(board, empty_spots, empty_spots_index);
    board.print();
  }
  
}