#include <iostream>
#include "deque.h"

using namespace std;

int main() {
	cout << "Inserting elements to the Front and Back" << endl;
	deque d1(5);
	d1.insertHead(79);
	d1.insertHead(11);
	d1.insertHead(67);
	d1.insertHead(42);
	d1.insertHead(54);
	d1.insertHead(79);
	d1.insertHead(99);
	cout << d1;
	
	int item;
	d1.removeHead(item);

	cout << d1;

	//cout << d1;
	
	/*d1.insertTail(2);
	d1.insertTail(4);
	d1.insertTail(6);
	d1.insertTail(8);
	d1.insertTail(10);*/
	//d1.insertTail(12);
	//d1.insertTail(15);
	
	//cout << d1;

	
	//int item2;
	//d1.removeTail(num);

	//cout << d1;

	system("pause");
	return 0;
}