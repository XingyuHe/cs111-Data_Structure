#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;	

int main(int argc, char ** argv) {
	copy_file(argc, argv);
}

void copy_file(int argc, char ** argv) {
	ifstream file;
	file.open(argv[1]);
	ofstream ofile; // output file 
	ofile.open(argv[2]);

	int c; // integer representation of a character 
	
	c = 0;
	while (c != EOF) {
		c = file.get(); // read a character from the file/
		cout << c << endl;
		ofile << (char)c << endl;
	}

	// not read the eof 
	while ((c = file.get()) != EOF) {
		cout << (char)c << '(' << c << ')' << endl;
	}
	
	//close the file when done
	file.close();
}