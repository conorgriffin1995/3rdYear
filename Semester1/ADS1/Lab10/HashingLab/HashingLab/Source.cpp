#include "HashTable.h"
#include <iostream>

using namespace std;

int main() {
	// Creating a hash table with size of 10.
	HashTable h1(10);

	// Inserting student ID's onto hash table.
	h1.insertStudent(111602);
	h1.insertStudent(120179);
	h1.insertStudent(121887);
	h1.insertStudent(112445);
	h1.insertStudent(223447);
	h1.insertStudent(225668);
	h1.insertStudent(778900);
	h1.insertStudent(554321);
	h1.insertStudent(443215);
	h1.insertStudent(778554);

	h1.display();

	// Find a student ID on the hash table.
	cout << "Searching for student..." << endl;
	h1.findStudent(120179);

	cout << endl;

	// Find a student ID that doesn't exist.
	cout << "Searching for student..." << endl;
	h1.findStudent(111111);

	cout << endl << endl;

	system("pause");
	return 0;
}