#include <iostream>

typedef int element_type;

class Set{

private:

	size_t _capacity;
	element_type _data[10];
	size_t _size;

public:

	Set(const Set&);
	~Set();
	Set();
	void pop();
	bool empty();
	void push(element_type);
	size_t size();
	void print(std::ostream &);


};