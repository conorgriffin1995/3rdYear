#pragma once

#include <iostream>

using namespace std;

class DoubleListNode {
	friend class ListOfDoubles;
public:
	DoubleListNode();
private:
	double value;
	DoubleListNode *next;
};
typedef DoubleListNode* ListNodePtr;