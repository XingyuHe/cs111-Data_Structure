#include <iostream>
#include <cassert>
#include "sudokuboard.h"

using namespace std;

sudokuboard::sudokuboard(string * input) 
{
	// constructor :the board is now the input. 
	board = input;
}

void sudokuboard::place(size_t r, size_t c, char n) 
{
	// place the n at row r and coloumn c.
	board[r][c] = n;
}

void sudokuboard::print() 
{
	// display the board by row. 
	for (size_t i = 0; i < 9; i++) {

		cout << board[i] << endl;
	}
}
char sudokuboard::get(size_t r, size_t c) 
{
	// return the numeral at position (r,c)
	return board[r][c];
}

void sudokuboard::remove(size_t r, size_t c) 
{
	// remove the numeral at position (r,c)
	board[r][c] = '_';
}

bool sudokuboard::canPlace(size_t r, size_t c, char n) 
{
	// true iff the board would allow placing
	// check if n is bigger than 9 or smaller than 0 or if 
	// the row and column are out of bound. 
	if (n - '0' > 9 || n - '0' < 1 || 
		r > 8 || c > 8 )
		return false; 

	// check if any number in the row is the same as n.
	for (size_t i = 0; i < 9 ; i++)
		if (board[r][i] == n)
			return false;

	// check if any number in the column is the same as n. 
	for (size_t i = 0; i < 9; i++)
		if (board[i][c] == n)
			return false;

	// find the top left corner of the corresponding 3 by 3 block. 
	size_t top_left_entry_r = (r % 3 == 0) ? r : r - r % 3;
	size_t top_left_entry_c = (c % 3 == 0) ? c :c - c % 3;

	// check if any of the number in that 3 by 3 block is the same as n
	for (size_t r = 0; r < 3 ; r++)
		for (size_t c = 0; c < 3; c++)
			if (board[top_left_entry_r + r][top_left_entry_c + c] == n)
				return false;
	
	// if there is no false whatsoever, return true. 
	return true;
} 

bool sudokuboard::solved() 
{
	// check each row and each column if there are still empty spots. 
	for (size_t r = 0; r < 9 ; r++)
		for (size_t c = 0; c < 9; c++)
			if (board[r][c] == '_')
				return false;

	return true;
}
