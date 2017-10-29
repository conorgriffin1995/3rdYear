#include "HashTable.h"
#include <iostream>

// Code Reference
// http://pumpkinprogrammer.com/2014/06/21/c-tutorial-intro-to-hash-tables/
// https://www.youtube.com/watch?v=MfhjkfocRR0&list=PLTxllHdfUq4f7-uHOpxXnBUbsuLiI9pmb

using namespace std;

HashTable::HashTable(int s) {
	size = s;
	hashTArray = new BucketNode *[s];
	count = 0;
	//Loop to set all values in Array to NULL
	for (int i = 0; i < size; i++) {
		hashTArray[i] = NULL;
	}
}

int HashTable::hash(int key) {
	int value = key % size; // HASH VALUE, REMAINDER = INDEX VALUE
	return value;
}

void HashTable::insertStudent(int id) {
	int index = hash(id);
	BucketNode* h1 = new BucketNode(id);

	h1->next = hashTArray[index];
	hashTArray[index] = h1;
	cout << "Student ID added : " << id << endl;
	count++;
}

bool HashTable::findStudent(int id) {
	int index = hash(id);
	BucketNode *tempptr = hashTArray[index];

	while (tempptr != NULL) {
		if (tempptr->studentNum == id) {
			cout << "Student ID: " << id << " found!" << endl;
			return true;
		}
		tempptr = tempptr->next;
	}
	cout << "Student ID doesn't exist!" << endl;
	return false;
}

void HashTable::display() {
	if (size == 0) {
		cout << "Table is empty!";
		return;
	}
	else {
		BucketNode *tempptr = hashTArray[size];
		while (tempptr != NULL) {
			count++;
			if (count >= size) {
				break;
			}
			else {
				cout << "Student ID: " << tempptr->studentNum << endl;
				tempptr = tempptr->next;
			}
		}

	}
	cout << endl;
}