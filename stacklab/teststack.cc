#include <iostream>
#include "stack.h"

using namespace std;

void output_stack(stack & st)
{
  stack temp;
  cout << "<";
  while (not st.empty()) {
    cout << st.top();
    temp.push(st.top());
    st.pop();
    if (not st.empty())
      cout << ", ";
  }
  while (not temp.empty()) {
    st.push(temp.top());
    temp.pop();
  }
  cout << ">" << endl;

}

void push_and_output(stack & st, const stack_element & item)
{
  st.push(item);
  output_stack(st);
}

void pop_and_output(stack & st)
{
  st.pop();
  output_stack(st);
}


void hline()
{
  cout << "-----------" << endl;
}

struct node {
  int data;
  node * next;
};

int main()
{
  stack s1;

  s1.push(10);
  cout << s1.size() << endl;
  push_and_output(s1, 1);
  push_and_output(s1, 2);
  push_and_output(s1, 3);
  cout << s1.size() << endl;


  stack s2 = s1;
  cout << s2.size() << endl;
  push_and_output(s2, 1);
  cout << s2.size() << endl;
  push_and_output(s2, 2);
  cout << s2.size() << endl;
  push_and_output(s2, 3);  
  cout << s2.size() << endl;

  node * p = new node;
  p -> data = 12;
  node * q = p;
  delete q;
  cout << p -> data << endl;
  cout << q << endl;
  // hline();
  
  // while (!s1.empty()) {
  //   cout << s1.top() << endl;
  //   pop_and_output(s1);
  // }

  // hline();
  
  // push_and_output(s2, 5);

  // hline();
  // stack s3;
  // push_and_output(s3, 11);
  // push_and_output(s3, 12);
  // push_and_output(s3, 13);

  // hline();

  // output_stack(s2);
  // s2 = s3;
  // output_stack(s3);

  // hline();
  
}
  
