// -*- mode: C++ -*-

#ifndef HASHTABLE
#define HASHTABLE

#include <vector>
#include <cassert>

template<typename K, typename V>
class hashtable {

private:
  struct node {
    K key;
    V value;
    node *next;
    node(const K & key, const V & value, node *next = NULL) :
      key(key), value(value), next(next) {}
  };
  
  size_t (*_hash)(const K &);  // pointer to hash function
  size_t _capacity;
  size_t _size;
  node ** _table;  // an array of node pointers.
  
  void make_table()
  {
    assert(_table == NULL);
    _table = new node*[_capacity];
    for(size_t i=0;i<_capacity;i++)
      _table[i] = NULL;
  }


  // THESE MIGHT BE USED LATER....
  static void delete_all(node * p)
  {
    if (!p) return;
    delete_all(p->next);
    delete p;
  }
  
  static void delete_nodes_in(node **array, size_t capacity)
  {
    for (size_t i=0;i < capacity; i++)
      if (array[i])
	delete_all(array[i]);
  }

  size_t non_empty_slots() const
  {
    size_t count = 0;
    for (size_t i=0;i < _capacity; i++)
      if (_table[i])
	count++;
    return count;
  }

  node * find(const K & key) const
  {

    size_t slot = _hash(key) % _capacity;
    for (node *p = _table[slot]; p ; p = p->next)
      if (p->key == key)
	return p;
    return NULL;
  }

public:
  hashtable(size_t (*hash)(const K &), size_t capacity=31)
  {
    _hash = hash;
    _capacity = capacity;
    _size = 0;
    _table = NULL;
    make_table();
  }
			   
  void set(const K & key, const V & value)
  {
    node *n = find(key);
    if (n) 
      n->value = value;
    else {
      // determine the right slot:
      size_t slot = _hash(key) % _capacity;
      // push a new element on the front of the list
      // at the slot
      _table[slot] = new node(key, value, _table[slot]);
    }
  }
  
  V get(const K & key) const
  {
    node *n = find(key);
    if (!n) 
      throw "Key not found";
    return n->value;
  }


  std::vector<K> keys() const
  {
    // return a vector of all the keys in this hash table
    std::vector<K> allkeys;
    for (size_t i=0;i<_capacity;i++)
      for (node *p = _table[i]; p ; p = p->next)
	allkeys.push_back(p->key);
    return allkeys;
  }
  
  void size()
  {
    // return number of distinct key/value pairs
    return _size;
  }

  bool has_key(const K & key) const
  {
    return find(key) != NULL;
  }
  
};
#endif