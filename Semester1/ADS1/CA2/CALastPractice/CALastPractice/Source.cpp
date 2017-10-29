#include "BookList.h"
#include <iostream>

using namespace std;

int main() {
	BookList b1;

	b1.insert("1", "Harry Potter");	//0
	b1.insert("2", "The Road");		//1
	b1.insert("3", "Lone Survivor");//2
	b1.insert("4", "The Chase");	//3

	b1.display();

	//b1.deleteMostRecent();

	b1.display();

	b1.getName("4");

	b1.display();

	b1.deleteFromPosition(2);

	b1.display();

	BookList b2(b1);

	b2.display();

	BookList b3;
	b3 = b1;

	b3.display();

	b3.insert("5", "The Go Go");

	b3.display();

	b3.deleteFromPosition(2);

	cout << b3;


	system("pause");
	return 0;
}