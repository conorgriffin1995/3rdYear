#include <iostream>
#include <string>
#include "ListOfEmployees.h"

using namespace std;

int main() {

	ListOfEmployees e1;
	e1.insert("Tom", 55000.75);
	e1.insert("Dan", 47000.25);
	e1.insert("Mark", 76000.85);
	e1.insert("James", 99000.05);
	e1.insert("Lee", 85000.15);

	cout << e1 << endl;

	ListOfEmployees e2(e1);
	cout << e2 << endl;

	ListOfEmployees e3 = e2;
	cout << e3 << endl;

	e1.~ListOfEmployees();
	e2.~ListOfEmployees();
	e3.~ListOfEmployees();

	cout << e1 << endl;
	cout << e2 << endl;
	cout << e3 << endl;

	/*e1.deleteMostRecent();
	e1.display();
	e1.getSalary("Mark");
	e1.display();*/

	system("pause");
	return 0;
}