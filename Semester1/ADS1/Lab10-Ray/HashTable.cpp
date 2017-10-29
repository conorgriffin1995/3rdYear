// Ruizhe Ji - X00119201

#include<iostream>
#include"HashTable.h";

using namespace std;

HashTable::HashTable(int size)
{
	arraySize = size;
	hashTableArray = new BucketNode *[size];

	for (int i = 0; i < arraySize; i++) {
		hashTableArray[i] = NULL;
	}
}

int HashTable::hash(int key)
{
	int value = key % arraySize;
	return value;
}

void HashTable::insertStudentId(int id)
{
	int key = hash(id);
	BucketNode* n1 = new BucketNode(id);

	n1->next = hashTableArray[key];
	hashTableArray[key] = n1;
	cout << "Student ID added: " << id << endl;
}

bool HashTable::findStudent(int id)
{
	int key = hash(id);
	BucketNode *tempPtr = hashTableArray[key];

	while (tempPtr != NULL) {
		if (tempPtr->studentNo == id) {
			cout << "Student ID: " << id << " Found!" << endl;
			return true;
		}
		tempPtr = tempPtr->next;
	}
	cout << "Student ID doesn't exist!" << endl;
	return false;
}
