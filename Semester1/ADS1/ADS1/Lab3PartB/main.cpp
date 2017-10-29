//  main.cpp
//  Lab3PartB


#include <iostream>
using namespace std;
/*
void InputAndAverage();
void Average5(double theAry[], int arySize);
void AverageN(double a[], int size);
*/
void fillArray(int ary[], int size, char& charsUsed);

const int MAX_CHARS = 100;


int main() {

	//Part 1
	/*
	char again;
	const int SIZE = 5;
	double a[SIZE];
	


	do
	{
	//1
	//InputAndAverage();

	//2
	for (int i = 0; i < SIZE; i++)
	{
	cout << "Enter element number " << i + 1 << endl;
	cin >> a[i];
	}
	Average5(a, SIZE);

	//3
	const int MAX = 200;
	double average[MAX];
	int arraySize;
	cout << "Please enter the size of the array: \n";
	cin >> arraySize;

	while(arraySize > 200)
	{
		"Size must be less than the max of 200! Please re-enter: \n";
		cin >> arraySize;
	}

	for (int i = 0; i < arraySize; i++)
	{
	cout << "Enter element number " << i + 1 << endl;
	cin >> average[i];
	}
	AverageN(average, arraySize);




	cout << endl << "\nEnter Y to run again, any other key to exit: ";
	cin >> again;

	} while (again == 'y' || again == 'Y');
	*/

	//Part 2
	//4
	int size[MAX_CHARS];
	char charsUsed;
	fillArray(size, MAX_CHARS, charsUsed);


	system("pause");
}

//Part 1
/*
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
//Answer to question
//You would declare the size of the array inside of a fuction as the main isnt a function.
*/

//Part 2
void fillArray(int ary[], int size, char& charsUsed)
{
	cout << "Enter up to " << size << " characters.\n"
		<< "Mark the end of the list with a full stop .\n";
	char value = '.';
	int sum = 0;
	int index = 0;
	cin >> value;
	while ((value!='.') && (index < size))
	{
		ary[index] = value;
		index++;
		cin >> value;
	}
	charsUsed = index;
	sum += charsUsed;

	cout << "User entered: " << sum << " characters.";
}
