// #include <iostream>
// #include <cassert>
// #include "set.h"

// Set::Set(){

// 	_size = 0;
// 	_capacity = 10;
// }

// bool Set::empty(){

// 	return (_size == 0);

// }

// void Set::push(element_type element){

// 	if (_size == _capacity) {

// 		_capacity *= 2;

// 		element_type * bigger_data = new element_type[_capacity];

// 		for (size_t i = 0; i < _size; i++)
// 			bigger_data[i] = _data[i];

// 		delete [] _data;
// 		_data = bigger_data;
// 	}

// 	_data[_size] = element;
// 	_size += 1;

// }

// // copy constructor
// Set::Set(const Set & ori){

	
// 	_size = ori._size;
// 	_capacity = ori._capacity;
// 	_data = new element_type[_capacity];

// 	for (size_t i = 0; i < _size; i++){

// 		_data[i] = ori._data[i];

// 	}

// }

// // delete constructor
// Set::~Set(){

// 	delete [] _data;
// }

// void Set::pop(){

// 	assert (_size != 0);

// 	_size -= 1;
// }

// size_t Set::size(){

// 	return _size;
// }

// void Set::print(std::ostream & ostr){

// 	for (size_t i = 0; i < _size; i++){
// 		ostr << _data[i] << std::endl;
// 	}
// }