#include <iostream>
#include "ListOfDoubles.h"

using namespace std;

int main() {

	ListOfDoubles l1;

	l1.insert(8.5);
	l1.insert(9.5);
	l1.insert(10.5);
	l1.insert(6.1);
	l1.insert(7.3);

	cout << l1 << endl;

	ListOfDoubles l2(l1);
	cout << l2 << endl;

	ListOfDoubles l3 = l2;
	cout << l3 << endl;

	l1.~ListOfDoubles();
	l2.~ListOfDoubles();
	l3.~ListOfDoubles();

	//Lists will not display so destructor works!!
	l1.displayList();
	l2.displayList();


	/*l1.deleteMostRecent();
	cout << "Now re-displaying list with most recent deleted.." << endl;
	l1.displayList();

	l1.deleteDouble(3);
	cout << "Now re-displaying list with position 3 deleted.." << endl;
	l1.displayList();

	l1.insert(2.2);
	l1.insert(4.8);
	l1.displayList();
	l1.deleteMostRecent();
	cout << "Now re-displaying list with most recent deleted.." << endl;
	l1.displayList();

	l1.deleteDouble(2);
	cout << "Now re-displaying list with position 2 deleted.." << endl;
	l1.displayList();

	l1.~ListOfDoubles();*/


	system("pause");
	return 0;
}