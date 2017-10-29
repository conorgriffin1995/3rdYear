#include "ListPhone.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	//ListPhone l1;

	//l1.insertAtStart("1", "Tom");
	//l1.insertAtStart("2", "Mark");
	//l1.insertAtStart("3", "John");
	//l1.insertAtStart("4", "Sam");

	//l1.display();
	//l1.displayTop();
	//cout << endl;
	//l1.getPhone("Mark");
	//cout << endl;
	/*l1.deletePosition(2);
	l1.deleteStart();*/
	//l1.display();

	ListPhone l2;

	l2.insertAtEnd("1", "Peter");
	l2.insertAtEnd("2", "Conor");
	l2.insertAtEnd("3", "Lee");
	l2.insertAtEnd("4", "James");

	l2.display();
	l2.deleteEnd();

	l2.display();
	//l2.getPhone("Lee");

	l2.displayTop();
	l2.display();
	
	l2.deletePosition(0);
	l2.display();

	ListPhone l3(l2);
	l3.display();

	ListPhone l4;
	l4 = l2;
	l4.display();


	system("pause");
	return 0;
}