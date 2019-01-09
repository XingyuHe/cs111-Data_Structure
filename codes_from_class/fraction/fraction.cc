#include "fraction.h"
#include <iostresm>

using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

void abs(int * a, int * b){
	if (* a < 0)
		* a = -1 * (* a);

	if (* b < 0)
		* b = -1 * (* b);
}

Fraction::Fraction(){

	num = 0 ;
	denom = 1;
	_reduce();
}

Fraction::Fraction(int n, int d){

	num = n;
	denom = d;

}

void Fraction::_reduce(){

	int sign = 1;
	if (num * denom < 0)
		sign = -1;	

	int * num_pointer = new int;
	num_pointer = & num;

	abs(num_pointer, & denom);

	int factor = gcd(num, denom);
	num /= factor;
	denom /= factor;

	num *= sign;

}

void Fraction::print(){


	std::cout << num << denom << std::endl;


}