#include <iostream>
using namespace std;


void input(int& hours, int& mins);

void convert(int& hours, int& mins, char& ampm);

void output(int& hours, int& mins, char& ampm);

int main() {

	int hours = 0, mins = 0;
	char ampm = 'A';
	bool repeat = true;
	char again;

	do 
	{
	input(hours, mins);
	convert(hours, mins, ampm);
	output(hours, mins, ampm);

	cout << endl << "Enter Y to run again, any other key to exit: ";
	cin >> again;

	} while (again == 'y' || again == 'Y');

	system("pause");
}

void input(int& hours, int& mins) {
	
	cout << "Enter your time in hours: ";
	cin >> hours;
	cout << "Enter your time in mins: ";
	cin >> mins;
		
}

void convert(int& hours, int& mins, char& ampm) {
	do
	{
	
	if (hours >= 12) {
		hours = hours - 12;
		ampm = 'p';
	}
	else if (hours == 12)
	{
		ampm = 'p';
	}
	else
	{
		ampm = 'a';
	}

	} while (hours <= 24);
}

void output(int& hours, int& mins, char& ampm) {

	cout << "Your time in 12 hour notation is " << hours << ":" << mins << ampm;
	

}

