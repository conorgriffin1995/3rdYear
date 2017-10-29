#include "Node.h"

using namespace std;

Node::Node(){ }

Node::Node(string ID, string NAME) {
	p.id = ID;
	p.name = NAME;
	next = NULL;
}

