#include <iostream>
typedef size_t stack_element;

class stack {

  private:
    void init(); // constructor
    void copy(const stack &); // copy every thing to from the stack 
    void destroy(); // destroy the stack

    struct node {
      stack_element data; // the data stored in the current node. 
      node * next; // a node pointer pointing to the next node. 
    };

    node * _top; // a pointer to the last node added to the structure. 

  public:
    stack();  // no-arg constructor
    stack(const stack &);  // copy constructor
    ~stack();  // destructor
    stack & operator=(const stack &); // assignment operator
    void push(const stack_element &); // add new element into stack
    void pop(); // delete the last element put on the stack
    stack_element top() const; // return the last element put on the stack
    bool empty() const; // indicate whether the stack is empty
    void print(); // print all the elements in the stack 

};
