/******************************************************************************
*                                                                             *
* list.cc                                                                     *  
* Xingyu He                                                                   *
* Project 4 List                                                              *
* Apr 15 2018                                                                 *
*                                                                             *
* This program constructs a list data structure that is doubly linked.        *
* The structure use nodes as its underlying component. There are some         *
* functions written for this data strcture such as add and remove.            *
*                                                                             *
******************************************************************************/

// list.h
// Alistair Campbell
// Fall 2009
// Spring 2011
// Fall 2011
// Spring 2012
// Fall 2012
// Spring 2013
// Fall 2014
// Revised spring 2015

/*******************************

Assignment:  Implement the data structure described herein.

 *******************************/

#ifndef LIST
#define LIST

#include <iostream>

template <typename T>
class list 
{
 public:

  list();
  // Create an empty doubly-linked list with front and rear sentinels,
  // current points to rear, and current_index = 0;

  ~list();
  // Delete all nodes (including the sentinels)

  list(const list & orig);
  // Make a (deep) copy of a list.
  // current_index and current can be set arbitrarily in the copy

  list & operator=(const list & rhs);
  // Support list assignment, with deep copy.  Similarly, current_index
  // and current are set arbitrarily.

  void add(const T & item, int index);
  // Insert a new element at a position (k) given by index.
  //     If index is non-negative, k is index; otherwise
  //     k is size() + index.
  // PRE:  this list contains <v0, v1, ..., vk, ...>
  //       0 <= k <= size()
  // POST: this list contains <v0, v1, ..., item, vk, ... >
  //       current points to new node containing item.
  //       current_index is k.
  // Guarantees constant time access to either end or vicinity of
  // current_index.  

  void remove_at(int index);
  // Remove an element from this list.  
  // index indicates a position k in the manner described in (add).
  // Pre: 0 <= k < size()
  //      This list contains <v0, v1, ..., vk, v(k+1), ... >
  // Post: This list contains <v0, v1, ..., v(k+1), ... >
  //       current points to v(k+1) (or the rear sentinel)
  // Guarantees constant time access to either end or vicinity of
  // current_index.  

  void remove(const T & item);
  // Let i be the smallest non-negative integer where get(i)==item. 
  // Post: same as for removeAt(i)
  // If no such i exists, no change to the list.

  size_t find(const T & item) const;
  // return smallest non-negative integer where get(i)==item,
  // or size() if no such integer

  // list<size_t> find_all(const list & item) const;

  T get(int index) const;
  // index indicates a position k in the manner described in (add).
  // return the element at position k.
  // Guarantees constant time access to either end or vicinity of
  // current_index.  

  size_t size() const;
  // return the number of elements of the list
  // runs in constant time
  
  void output(std::ostream & ostr) const;
  // output the list to ostr using format
  // <v0, v1, v2, ..., vn-1>

 private:
  struct list_node { // base class for list nodes
  list_node * prev;
  T data;
  list_node * next;
  list_node();
  list_node(list_node* p,list_node* n);  // create node with given prev 
                                      // and next pointers
  list_node(list_node* p, const T & d, list_node* n);  // or all 3.
  };

  void _set_current_index(size_t index) const;  
  // PRE: 0 <= index <= size()
  // POST: (1) current points to the node holding the element at position 
  //       index, or to the rear sentinel.
  //       (2) current_index is index
  // set the _current pointer to point to the node at a location index

  void _init();   // initializer 

  void _copy(const list & orig);   // copy constructor
  
  void _destroy();  // destroy the list

  // data fields:
  size_t _size; // number of data items
  list_node * _front;  // points to front sentinel
  list_node * _rear;   // points to rear sentinel
  mutable list_node* _current;  // points to a node in the list beyond the 
                          // front sentinel
  mutable size_t _current_index;  // corresponds to current.  
                        // 0 <= current_index <= size()
    
};

#include "list.cc"
#endif
