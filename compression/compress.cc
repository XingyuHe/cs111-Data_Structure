/******************************************************************************
 *
 * Name:        Xingyu He
 *
 * Date:        05/01/2018
 *
 * Assignment:	Compression
 *
 * Description: This program has two functions. First is to compresse a file 
 *              using huffman tree. The second functionality is to 
 *              decompress the compressed file.
 *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <cassert>

#include "pq.h"

using namespace std;

// structure for a huffman tree
struct HuffmanTree {
  unsigned char value;
  size_t count;
  HuffmanTree *left;
  HuffmanTree *right;
  // each huffman tree has a value, which is the value of the char
  // stored, the count of that character in the file, and two 
  // children
  HuffmanTree(unsigned char value, size_t count,
	      HuffmanTree *left=NULL, HuffmanTree *right=NULL) :
    value(value), count(count), left(left), right(right) {}
};


// a function that compares the count of the value of the huffman 
// tree. This will be passed as a function pointer into the priority
// queue
int huffman_tree_cmp(HuffmanTree * const & a, HuffmanTree * const & b)
{
  if (a->count == b->count) return 0;
  return a->count < b->count ? -1 : 1;
}


// This function takes a huffman tree and traverses the tree pre-orderly
// This is function is for debugging and printing the tree
void traverse_tree(HuffmanTree * tree) 
{
  if (!tree)
    return;
  cout << "node value " << tree -> value << " node count" <<tree -> count;
  cout << "(  " ; traverse_tree(tree -> left); 
  traverse_tree(tree -> right); cout << "  )";

}


// This function takes bit string less than 8 bits
 // and convert it to a character
unsigned char bits_to_byte(string bitstr) 
{
  unsigned char total = 0;
  // i is the binary digit
  size_t i;
  // p is the number contains at each binary digits 
  int p;

  // at each iteration of the for loop, the decimal number contains at that 
  // specific binary digit is added to the total number of bites
  for (i = 0, p=128; i < 8; i++, p /= 2)
    if (bitstr[i] == '1')
      total += p;    
  return total;
}


// This function takes in a byte and convert it to a bit string
string byte_to_bits(int byte) 
{
  string bits = "00000000";
  size_t num_digit = bits.length();

  // this for loop goes through each digit in the bits string and check 
  // if the byte can is larger than the decimal number that digit can hold
  for (int i = num_digit - 1; i > -1; i--) {

    // if the digit can hold part or all of the byte, convert that part of 
    // of the byte to binary and correspondingly decrease the decimal 
    // representation in byte 
    bits[num_digit - 1 - i] = (pow(2, i) <= byte)? '1' : '0';
    byte -= (pow(2, i) <= byte)? pow(2, i) : 0;
  }
  return bits;
}


// This function read the file to be compressed and figure out its size
void get_counts(size_t * counts, size_t & size, istream & in)
{
  // POST:  all characters read from in.
  //        counts[k] = the number of occurrences of k in the istream.
  //        size is the number of characters read
  
  // reads every single character in a file, counts the frequency of each 
  // letter, and keeps track of the size of the file
  for (int c = in.get(); c != -1; counts[c] += 1, size ++, c = in.get());
}


// make a huffman tree based on the counts given of each letter
HuffmanTree * make_tree(size_t * counts)
{
  priority_queue<HuffmanTree *> queue(huffman_tree_cmp);

  for (size_t i = 0; i < 256; i++)
    if (counts[i] != 0) {

      // make leaves and insert in priority queue
      HuffmanTree * leaf = new HuffmanTree(i, counts[i]);
      queue.add(leaf);
    }

  HuffmanTree * result;
  // this for loop keeps removing two
  // trees, combining and reinserting until queue size
  // is 1
  while (queue.size() != 1) {

    HuffmanTree * first_child = queue.front();
    queue.remove();
    HuffmanTree * second_child = queue.front();
    queue.remove();
    HuffmanTree * alpha = new HuffmanTree(0, first_child -> count +
                                          second_child -> count,
                                          first_child, second_child);
    // the new huffman tree is properly placed because it is a priority queue
    queue.add(alpha);
  } 

  // the root of the huffman tree is the remaining one huffman tree
  result = queue.front();
  return result;
}


// This function makes the path to reach the character in the given huffman tree
void make_codes(HuffmanTree *tree, string *codes, string code="")
{
  // codes is an array of 256 strings, initially empty, and will contain
  // the path of all 256 characters
  // code is the path so far
  // traverse the tree and if at a leaf, store path in codes corresponding to 
  // value otherwise, recursive call left and right, with updates to code.

  if (!tree)
    return;
  if (!tree -> left && !tree -> right)
    codes[tree -> value] = code;

  make_codes(tree -> left, codes, code + "0");
  make_codes(tree -> right, codes, code + "1");
}


// This function outputs the huffman tree using I and L
void write_tree(HuffmanTree * tree, ostream & ostr)
{

  // base case
  if (!tree)
    return;

  // if the node is a leaf, output L and the value at the leaf
  // otherwise, it is an internal node and output I
  (!tree -> left && !tree -> right)? ostr << "L" << tree -> value : ostr << "I";
  
  // traverse the tree recursively
  write_tree(tree -> left, ostr);
  write_tree(tree -> right, ostr);
}


// This helpher function that helps buffer the byte into bits
string read_helper(istream & istr) 
{
  int c = istr.get();

  // make sure that c is not the end of the file
  return (c != -1)? byte_to_bits(c): NULL;
}

HuffmanTree * read_tree(istream & istr)
{
  // get a buffer to start
  string buffer = read_helper(istr);

  // check if buffer represents a leaf node
  // The binary string represents letter L
  if (buffer == "01001100") {
    // if the node is a leaf, the next letter in the code would indicate the 
    // value of the leaf. Assign the value to the huffman tree and return 
    // the tree
    string new_buffer = read_helper(istr);
    int byte = bits_to_byte(new_buffer);
    return new HuffmanTree(byte, 0);
  }

  // check if buffer represents an internal node. 
  // The binary string represents letter I
  if (buffer == "01001001")
    // if it's an internal node, recursively create huffman as this huffman tree
    // 's children
    return new HuffmanTree(0,0, read_tree(istr), read_tree(istr));
  return NULL;
}


// this function decode the path of each character and output the character
void decode(istream & istr, ostream & ostr, HuffmanTree * root, int file_size)
{
  // initialize buffer bits and num_used_bits
  string buffer;
  size_t num_used_bits = 0;

  // this for loop make sures that all the characters are read
  for (int letter_count = 0; letter_count < file_size; letter_count++) {
    // reading a new character requries to start from the root of the huffman
    // tree
    HuffmanTree * tree = root;

    // this for loop iterates until it reaches the leaf
    for (; tree -> left && tree -> right; num_used_bits ++) {
      
      // this if statement makes sure that the buffer is not used up. If so,
      // get new data from the standard input. Since this is a new buffer,
      // number of bits used in the buffer would be 0
      if (num_used_bits == buffer.length()) {
        num_used_bits = 0;
        buffer = read_helper(istr);
      }

      // if the next unread bit is 0, go to the tree's left, else right
      tree = (buffer[num_used_bits] == '0') ? tree -> left : tree -> right;
    }

  // output the value of the leaf
  ostr << tree -> value;
  }
}


// this function write each character in the file using the huffman tree
// and the path for each letter in codes 
void write_compress(ifstream & in, string * codes, ostream & ostr) 
{
  string buffer;
  string code;

  for (int c = in.get(); c != -1;) {
    
    // attach the path of each chacter in the source to the code
    code += codes[c];
    c = in.get();

    // buffer if needed and convert the bit string to byte
    if (code.length() >= 8) {

      buffer = code.substr(0, 8);
      // code would be the remaining value other than the buffer
      code = code.substr(8, code.length());
      ostr << bits_to_byte(buffer);
    }
  }

  // patch the code if needed so that all code will be represented by byte
  if (code.length() != 0) {
    for (size_t i = 0; i < 8 - code.length(); i ++) 
      code += '0';
  }

  ostr << bits_to_byte(code);
}


// this function is the mother function for compressing a file 
void compress(char *filename)
{

  ifstream in(filename);
  // initializes all to zero.
  size_t counts[256] = { }; 
  size_t file_size;

  // read the file first time to get file size and character frequency 
  // distribution
  get_counts(counts, file_size, in);
  in.close();

  // if nothing is in the file, there is no point doing anything further
  if (file_size == 0)
    return;

  // make a huffman tree based on the character frequency distribution 
  HuffmanTree * tree = make_tree(counts);

  string codes[256];
  make_codes(tree, codes);

  cout << file_size ;
  // write the tree using I L
  write_tree(tree, cout);

  // Second pass through the input and write the file in terms of huffman tree
  // code 
  in.open(filename);
  write_compress(in, codes, cout); 
}


// this is the mother function for uncompressing file
void uncompress()
{
  // if there is nothing in the compressed file, don't do anything
  if (cin.peek() == EOF)
    return;

  // extract information about the file from compressed file
  size_t file_size;
  cin >> file_size;
  // read the huffman tree
  HuffmanTree *tree = read_tree(cin);
  // rewrite the file
  decode(cin, cout, tree, file_size);
}


// check the ending of a string is the provided suffix
bool ends_with(const string & str, const string & suffix)
{
  return str.size() >= suffix.size() and 
    str.substr(str.size()-suffix.size()) == suffix;
}


// check if the user enter ./compress or ./uncompress
bool is_compress(const string & command) 
{
  return ends_with(command, "compress") and 
    not ends_with(command, "uncompress");
}


// main function determine whether the shell user wants to compress or 
// uncompress
int main(int argc, char **argv)
{
  // need to use the variable in order to compile
  assert(argc == 2);
  // check if the user wants to compress or uncompress the file
  if (is_compress(argv[0]))
    // the original code left by prof. campell to use for debugging
    if (string(argv[1])=="-b") 
      compress(argv[2]);
    else 
      compress(argv[1]);
  else 
    uncompress();
}
