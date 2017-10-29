//My first program C++
// Conor Griffin X00111602

#include <iostream>
using namespace std;

int main()
{
/*	
	Question 1

	double metricTon = 35273.92;
	double cerealWeight, metricTonWeight;

	cout << "Hello\n";
	cout << "Enter the weight of cereal in ounces: ";
	cin >> cerealWeight;

	metricTonWeight = cerealWeight / metricTon;

	cout << "Your Cereal Weighs: " << metricTonWeight << " in metric tonnes.\n";
	cout << "You would need " << metricTon / metricTonWeight << " boxes to yield one metric ton of cereal.\n";

	system("pause"); */


	//Question 2

	double amountSweetener;
	double mouseWeight;
	double dieterWeight;
	double sweetenerPerPound;
	double death;
	double const Percentage = 0.001;

	cout << "Hello\n";
	cout << "Enter the weight of mouse: ";
	cin >> mouseWeight;
	cout << "Enter weight of dieter: ";
	cin >> dieterWeight;
	cout << "Enter amount of artificial sweetener needed to kill a mouse: ";
	cin >> amountSweetener;
	sweetenerPerPound = mouseWeight / amountSweetener;
	death = dieterWeight / sweetenerPerPound;

	cout << "You can drink " << death / Percentage << " cans of soda.\n";

	system("pause");

}
