#pragma once

#include "DoubleListNode.h"

class ListOfDoubles {

public:
	ListOfDoubles();
	~ListOfDoubles();
	void insert(double);
	void displayList();
	void deleteMostRecent();

	void deleteDouble(int pos);

private:
	DoubleListNode *head;
	
};

