#pragma once
#include <iostream>
#include <string>
using namespace std;

class Node {
	friend class ListBook;
	friend struct Book;
public:
	Node();
	Node(string name, double price);
private:
	struct Book {
		string name;
		double price;
	};
	Book b;
	Node *next;
};
typedef Node* nodePtr;