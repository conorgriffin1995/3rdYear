#pragma once

#include "DoubleListNode.h"

class ListOfDoubles {

public:
	ListOfDoubles();
	~ListOfDoubles();
	void insert(double);
	void displayList() const;
	double displayTop();
	double deleteMostRecent();

	double getSize();

private:
	DoubleListNode *head;
	double size;
};
