#include "Node.h"
#include "string"

Node::Node(int ID, string nameIn) {
	p.id = ID;
	p.name = nameIn;
	next = NULL;
}