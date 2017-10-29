#include <iostream>
#include "ListOfDoubles.h"

using namespace std;

class StackOfDoubles {

public:
	//a)
	StackOfDoubles();
	//~StackOfDoubles();
	void push(double);
	void pop();
	double top();

	//b)
	friend ostream& operator <<(ostream& str, const StackOfDoubles &stackobj);
	
private:
	ListOfDoubles List;
};
