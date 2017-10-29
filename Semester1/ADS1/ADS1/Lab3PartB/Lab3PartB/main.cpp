//  main.cpp
//  Lab3PartB


#include <iostream>
using namespace std;

void InputAndAverage();
void Average5(double theAry[], int arySize);
void AverageN(double a[], int size);


int main() {
	char again;
	const int SIZE = 5;
	double a[SIZE];
	const int MAX = 200;

	do
	{
		//1
		//InputAndAverage();

		//2
		/*for (int i = 0; i < SIZE; i++)
		{
		cout << "Enter element number " << i + 1 << endl;
		cin >> a[i];
		}
		Average5(a, SIZE);*/

		//3
		double average[MAX];
		for (int i = 0; i < SIZE; i++)
		{
			cout << "Enter element number " << i + 1 << endl;
			cin >> average[i];
		}
		AverageN(average, SIZE);




		cout << endl << "\nEnter Y to run again, any other key to exit: ";
		cin >> again;

	} while (again == 'y' || again == 'Y');

	system("pause");
}

void InputAndAverage()
{
	const int SIZE = 5;
	double a[SIZE];
	double sum = 0;
	double average = 0;

	for (int i = 0; i < SIZE; i++)
	{
		cout << "Enter element number " << i + 1 << endl;
		cin >> a[i];
		sum = sum + a[i];

	}
	average = sum / SIZE;
	cout << "Average is: " << average;
	if (average > SIZE) {
		cout << "\nSize differs from average by: " << (average - SIZE) << endl;
	}
	else {
		cout << "\nSize differs from average by: " << (SIZE - average) << endl;
	}


}

void Average5(double theAry[], int arySize) {
	double sum = 0;
	double average = 0;
	for (int i = 0; i < arySize; i++) {
		sum += theAry[i];
	}
	average = sum / arySize;
	cout << "Average is: " << average << endl;
}

void AverageN(double a[], int size) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += a[i];
	}
	if (size > 0) {
		cout << "Average:" << (sum / size);
	}
	else {
		cout << "ERROR";
	}
}


