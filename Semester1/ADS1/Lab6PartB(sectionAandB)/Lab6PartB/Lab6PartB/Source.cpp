#include <iostream>
#include "ListOfDoubles.h"

using namespace std;

int main() {
	ListOfDoubles* l1 = new ListOfDoubles();

	l1->insert(8.5);	
	l1->insert(9.5);	
	l1->insert(10.5);	
	l1->insert(6.1);	
	l1->insert(7.3);	


	l1->displayList();
	//l1->deleteMostRecent();
	//cout << "Now re-displaying list with most recent deleted.." << endl;
	//l1->displayList();

	l1->deleteDouble(3);
	cout << "Now re-displaying list with position 3 deleted.." << endl; 
	l1->displayList();

	l1->insert(2.2);
	l1->insert(4.8);
	l1->displayList();
	l1->deleteMostRecent();
	cout << "Now re-displaying list with most recent deleted.." << endl;
	l1->displayList();

	l1->deleteDouble(2);
	cout << "Now re-displaying list with position 2 deleted.." << endl;
	l1->displayList();


	system("pause");
}