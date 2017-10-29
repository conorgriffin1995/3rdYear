#pragma once

#include "DoubleListNode.h"

class ListOfDoubles {

public:
	ListOfDoubles();
	
	//The Big Three
	ListOfDoubles(const ListOfDoubles &obj);
	ListOfDoubles& operator =(const ListOfDoubles& obj);
	~ListOfDoubles();

	friend ostream& operator << (ostream& output, const ListOfDoubles& obj);

	void insert(double);
	void displayList() const;
	double displayTop();
	double deleteMostRecent();

	double getSize();

private:
	DoubleListNode *head;
	double size;
};