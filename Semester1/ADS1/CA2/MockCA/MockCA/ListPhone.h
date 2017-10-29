#pragma once

#include "Node.h"
#include <string>

class ListPhone {

public:
	ListPhone();

	//The Big Three
	ListPhone(const ListPhone& obj);
	//ListPhone& operator =(const ListPhone& obj);
	//~ListPhone();

	void insert(int, string);
	void deleteMostRecent();
	void display() const;

	int getContact(int);
private:
	Node *head;
};
