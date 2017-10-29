#pragma once

class BucketNode {
	friend class HashTable;
public:
	BucketNode();
	BucketNode(int sNUm);

private:
	int studentNum;
	BucketNode  *next;
};