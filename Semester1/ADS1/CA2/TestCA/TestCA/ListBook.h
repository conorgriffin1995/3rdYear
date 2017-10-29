#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

class ListBook {

public:
	ListBook();
	void insert(string, double);
	void deleteMostRecent();
	void display();
	bool getBook(string name);

	//The Big Three
	ListBook(const ListBook& obj);
	ListBook& operator =(const ListBook& obj);
	~ListBook();
private:
	Node *head;
};
