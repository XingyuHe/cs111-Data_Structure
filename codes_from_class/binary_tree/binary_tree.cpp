#include "binary_tree.h"
using namespace std;

int main(int argc, char const *argv[])
{
	Binary_Search_Tree<int> the_tree;
	the_tree.insert(50);
	the_tree.output(cout);
	return 0;
}