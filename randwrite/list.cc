/******************************************************************************
*                                                                             *
* list.cc 	                                                                  *  
* Xingyu He                                                                   *
* Project 4 List                                                              *
* Apr 15 2018                                                                 *
*                                                                             *
* This program constructs a list data structure that is doubly linked.		  *
* The structure use nodes as its underlying component. There are some 		  *
* functions written for this data strcture such as add and remove. 			  *
*                                                                             *
******************************************************************************/


#include <iostream>
#include <cassert>
using namespace std;

// List node constructors provided by Prof. Campbell

// list node constructor 
template <typename T>
list<T>::list_node::list_node() : prev(NULL), next(NULL) {}


// list node constructor when the previous node and the node is provided
template <typename T>
list<T>::list_node::list_node(list_node * p, const T & d, list_node * n):
  prev(p), data(d), next(n)  
{
    p -> next = this;
    n -> prev = this;
}


// List constructors/destructor/assignment also provided.  
// No need to change these.

// list constructor
template <typename T>
list<T>::list() 
{
  _init();
}


// list destructor 
template <typename T>
list<T>::~list()
{
  _destroy();
}


// list copy constructor 
template <typename T>
list<T>::list(const list & orig)
{
  _copy(orig);
}


// list assignment operator
template <typename T> 
list<T> & list<T>::operator=(const list & rhs)
{
  if (this != &rhs) {
    _destroy();
    _copy(rhs);
  }
  return *this;
}

// List method stubs provided.  Here's where you come in. You delete this
// comment and fill in the method bodies.


// Create an empty doubly-linked list with front and rear sentinels,
// current points to rear, and current_index = 0;
template <typename T>
void list<T>::_init()
{
    // create sentinal nodes
    _front = new list_node; 
    _rear = new list_node;

    // connect sentinal nodes
    _front -> next = _rear;
    _rear -> prev = _front;

    _size = 0;
    //set _current to be _rear and current_index to be 0
    _set_current_index(0);
}


// Make a (deep) copy of a list.
template <typename T>
void list<T>::_copy(const list & orig)
{
    _init();

    // iterate through orig's each node and add its value to this list
    for (int i = 0; i < (int)orig.size(); i++)
        add(orig.get(i), i);
}


// Delete all nodes (including the sentinels)
template <typename T>
void list<T>::_destroy()
{
    // delete the first node whenever the list is not empty
    for (; 0 != _size;)
        remove_at(0);
    delete _front; 
    delete _rear;
}


// Insert a new element at a position (k) given by index.
//     If index is non-negative, k is index; otherwise
//     k is size() + index.
template <typename T>
void list<T>::add(const T & item, int index)
{
    // there is no assert statement here because the condition is asserted
    // in _set_current_index
    // convert index to a positive number
    index = index < 0 ? _size + index : index;
    // sets the current pointer to point to the node at index
    _set_current_index(index);

    // create new node 
    list_node * new_node = new list_node(_current -> prev, item, _current);
    new_node = new_node; // compiler give warning if new_node is not used

    // increment current index and size
    _current_index ++;
    _size ++;
}


// Remove an element from this list.  
// index indicates a position k in the manner described in (add).
template <typename T>
void list<T>::remove_at(int index)
{
    // convert the index to a positive number
    index = index < 0 ? _size + index : index;
    // make sure the index is not out of range
    assert(index < (int)_size && index >= 0);
    // set the current point to point to the node at the index
    _set_current_index(index);

    // connect the nodes on both sides of the current
    _current -> prev -> next = _current -> next;
    _current -> next -> prev = _current -> prev;

    // free the momery at _current's loaction
    delete _current;
    _size --;
}


// Let i be the smallest non-negative integer where get(i)==item. 
template <typename T>
void list<T>::remove(const T & item)
{
    // find i such that i is the smallest non-negative integer where 
    // get(i) == item
    size_t remove_index = find(item);

    // make sure that such i exists
    if (remove_index != _size)
        remove_at(remove_index);
}


// return smallest non-negative integer where get(i)==item,
// or size() if no such integer
template <typename T>
size_t list<T>::find(const T & item) const
{
    // go through each node in the list
    // when the data at that node is the same as item, return the index of that 
    // node, else return _size
    for (int i = 0; i < (int)_size; i++)
        if (get(i) == item)
            return i;
    return _size;
}


// obtain the element at a a location index
template <typename T>
T list<T>::get(int index) const
{
    // convert the index to a positive number
    index = index < 0 ? _size + index : index;
    // make sure the index is not out of range
    assert(index < (int)_size && index >= 0);
    // set the current point to point to the node at the index
    _set_current_index(index);
    
    return _current -> data;
}


// index indicates a position k in the manner described in (add).
// return the element at position k.
template <typename T>
size_t list<T>::size() const
{
    return _size;
}


// output the list to ostr using format
// <v0, v1, v2, ..., vn-1>
template <typename T>
void list<T>::output(std::ostream & ostr) const
{
    ostr << "<";
    // print the data in each node with a comma. When it comes to the last node
    // print ">"
    for (int i = 0; i < (int)_size; i++) {
        ostr << get(i);
        if (i != (int)_size - 1)
            ostr << ", ";
    }
    ostr << ">";
}


// set the _current pointer to point to the node at a location index
template <typename T>
void list<T>::_set_current_index(size_t index) const
{
    // make sure the index is not out of range. Because it's size_t, it cannot 
    // be negative. Everywhere this function is used check if index is negative
    assert(index <= _size);

    // if index is less than the midpoint between current_index and _front,
    // iterate to the node from _front -> next
    if (index <= _current_index / 2) {
        _current = _front -> next;
        _current_index = 0;
        for (; _current_index != index; _current_index ++)
            _current = _current -> next;

    // if index is more than the midpoint between current_index and _rear, 
    // iterate to the node from _rear 
    } else if (index >= (_size - _current_index) / 2 ){
        _current = _rear;
        _current_index = _size;
        for (; _current_index != index; _current_index --) 
            _current = _current -> prev;

    // iterate from _current otherwise. The direction of iteration depends on
    // whether index is on the right of the current index or on the left of the 
    // current index. Current index increase or decrease correspondingly. 
    } else {
        if (index < _current_index)
            for (; _current_index != index; _current_index --) 
                _current = _current -> prev;
        else
            for (; _current_index != index; _current_index ++)
                _current = _current -> next;
    }
}
