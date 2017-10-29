#pragma once
#include "Node.h"
#include <string>

using namespace std;

class ListPhone {
public:
	ListPhone();

	void insertAtStart(string, string);
	void insertAtEnd(string, string);

	void display();
	void displayTop();

	void deleteStart();
	void deleteEnd();
	void deletePosition(int pos);

	bool getPhone(string);

	////The Big Three
	ListPhone(const ListPhone& list);
	~ListPhone();
	ListPhone& operator =(const ListPhone& list);

private:
	Node *head;
};