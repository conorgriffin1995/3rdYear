#include <iostream>
#include <string>
#include "ListBook.h"
using namespace std;
int main() {
	ListBook b1;
	b1.insert("The Road", 22.55);
	b1.insert("The Catcher", 31.20);
	b1.insert("Ho Ho Ho", 45.70);
	b1.display();
	b1.deleteMostRecent();
	b1.display();
	b1.insert("Hello World", 50.10);
	b1.display();
	b1.getBook("The Catcher");

	ListBook b2(b1);
	b2.display();

	ListBook b3 = b2;
	b3.display();

	b1.~ListBook();
	b2.~ListBook();
	b3.~ListBook();

	//Test Destructor lists shouldn't display
	b1.display();
	b2.display();
	b3.display();

	system("pause");
	return 0;
}