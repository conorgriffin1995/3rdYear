#pragma once
#include "Node.h"

using namespace std;

class BookList {
public:
	BookList();
	void insert(string, string);
	void display() const;

	void deleteMostRecent();
	int getName(string);
	void deleteFromPosition(int pos);

	//The Big Three
	BookList(const BookList& list);
	BookList& operator=(const BookList& list);
	~BookList();

	friend ostream& operator<<(ostream&, const BookList& obj);
private:
	Node *head;
};
