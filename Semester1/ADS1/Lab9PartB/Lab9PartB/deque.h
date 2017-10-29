
#pragma once
#include<iostream>

using namespace std;

class deque {
public:
	deque(int s);
	bool isEmpty();
	bool isFull();

	void insertHead(int);
	int removeHead(int &);

	void insertTail(int);
	int removeTail(int&);

	friend ostream& operator<<(ostream & output, const deque & obj);
	
private:
	int cArr[100];
	int size;
	int headIndex;
	int tailIndex;
};
