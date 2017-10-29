#include "EmpNode.h"

using namespace std;

EmpNode::EmpNode(string name, double salary) {
	emp.name = name;
	emp.salary = salary;
	next = NULL;
}