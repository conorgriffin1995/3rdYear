#include "StackOfDoubles.h"
#include <iostream>

using namespace std;

StackOfDoubles::StackOfDoubles() {}

//a)
//Push Operation
void StackOfDoubles::push(double value) {
	List.insert(value);
}

//Pop Operation
void StackOfDoubles::pop() {
	List.deleteMostRecent();
}

//Top Operation
double StackOfDoubles::top() {
	return List.displayTop();
}

//b)
ostream& operator << (ostream& str, const StackOfDoubles &stackobj) {
	stackobj.List.displayList();
	return str;
}