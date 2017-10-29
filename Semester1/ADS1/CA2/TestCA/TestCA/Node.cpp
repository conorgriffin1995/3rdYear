
#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

Node::Node() { }

Node::Node(string name, double price) {
	b.name = name;
	b.price = price;
	next = NULL;
}