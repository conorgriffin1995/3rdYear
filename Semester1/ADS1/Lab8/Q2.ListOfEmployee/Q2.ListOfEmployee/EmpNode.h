#pragma once


#include <iostream>
#include <string>

using namespace std;

class EmpNode {
	friend class ListOfEmployees;
	friend struct Employee;

public:
	EmpNode(string name, double salary);
private:
	struct Employee {
		string name;
		double salary;
	};
	Employee emp;
	EmpNode *next;
};
typedef EmpNode* nodePtr;