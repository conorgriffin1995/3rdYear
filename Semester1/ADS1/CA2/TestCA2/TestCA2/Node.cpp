#include <iostream>
#include <string>
#include "Node.h"
using namespace std;
Node::Node() {}

Node::Node(string n, double p) {
	b.name = n;
	b.price = p;
}