#include "set.h"
#include <iostream>
using namespace std;


struct node{

private:
	node * next;
	
public:
	int _data;
	node(int data): _data(data) {}
	node();
	void change_data(int input) {
		_data = input;
	}


};

int main(){

	// Set s;
	// s.push(10);
	// Set p = s;
	// p.pop();
	// for (size_t i = 0; i < 100; i++)
	// 	p.push(i);

	// s.print(std::cout);
	// p.print(std::cout);

	node * y = new node(1);
	node tim = *y;
	node & kane = *y;
	tim.change_data(10);
	tim._data = 11;
	kane._data = 19;
	cout << y -> _data << endl;
	cout << kane._data << endl;
	cout << tim._data << endl;

}