// Ruizhe Ji - X00119201

#pragma once
#include<iostream>

using namespace std;

class BucketNode {

	friend class HashTable;

private:

	int studentNo;
	BucketNode* next;

public:

	BucketNode(int stuNo);

};
