#include "Money.h"
#include <iostream>

int main() {

	Money m1(5,50);
	Money m2(10,90);
	Money m3(0,0);

	cout << "Dividing.." << endl;
	m3 = m1 / 2.5;
	printf("%d.%d", m3);
	cout << endl;

	cout << "Adding.." << endl;
	m3 = m1 + m2;
	printf("%d.%d", m3);
	cout << endl;
	
	cout << "Subtracting.." << endl;
	m3 = m2 - m1;
	printf("%d.%d", m3);
	cout << endl;

	cout << "Subtracting.." << endl;
	m2 = m3 - m1;
	printf("%d.%d", m2);
	cout << endl;

	cout << "Multiplying.." << endl;
	m3 = m1 * 2;
	printf("%d.%d", m3);
	cout << endl;

	Money m4;
	cout << "Enter euros and cents : " << endl;
	cin >> m4;
	cout << m4;
	cout << endl;

	cout << "Checking less than.." << endl;
	if (m3 < m2) {
		cout << "Yes " << m3 << " is less than " << m2 << endl;
	}
	else {
		cout << "No " << m3 << " is not less than " << m2 << endl;
	}

	
	cout << "Checking more than.." << endl;
	if (m3 > m1) {
		cout << "Yes " << m3 << " is more than " << m1 << endl;
	}
	else {
		cout << "No " << m3 << " is not more than " << m1 << endl;
	}

	Money m5(10, 10);
	Money m6(10, 10);
	cout << "Checking equal to.." << endl;
	if (m5 == m6) {
		cout << "Yes " << m5 << " is equal to " << m6 << endl;
	}
	else {
		cout << "No " << m5 << " is equal to €" << m6 << endl;
	}

	cout << "Checking equal to.." << endl;
	if (m3 == m1) {
		cout << "Yes " << m3 << " is equal to " << m1 << endl;
	}
	else {
		cout << "No " << m3 << " is equal to " << m1 << endl;
	}
	system("pause");
}