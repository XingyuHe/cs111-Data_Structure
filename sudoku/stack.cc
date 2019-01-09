#include <cassert>
#include "stack.h" 
#include <iostream> 
using namespace std;

stack::stack()
{
  // constructor
  init();
}

stack::~stack()
{
  // delete operator
  destroy(); 
}

stack & stack::operator=(const stack & rhs)
{
  // assignment operator
  if (this != &rhs) {
    // destroy current node, copy rhs
    destroy();
    copy(rhs);
  }
  return * this;
}

stack::stack(const stack & orig)
{
  // copy constructor
  copy(orig);
}

void stack::init()
{
  // initialize to empty
  _top = NULL;
}

void stack::copy(const stack & orig) 
{
  init();

  if (!orig.empty()) {
    // _top need to be initialize
    _top = new node;
    // curr nodes are nodes that are currently transferring data
    node * curr_node = _top;

    for (node * orig_curr_node = orig._top; orig_curr_node != NULL; 
        orig_curr_node = orig_curr_node -> next) {
      // transfer data.
      curr_node -> data = orig_curr_node -> data;
      // initialize a new node for the current node 
      curr_node -> next = new node;
      // the curr nodes move to the next node in the linked nodes. 
      curr_node = curr_node -> next;
    }
  }
}

void stack::destroy() {
  // destroy this stack
  while (not empty())
    pop();
    // destroy current node.
}

void stack::push(const stack_element & item)
{
  // declare a new node
  node * new_node = new node;
  // put in the data
  new_node -> data = item;
  // make sure _top point to this new node and next points
  // to the next node. 
  new_node -> next = _top;
  _top = new_node;
}

void stack::pop()
{
  // delete the last entered node. 
  assert(not empty());

  node * temp = _top;
  _top = _top -> next;
  // delete the node temp is pointing. 
  delete temp; 
}

stack_element stack::top() const
{
  assert(not empty());

  return (_top->data);
}

bool stack::empty() const
{
  // tell whether the 
  return (_top == NULL);
  
}

void stack::print()
{  
  // print all data in stack. 
  cout << "<";
  // as long as p is not null, print the data in p and move to 
  // the next node. 
  for (node * p = _top; p != NULL; p = p -> next) {
    cout << p -> data;

    // pint , after every element except the last.
    if (p -> next)
      cout << ", ";
  }
  cout << ">" << endl;
}




