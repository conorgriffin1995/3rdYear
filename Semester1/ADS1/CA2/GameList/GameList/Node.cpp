#include "Node.h"

Node::Node(){}

Node::Node(string name, string price) {
	g.name = name;
	g.price = price;
	next = NULL;
}

