#pragma once

#include <string>
#include "EmpNode.h"


class ListOfEmployees {

public:
	ListOfEmployees();

	//The Big Three
	ListOfEmployees(const ListOfEmployees &obj);
	ListOfEmployees& operator = (const ListOfEmployees& obj);
	~ListOfEmployees();

	friend ostream& operator << (ostream& output, const ListOfEmployees& obj);

	void insert(string, double);
	void display() const;
	void deleteMostRecent();
	double getSalary(string);

private:
	EmpNode *head;
};
