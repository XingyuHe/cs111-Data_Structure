#include "list.h"
#include <iostream>

using namespace std;

int main()
{  
  list lst;
  
  for (int i=0;i<20;i++) {
    lst.add(i, lst.size()/2);
  }
  lst.output(cout);cout << endl;
  // remove all:
  while (lst.size() != 0) {
    lst.remove_at(0);
    lst.output(cout); cout  << endl;
  }
  // and add!
  cout << "add" << endl;
  cout << lst.size() << endl;
  lst.add(55,0);
  cout << "1" << endl;
  lst.output(cout);
  cout << "5" << endl;
  lst.add(66,1); 
  cout << "3" << endl;
  lst.add(77,0);
  cout << "2" << endl;
  lst.output(cout); cout  << endl;

  size_t * a = new size_t;
  *a = 9;
  delete a;
  cout << *a;
  
}
