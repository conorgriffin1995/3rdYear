#pragma once
#include "BucketNode.h"

class HashTable {
public:
	HashTable(int s);
	int hash(int key);
	bool findStudent(int id);

	void insertStudent(int id);
	void display();
private:
	int size;
	BucketNode** hashTArray;
	int count;
};
