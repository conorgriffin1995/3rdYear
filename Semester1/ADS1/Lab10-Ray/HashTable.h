// Ruizhe Ji - X00119201

#pragma once
#include<iostream>
#include"BucketNode.h"

using namespace std;

class HashTable {
private:

	int arraySize;
	BucketNode** hashTableArray;

public:

	HashTable(int size);
	int hash(int key);
	void insertStudentId(int id);
	bool findStudent(int id);

};
