#include <cassert>
#include "stack.h" 

stack::stack()
{
  // initialize to empty
  _top = NULL;
  _size = 0; 
}

stack::~stack()
{
  while (not empty())
    pop();
  // destroy current
}

stack & stack::operator=(const stack & rhs)
{
  if (this != &rhs) {
    // destroy current, copy rhs
  }
  return *this;
}

stack::stack(const stack & orig)
{
	_size = orig._size;
  node * orig_curr_node = orig._top;
  _top = new node;
  node * curr_node = _top;


  while (orig_curr_node != NULL) {

    // curr_node = new node; 
    curr_node -> data = orig_curr_node -> data;
    curr_node -> next = new node;
    curr_node = curr_node -> next;
    orig_curr_node = orig_curr_node -> next;
  }

  // copy original
}

void stack::push(const stack_element & item)
{
	_size ++;
  node * new_node = new node;
  new_node -> data = item;
  new_node -> next = _top;
  _top = new_node;
  // finish
}


void stack::pop()
{
  assert(not empty());
  node * temp = _top;
  _top = _top -> next;
  delete temp;
  _size --;
  // finish
}

stack_element stack::top() const
{
  assert(not empty());
  // delete this:
  return (_top->data);
  // finish
  
}

bool stack::empty() const
{
  // delete this:
  return (_top == NULL);
  // finish
  
}

size_t stack::size() const
{
	return _size;
}


