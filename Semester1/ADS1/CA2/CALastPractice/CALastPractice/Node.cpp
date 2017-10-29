#include "Node.h"

Node::Node(){}

Node::Node(string id, string name) {
	b.id = id;
	b.name = name;
	next = NULL;
}