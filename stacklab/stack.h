#include <iostream>

typedef int stack_element;

class stack {
 private:
  struct node {
    stack_element data;
    node * next;
  };

  node * _top;
  size_t _size;
 
 public:
  stack();  // no-arg constructor
  stack(const stack &);  // copy constructor
  ~stack();  // destructor
  stack & operator=(const stack &); // assignment operator
  void push(const stack_element &);
  void pop();
  stack_element top() const;
  bool empty() const;
  size_t size() const; 
};





// class queue
// class queue {
// private:
//   struct node {
//     stack_element data;
//     node * next;
//   };
//   node * _front;
//   node * _rear;
//   size_t size; 

//   ~queue() {destroy();}
//   queue(const queue &) {copy();}
// public:
// 	queue():_front(NULL) _rear(NULL) {}
// 	void copy(const queue &);
// 	void destroy() {
// 		while (not empty())
// 			remove();
// 	}
// 	void add(int input) {

// 		if (_rear == NULL)
// 			_rear = new node;
// 			_rear -> data = input;
// 		else {
// 			_rear -> next = new node;
// 			_rear -> data = input;
// 			_rear = _rear -> next;
// 		}

// 		if (_front == NULL)
// 			_front  = _rear;
// 	}
// 	void remove() {

// 		if (empty()) 
// 			return;

// 		node * p = _front;
// 		delete _front;
// 		_front = p -> next;

// 	}
// 	int front();
// 	bool empty() {
// 		return _front == NULL;
// 	}

// 	void print() {
// 		for (node * p = _front; p != NULL)
// 	}

// }