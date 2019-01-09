#include <iostream>
#include <cstdlib>
#include "hashtable.h"

using namespace std;

size_t hash1(const string & s) {
  size_t p = 1;

  // p the product of all characters of the key
  for (size_t i = 0; i < s.size(); i++)
    p *= s[i];
  return p;
}

string random_string(size_t len) {
  static string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
  return len == 0? "":ALPHABET[rand() % 26] + random_string(len - 1);
}


template<typename K, typename V>
void print_tab(const hashtable<K, V> & tab) {
  std::vector<K> keys = tab.keys();
  for (size_t i = 0; i < keys.size(); i++)
    cout << keys[i] << ":" << tab.get(keys[i]) << endl;
}

int main() {
  hashtable<string , int> the_table(hash1);
  for (size_t i = 0; i < 5; i ++) {
    string rs = random_string(3);
    int ri = rand();
    cout << rs << ":" << ri << endl;
    the_table.set(rs, ri);
  }

  cout << "--------" << endl;

  string key;
  cout << "Get > ";
  cin >> key;
  try {
    cout << the_table.get(key) << endl;
  }
  catch (const char * msg) {
    cerr << "ERROR: " << msg << endl;
    exit(1); 
  }


  print_tab(the_table);

}