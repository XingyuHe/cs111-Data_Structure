#ifndef HASHTABLE
#define HASHTABLE

#include <vector>
#include <cassert>

template<typename K, typename V>
class hashtable{

private:
	// structure for node
	struct node {

		// attribute of the structure
		K key;
		V value;
		node * next;
		// initializer
		node(const K & key, const V & value, node * next = NULL) : key(key), value(value), next(next) {}
	};

	// attribute for the hashtable
	// function pointer to the function that takes a variable of a T type 
	// this is a hash function I guess
	size_t (* _hash)(const K &);
	
	size_t _size;
	size_t _capacity;
	// this is a pointer that points to a node
	node ** _table;

	void make_table() {
		// make sure that the table has not be initialized 
		assert(_table == NULL);

		// node * is the type of data that is going to be stored in the array
		// table is pointer that points to an array of pointers to node
		// the length of the list is capcacity
		_table = new node * [_capacity];

		// 
		for (size_t i = 0; i < _capacity; i++)
			_table[i] = NULL;
	}

	// static function -- the function can be called without object being instanstiated 
	// can be called using the name of the class

	static void delete_all(node * p) {
		
		// base case: if the pointer does not exist, delete it
		if (!p) return;
		// if the node pointer exist, delete that
		delete_all(p -> next);
		// delete the past one of the linked list and then to the beginning
		delete p;
	}

	static void delete_nodes_in(node ** array, size_t capacity) {

		// goes through every element of the array, each element is a node pointer

		for (size_t i = 0; i < capacity; i++)
			if (array[i])
				// if the element of the array is defined, delete each linked list
				delete_all(array[i]);
	}

	// return the number of slot that has a linked list
	size_t non_empty_slots() const {
		size_t count = 0;
		for (size_t i = 0; i < _capacity; i++)
			if (_table[i])
				count ++;
		return count;
	}


	node * find(const K & key) const {

		// return the slot that is the at the hash key mod _capacity
		size_t slot = _hash(key) % _capacity;

		// iterate the linked list that locates at the hash key position,
		// if found, return that node
		for (node * p = _table[slot]; p; p = p -> next)
			if (p -> key == key)
				return p;
		// if nothing is found, it is not found
		return NULL;
	}

public:

	// initiailizer
	hashtable(size_t (* hash)(const K &), size_t capacity = 31) : 
	_hash(hash), _capacity(capacity), _size(0), _table(NULL) {
		make_table();
	}

	void set(const K & key, const V & value) {
		
		node * n = find(key);

		//  if hash key is found
		if (n)
			// set the value in the node to be the value we wanted
			n -> value = value;
		else {
			size_t slot = _hash(key) % _capacity;
			// put every linked list element as the next of the new element
			_table[slot] = new node(key, value, _table[slot]);
		}
	}

	// get value at the key
	V get(const K & key) const {
		
		// if the key is find
		node * n = find(key);
		// throw an exception if the key node is not found
		if (!n)
			throw "key not found";
		// else return the value of that node 
		return n -> value;
	}

	// get all the keys
	std::vector<K> keys() const {
		std::vector<K> allkeys;
		for (size_t i = 0; i < _capacity; i++)
			for (node * p = _table[i]; p; p = p -> next)
				allkeys.push_back(p -> key);
		return allkeys;
	}

	void size() {
		return _size;
	}

	bool has_key(const K & key) const {
		return find(key) != NULL;
	}


};
#endif