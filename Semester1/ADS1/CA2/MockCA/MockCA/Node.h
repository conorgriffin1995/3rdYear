#pragma once
#include <iostream>
#include <string>
using namespace std;

class Node {
	friend class ListPhone;
	friend struct Phone;
public:
	Node(int id, string name);
private:
	struct Phone {
		int id;
		string name;

	};
	Phone p;
	Node *next;
};
typedef Node* nodePtr;