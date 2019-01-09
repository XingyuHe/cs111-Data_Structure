using namespace std;

class sudokuboard{
  
  private:
  	string * board;

  public:
  	sudokuboard(string * input);
    void place(size_t r, size_t c, char n) ;// place numeral n at position (r,c)
    void print() ;// write the board to cout
    char get(size_t r, size_t c) ;// return the numeral at position (r,c)
    void remove(size_t r, size_t c) ;// remove the numeral at position (r,c)
    bool canPlace(size_t r, size_t c, char n) ;// true iff the board would allow 
    // placing n at (r,c)
    bool solved() ;// true iff there are no blank spots on the board
    
};
