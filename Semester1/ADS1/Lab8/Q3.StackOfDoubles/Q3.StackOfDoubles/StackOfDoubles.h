#include <iostream>
#include "ListOfDoubles.h"

using namespace std;

class StackOfDoubles {

public:
	
	StackOfDoubles();

	//The Big Three
	StackOfDoubles(const StackOfDoubles &obj);
	//const StackOfDoubles& operator =(const StackOfDoubles& obj);
	~StackOfDoubles();

	friend ostream& operator <<(ostream& str, const StackOfDoubles &stackobj);

	void push(double);
	void pop();
	double top();

private:
	ListOfDoubles List;
};
