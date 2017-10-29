#include <iostream>
#include "Percent.h"

using namespace std;

int main() {
	Percent p1(40);
	Percent p2(20);
	Percent p3(0);
	
	cout << "Adding.." << endl;
	p3 = p1 + p2;
	cout << "Answer = " << p3 << endl;

	cout << "Subtracting.." << endl;
	p3 = p1 - p2;
	cout << "Answer = " << p3 << endl;

	cout << "Multiplying.." << endl;
	p3 = p1 * p2;
	cout << "Answer = " << p3 << "%" << endl;

	p2 = p2 - 20;
	cout << "Checking less than.." << endl;
	if (p3 < p2) {
		cout << "Yes " << p3 << " is less than " << p2 << endl;
	}
	else {
		cout << "No " << p3 << " is not less than " << p2 << endl;
	}
	
	
	
	system("pause");

}