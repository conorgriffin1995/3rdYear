// Ruizhe Ji - X00119201

#include<iostream>
#include"HashTable.h"

using namespace std;

int main() {

	// Creating a hash table with size of 6
	HashTable h1(6);

	// Insert student ID number onto the hash table just created
	h1.insertStudentId(12345);
	h1.insertStudentId(54321);
	h1.insertStudentId(67891);

	// Find a student ID that doesn't exist
	h1.findStudent(11111);

	// Find a student ID on the hash table
	h1.findStudent(12345);

	system("pause");
}
