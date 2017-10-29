#pragma once

#include <iostream>

using namespace std;

class DoubleStackNode {
	friend class StackOfDoubles;
public:
	DoubleStackNode();
private:
	double value;
	DoubleStackNode *next;
};
typedef DoubleStackNode* StackNodePtr;
