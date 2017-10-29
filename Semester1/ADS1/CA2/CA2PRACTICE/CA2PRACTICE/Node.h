#pragma once
#include <iostream>
#include <string>

using namespace std;

class Node {
	friend class ListPhone;
	friend struct Phone;
public:
	Node();
	Node(string, string);

private:
	struct Phone {
		string id;
		string name;
	};

	Phone p;
	Node *next;
};
typedef Node* nodePtr;