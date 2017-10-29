#include <iostream>

using namespace std;

//Question
//The following code runs but can cause a serious system error. Identify and explain the error, then add code to fix it.

//Answer
/*From looking at this class we see that a shallow copy is being made through the defauls constructor, this is not sufficient
if one or more of the data members points to dynamically allocated memory.
The contents of an object are copied into another but both still point to the same array causing a possible logic error where multiple things point
to the same data. This can cause a memory leak. 
What we need to do is create a copy constructor creating a deep copy of an object. This will prevent a memory leak.
This is invoked in our functions when we pass by value or return by value and also in the test class when we construct sample2 as a copy of sample. 
*/


class PFArrayD
{
public:
	PFArrayD();
	//Initializes with a capacity of 50.

	PFArrayD(int capacityValue);

	PFArrayD(const PFArrayD& obj);
	//Copy constructor

	void addElement(double element);
	//Precondition: The array is not full.
	//Postcondition: The element has been added.

	bool full() const { return (capacity == used); }
	//Returns true if the array is full, false otherwise.

	int getCapacity() const { return capacity; }
	int getNumberUsed() const { return used; }

	void emptyArray() { used = 0; }
	//Empties the array.

	double& operator[](int index);
	//Read and change access to elements 0 through numberUsed - 1.

	PFArrayD& operator =(const PFArrayD& rightSide);
	//Overload Assignment Operator

	~PFArrayD();
	//Destructor

private:
	double *a; //For an array of doubles
	int capacity; //For the size of the array
	int used; //For the number of array positions currently in use
};

//Initializes with a capacity of 50.
PFArrayD::PFArrayD() :capacity(50), used(0)
{
	a = new double[capacity];
}
PFArrayD::PFArrayD(int size) : capacity(size), used(0)
{
	a = new double[capacity];
}

//Copy Constructor to perform a deep copy
PFArrayD::PFArrayD(const PFArrayD& obj)
	:capacity(obj.getCapacity()), used(obj.getNumberUsed())
{
	a = new double[capacity];
	for (int i = 0; i < used; i++) {
		a[i] = obj.a[i];
	}

}

void PFArrayD::addElement(double element)
{
	if (used >= capacity)
	{
		cout << "Attempt to exceed capacity in PFArrayD.\n";
		exit(0);
	}
	a[used] = element;
	used++;
}
double& PFArrayD::operator[](int index)
{
	if (index >= used)
	{
		cout << "Illegal index in PFArrayD.\n";
		exit(0);
	}
	return a[index];
}

PFArrayD& PFArrayD::operator =(const PFArrayD& rightSide)
{
	if (capacity != rightSide.capacity)
	{
		delete[] a;
		a = new double[rightSide.capacity];
	}
	capacity = rightSide.capacity;
	used = rightSide.used;
	for (int i = 0; i < used; i++)
		a[i] = rightSide.a[i];
	return *this;
}

PFArrayD::~PFArrayD()
{
	delete[] a;
}

void showPFArrayD(PFArrayD parameter)
{
	cout << "The first value is: "
		<< parameter[0] << endl;
}

int main()
{
	cout << "This program tests the class PFArrayD.\n";
	
	PFArrayD sample;

	sample.addElement(5.5);
	sample.addElement(6.6);
	sample.addElement(3.3);

	PFArrayD sample2(sample);

	showPFArrayD(sample2);
	cout << "After call: " << sample2[0] << endl;

	cout << "Sample2" << endl;
	//Test to see if we can display Elements in sample2
	for (int i = 0; i < 3; i++) {
		cout << "Element " << i+1 << ": " << sample2[i] << endl;
	}

	cout << "Sample3" << endl;
	//Test Overload Assignment
	PFArrayD sample3 = sample2;
	//Test to see if we can display Elements in sample3
	for (int i = 0; i < 3; i++) {
		cout << "Element " << i + 1 << ": " << sample3[i] << endl;
	}

	
	system("pause");
	return 0;

}


