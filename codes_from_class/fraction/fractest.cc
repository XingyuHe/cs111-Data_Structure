#include <iostream>
#include <typeinfo>
#include "fraction.h"
using namespace std;

int abs(int a){
	if (a < 0)
		a = -1 * a;
	return a;
}

// pair furthest_away(pair points[], size_t N)
// {
// // given an array of N coordinate pairs, return the one that is furthest
// // away from the (0.0, 0.0) origin. Assume a sqrt function exists.

// }

// struct pair { 
// 	float x; 
// 	float y;

// 	pair(int first, int second){

// 		x = first;
// 		y = second;
// 	}


// 	};

// void print_array(int ** a){

// 	for (int i = 0; i < 9; i++)
// 		cout << a[i] << endl;
// 	cout << a << endl;

// }

int main(){

	string a = "abcd";
	string * q = new string;
	
	// int * p = q;

	// Fraction o;
	// Fraction g(7, 9);
	// g.print();

	// // g.print(cout);
	// int A = 10;
	// // int * p = A;
	// int * b = &A;
	// int & B = A;
	// *b = 19;


	// cout << b <<endl; 
	// cout << typeid(b).name() << endl;
	// cout << typeid(*b).name() << endl;
	// cout << typeid(B).name() << endl;
	// cout << typeid(&B).name() << endl;
	// // cout << (*b != &A) << endl;ß
	// cout << (1 == 0) <<endl;
	// cout << B << endl;

	// string a = "abcd";
	// cout << typeid(a.substr(0,1)).name() << endl;
	// cout << typeid(a).name() << endl;
	// string b = "a";
	// cout << typeid(b).name() << endl;

}

