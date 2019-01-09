/************************************************************************
    File:        sequence.cc
    Author:      Xingyu He
    Date:        Feb 11 2018
    Assignment:  Project 2

    Implementation of a simple array-based sequence class.

************************************************************************/
#include <iostream>
#include <cassert>
#include "sequence.h"

using namespace std;

/*** Constructor ***/
sequence::sequence()
{
  // Initializes this sequence with 0 elements

  _size = 0;
}

/*** const member functions ***/

  
size_t sequence::size() const
{
  // return the number of elements in this sequence

  return _size;
}


bool sequence::empty() const
{
  // return true if this sequence has no elements, false otherwise.
  
  return (_size == 0);
}


bool sequence::full() const
{
  // return true if this sequence has _capacity elements, false otherwise.

  return _size == _capacity;
}


void sequence::print() const
{
  // Produce output with cout: a single open square bracket, the elements
  // of the sequence, separated by commas and spaces, followed by a single
  // close square bracket. 

  cout << "[";

  for (size_t i = 0; i < _size; i++) {

    cout << _data[i];

    // print a comma befind each element if that element is not the last one.
    if (i != _size - 1)

      cout << ", ";
  }

  cout << "]";
}


int sequence::get(size_t position) const
{
  // Precondition:  position < size()
  // Return the element at the given position.

  // make sure index is not out of bound.
  assert (position < _size);
  return _data[position];
}


size_t sequence::getLongestRun() const
{
  // Determine the length of the longest run of two or more identical adjacent
  // elements of this sequence.  Return the smallest starting position of a
  // run with this length.  If no such run occurs, return size().
  // (This method may use auxiliary stand-alone functions, but, again, you
  // cannot change this  file.  This means that you cannot define auxiliary
  // methods.)

  size_t start_longest_index = 0;
  size_t start_index = 0;
  size_t curr_index = 0;
  size_t length = 0;

  // here is the overview of how I accomplish finding the longest run number.
  // Step 1: this for loop goes through each element in data. 
  // Step 6: this for loop will pick up what the second for loop leave behind 
  // and continue to check the rest of the array. Step 1 to 5 is repeated. 
  // These for loops are designed so that in the worst case, where there is 
  // is no run, the function only goes through the array once. 
  for (; curr_index < _size; curr_index++)
    
    // Step 2: if the same element is spotted behind the current element,
    // we mark the current element as the start element.
    if (_data[curr_index] == _data[curr_index + 1]) {
        
        start_index = curr_index;
        // Step 3: the next element is marked as the current element. 
        curr_index ++;
        
        // Step 4: this for loop check if every element after the start_index is 
        // the same. 
        for (; _data[curr_index] == _data[curr_index + 1]; curr_index++);
          
        
        // Step 5: check if the length of this run is the longest. If it is,
        // this becomes the longest. 
        if (length < curr_index - start_index){
          
          length = curr_index - start_index;
          start_longest_index = start_index;
        }
    }

  if (length > 0)

    return start_longest_index;

  else

    return size();
}
  

/*** non-const member functions ***/


void sequence::add(int item)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != _capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ...VN-1]
  // Adds item to the end of the sequence.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., VN-1, item];
  //   size() == N+1.

  // make sure the capacity of the array is not reached.
  assert (_size != _capacity);

  _data[_size] = item;
  _size ++;

}


void sequence::add(int item, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   N != capacity;
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  //   position <= size()
  // Inserts item at the given position.  All elements with indices at position
  // or greater are shifted to the right.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., item, Vposition,..., VN-1];
  //   size() == N+1

  // make sure index is not out of bound.
  assert (position <= _size);
  // make sure capcity is not reached. 
  assert (_size != _capacity);

  // create a temporary array to store the elements after that position.
  int * temp;
  // the length of the position of determined by the length of the array and 
  // the position.
  temp = new int[_size - position];

  // store elements after the position in temp.
  for (size_t i = position; i < _size; i++)

    temp[i - position] = _data[i]; 

  // add item into the position and expand the size of the array.
  _data[position] = item;
  _size ++;

  // re-eneter the elements after the position from temp.
  for (size_t i = position + 1; i < _size; i++)

    _data[i] = temp[i - position - 1];
}


void sequence::remove(size_t position)
{
  // Preconditions:
  //   The sequence has N elements
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1,  ..., Vposition-1, Vposition, Vposition+1, ... VN-1];
  //   0 <= position and position < N
  // The item at the given position is discarded.  All elements with greater
  // indices are shifted to the left.
  // Postconditions:
  //   The sequence contains elements
  //     [V0, V1, ..., Vposition-1, Vposition+1, ..., VN-1]
  //   size() == N-1.

  // make sure index is not out of bound. position is bigger or equal to 0 
  // becaus it's type size_t.
  assert (position <= _size);

  // move every element to the left. 
  for (size_t i = position; i < _size; i++)

    // move every element to the position one less than their current position.
    _data[i] = _data[i+1];

  _size --;
}


void sequence::replace(int newitem, size_t position)
{
  // Preconditions:
  //   The sequence has N elements.
  //   0 <= position < N
  //   Without loss of generality, the sequence contains elements
  //     [V0, V1, V2, ..., Vposition,... VN-1];
  // Replaces the item at the given position with the given new item.
  // Postcondition:
  //   The sequence contains elements
  //     [V0, V1, V2, ..., newitem,... VN-1];
  //   size() == N  (unchanged)

  // make sure index is not out of bound.
  assert (position <= _size);

  _data[position] = newitem;
}


void sequence::clear()
{
  // Remove all elements from the sequence.
  // Postcondition:
  //   size() == 0

  _size = 0;
}
