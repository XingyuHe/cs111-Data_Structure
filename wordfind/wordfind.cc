/******************************************************************************
*                                                                             *
* wordfine.cc                                                                 *  
* Xingyu He                                                                   *
* Project 1 Wordfind                                                          *
* Jan 30 2018                                                                 *
*                                                                             *
* This program finds the need word in a letter grid and                       *        
* then capitalize them. The grid is a stored in a class. The letter in the    *
* grid has unique row and column number.                                      *
*                                                                             *
******************************************************************************/

#include <wordgrid.h>

using namespace std;

// determine the direction that the start coordinate towards the end
// coordinate. 
void determine_delta_r_c(size_t end, size_t start, int & delta) {

    if (end > start)
        delta = 1;

    if (end < start)
        delta = -1;

    if (end == start)
        delta = 0;
}

// capitalize the word in a grid once the word is found.
void capitalize(string word, wordgrid & grid, size_t start_row, 
                size_t start_col, size_t end_row, size_t end_col) {

    int delta_col;
    int delta_row;
    size_t curr_col;
    size_t curr_row;

    // determine the direction that the start coordinate towards the end 
    // coordinate. delta_col and delta_row would be changed to the 
    // correct value through reference. 
    determine_delta_r_c(end_col, start_col, delta_col);
    determine_delta_r_c(end_row, start_row, delta_row);

    // this for loop find every letter between the end coordate and the start 
    // coordinate and capitalize each. 
    for (size_t i = 0; i < word.length(); i++) {

        // curr_row and curr_col represent the current coordinate, which would
        // be used to find the current character. 
        curr_row = start_row + i * delta_row;
        curr_col = start_col + i * delta_col;

        char curr_char = grid.get(curr_row, curr_col);

        // this if statement checks whether the current character is lower case.
        // all lower case letter is bigger than 96 since a is 97. 
        if (curr_char > 96){

            // curr_char - 32 is the number corresponding to the corresponding 
            // upper case letter. 
            grid.set(curr_row, curr_col, curr_char - 32);
        }
    }
}

// find the rest of the word, meaning find the letters after the first letter. 
void find_rest_of_word(string word, wordgrid & grid, 
                        size_t start_r, size_t start_c, 
                        size_t * end_coordinate) {

    // this array has contains the 8 possible directions that the letter 
    // after the first letter in the word can be in the grid. 
    int directions[8][2] = {{1,1},{1,0},{1,-1},
                            {0,1},{0,-1},
                            {-1,1},{-1,0},{-1,-1}};
    // initialize the value of end_row and end_col to be column and row of the 
    // first letter. Add any changes to column and row would represent the end
    // coordinate.
    size_t end_row = start_r;
    size_t end_col = start_c;

    // this for loop goes through each direction in the directions array.
    for (int direction = 0; direction < 8; direction++) {

        // delta row and delta rol represent the corresponding changes needed 
        // to make on end_row and end_col to achieve certain direction in the 
        // grid.
        int delta_row = directions[direction][0];
        int delta_col = directions[direction][1];

        // this for loop goes through each letter of the word after the first 
        // letter under each direction.
        for (size_t i = 0; i < word.length(); i++) {

            int next_row = (int)end_row + delta_row;
            int next_col = (int)end_col + delta_col;

            // this if statement makes sure that the next coordinate in that 
            // direction is not out of the bound of the grid. 
            if ((next_row >= 0 && (int)grid.size() > next_row) &&
                (next_col >= 0 && (int)grid.size() > next_col)) {

                // this if statement checks if the next letter is the same 
                // as the letter required by the word. If this is the case, 
                // the new end_row and col is the next_row and col.
                if (grid.get((size_t)next_row, (size_t)next_col) == 
                    word[i + 1]) {

                    end_row = (size_t)next_row;
                    end_col = (size_t)next_col;

                    // this if statement check if the end_row and end_col now 
                    // contains the entire word. If the number of letters 
                    // between the start coordinate and the end coordinate 
                    // is the same as the length of the word, return the end
                    // coordinate.
                    if (end_row - start_r == word.length() - 1 || 
                        end_col - start_c == word.length() - 1) {

                        // attach the start row and col so that we know the 
                        // start and the end coordinate pair.
                        end_coordinate[0] = start_r;
                        end_coordinate[1] = start_c;
                        end_coordinate[2] = end_row;
                        end_coordinate[3] = end_col;

                        return;
                    }
                } else {

                    // if the corresponding next letter is not found in the gird
                    // end_row and col return to the start row and col to 
                    // restart.
                    end_row = start_r; end_col = start_c;

                    break;
                }
            } else { 

                end_row = start_r; end_col = start_c;

                break;
            }
        }
    }
}

// main find function, which would return the result of finding words on the 
// grid. It would also distribute the task to helper functions to accomplish
// the goal.
bool find(string word, wordgrid & grid) {

    // this for loop checks each letter in the word whether they are lower
    // case. 
    for (size_t i = 0; i < word.length(); i++){

        if ((char)word[i] > 122 && (char)word[i] < 97){

            cout << "Please input a word in lower case!" << endl;
            return false;
        }
    }

    char first_letter = word[0];
    size_t dimension = grid.size();
    size_t start_row ;
    size_t start_col ;
    // initialize the first value of the array to be dimension + 1 to indicate 
    // that if the array value is not changed, nothing is found. It is 
    // impossible to get more than the dimension .
    size_t end_coordinate[4] = {dimension + 1}; 

    // this for loop goes through each item in the grid to find the first letter
    // of the word. 
    for (size_t r = 0; r < dimension; r++ ) {

        for (size_t c = 0; c < dimension; c++ ) {

            // check if the letter is the same as the first letter of the word. 
            if (grid.get(r,c) == first_letter) {

                start_col = c;
                start_row = r;

                // this if statement checks the length of the word to make sure
                // that find_rest_word doesn't need to be called if not needed. 
                if (word.length() == 1) {
                    
                    capitalize(word, grid, start_row, 
                               start_col, start_row, start_col);        

                    return true;
                } else {

                    // find the rest of the word if the length of the word is 
                    // more than 1.
                    find_rest_of_word(word, grid, r, c, end_coordinate);
                }
            }
        }
    }
    
    // check of the value of the first element in end_coordinate is changed to 
    // tell whether word is found on the grid. 
    if (end_coordinate[0] == dimension + 1) {

        return false;
    } else {

        // capitalize.
        capitalize(word, grid, 
                   end_coordinate[0], end_coordinate[1], 
                   end_coordinate[2], end_coordinate[3]);   

        return true;
    }
}

//------------------------------------------------------------------------
int main() {

    size_t dim = 0;  // size of the word grid
    string word = ""; // word to search for
    bool found = false;  // whether the word is found in the grid.
    string one_row = ""; // dim characters (one row) read from stdin
    string all_rows = ""; // dim x dim characters

    // SETUP
    // cout << "enter the dimension" << endl;
    cin >> dim;  // read the dimension 
    // read each row and append to the string of all rows
    for (size_t r = 0; r < dim ; r++) {

        cin >> one_row;
        all_rows += one_row;
    }

    wordgrid grid(dim, all_rows);  // create the grid from that data
    cin >> word; // read the word

    // SEARCH  (you do)
    found = find(word, grid);
  
    // REPORT
    if (found) {

        cout << "FOUND!" << endl;
        grid.output(cout);
    } else {
    
        cout << "NOT FOUND!" << endl;
    }
}
