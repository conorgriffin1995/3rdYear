#include <iostream>
using namespace std;

int main()
{
	int chocBar;
	int coupons;
	int dollars;

	cout << "Enter amount of money: ";
	cin >> dollars;
	chocBar = dollars;
	coupons = chocBar;

	while (coupons > 7) {
		if (coupons - 7 >= 0) {
			coupons = coupons - 7 + 1;
			chocBar++;
		}
		
	}

	cout << "You can have " << chocBar << " chocolate bars and will have " << coupons << " coupons left over.";
	
	system("pause");
}