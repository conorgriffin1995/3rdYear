#include "ListPhone.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	ListPhone l1;

	l1.insert(1, "Sarah");
	l1.insert(2, "Eoin");
	l1.insert(3, "Mark");

	l1.display();

	l1.deleteMostRecent();

	l1.display();

	l1.getContact(2);

	l1.insert(3, "Tom");

	l1.display();

	ListPhone l2(l1);

	l2.display();


	system("pause");
	return 0;

}