#include <iostream>


class Binary_Search_Tree{

template <typename T>
public:

	void insert(const T & item) {
		_insert(_root, item);
	}
	void add(const T & item);
	void output(ostream & ostr) const {
		_output(ostr, _root);
	}

	Binary_Search_Tree() {
		_size = 0;
		_root = NULL;
	}
private:
	struct node {
		T data;
		node * left;
		node * right;
	}

	size_t _size;
	node * _root;

	static void _insert(node * & tree, const T & item) {
		//we can do this recursively using helper function
		// using at static method because I am setting it as a class method
	}

	static void _output(ostream & ostr, node * tree) {
		// we can do this recursively traverse the tree
	}

	static node * & _find_node(node *& tree, const T & item) {

		if (tree == NULL or tree -> data == item)
			return tree;

	}

	static bool prunable(node * tree) {

		return not (tree -> right and tree -> left);
	}

	static void prune(node * & tree) {
		// PRE: prunable
		node * killme = tree;
		if (tree -> left)
			tree = tree -> left;
		if (tree -> right)
			tree = tree -> right;
		delete killme;
	}

	static node * & smallest(node * & tree) {

		// PRE : tree is not equal to NULL
		return (tree -> left) ? smallest(tree -> left) : tree;
	}

	static void _remove(node * & tree, const T & item) {

		node * & the_node = _find_node(tree, item);
		if (! the_node)
			return;
		if (prunable(the_node))
			prune(tree);
		else {
			node * & smallest_right = smallest(the_node->right);
			the_node -> data = smallest_right -> data;
			prune(smallest_right);
		}
	}

	bool remove(const T & item) {

		if (find(item))
			_size--;
		_remove(_root, item);
	} 
};