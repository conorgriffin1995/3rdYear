#pragma once
#include <string>
#include <iostream>
using namespace std;

class Node {
	friend class BookList;
	friend struct Book;
public:
	Node();
	Node(string, string);
private:
	struct Book {
		string id;
		string name;
	};
	Book b;
	Node *next;
};
typedef Node* nodeptr;
