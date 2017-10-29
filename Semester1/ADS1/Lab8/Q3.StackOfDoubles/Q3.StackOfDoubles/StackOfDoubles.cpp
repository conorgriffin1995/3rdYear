#include "StackOfDoubles.h"
#include <iostream>

using namespace std;

StackOfDoubles::StackOfDoubles() {}


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

//Copy Constructor
StackOfDoubles::StackOfDoubles(const StackOfDoubles &obj) {
	ListOfDoubles List = obj.List;
	//obj.List.displayList();
	
}

//An = assignment operator
//const StackOfDoubles& StackOfDoubles::operator =(const StackOfDoubles& obj) {
//
//	while (obj.List != NULL) {
//		List.deleteMostRecent();
//	}
//	List = obj.List;
//	return(*this);
//}

//Destructor
StackOfDoubles::~StackOfDoubles() {
	List.~ListOfDoubles();
}


ostream& operator << (ostream& str, const StackOfDoubles &stackobj) {
	str << stackobj.List;
	return str;
}