#include <iostream>
#include "StackOfDoubles.h"

using namespace std;

int main() {

	//c)
	StackOfDoubles s1 = StackOfDoubles();

	s1.push(5.5);
	s1.push(2.2);
	s1.push(3.3);

	cout << "Outputting contents of the stack.." << endl;
	cout << s1 << endl;

	StackOfDoubles s2(s1);
	/*s2.push(8.8);
	s2.push(9.9);*/
	//s2.pop();

	cout << s2 << endl;

	

	/*cout << "Deleting top item.." << endl;
	s1.pop();
	cout << endl;

	cout << "Outputting contents of the stack.." << endl;
	cout << s1;

	s1.push(10.1);
	s1.push(7.2);
	s1.push(8.8);

	cout << "Outputting contents of the stack.." << endl;
	cout << s1;

	cout << "Returning top item.." << endl;
	cout << s1.top() << endl;
	cout << endl;

	cout << "Adding contents to the stack.." << endl;
	s1.push(1.1);
	cout << endl;

	cout << "Outputting contents of the stack.." << endl;
	cout << s1;

	cout << "Returning top item.." << endl;
	cout << s1.top() << endl;
	cout << endl;

	cout << "Outputting contents of the stack.." << endl;
	cout << s1;*/

	system("pause");
	return 0;

}