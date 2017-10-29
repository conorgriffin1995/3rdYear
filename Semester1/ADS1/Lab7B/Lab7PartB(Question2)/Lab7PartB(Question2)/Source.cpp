#include <iostream> //cout
#include <list>		
#include <queue>	//priority_queue
#include <vector>

using namespace std;

class mycomparison {
	bool reverse;
public:
	mycomparison(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const double& lhs, const double& rhs) const
	{
		if (reverse) return (lhs>rhs);
		else return (lhs<rhs);
	}
};

int main() {
	//Using STL to implement a queue of doubles
	/*
	list<double> list1;

	double value1 = 10.5;
	double value2 = 3.3;
	double value3 = 7.2;
	double value4 = 8.6;
	double value5 = 12.9;
	list1.push_back(value1);
	list1.push_back(value2);
	list1.push_back(value3);
	list1.push_back(value4);
	list1.push_back(value5);

	
	list<double>::iterator iter = list1.begin();
	cout << "List values: " << endl;
	//loop as long there are elements in the list.
	while (iter != list1.end()) {
		cout << *iter << ' ';
		iter++;	
	}
	cout << endl << endl;

	//Remove the top element
	cout << "Removing front element.. " << endl;
	list1.pop_front();

	cout << "List values: " << endl;
	iter = list1.begin();
	while (iter != list1.end()) {
		cout << *iter << ' ';
		iter++;
	}

	cout << endl << endl;

	//Sort the list
	cout << "Sorting the list.. " << endl;
	list1.sort();

	cout << "List values: " << endl;
	iter = list1.begin();
	while (iter != list1.end()) {
		cout << *iter << ' ';
		iter++;
	}

	cout << endl << endl;

	//Remove the back element
	cout << "Removing from back.. " << endl;
	list1.pop_back();

	cout << "List values: " << endl;
	iter = list1.begin();
	while (iter != list1.end()) {
		cout << *iter << ' ';
		iter++;
	}

	cout << endl << endl;

	list1.push_front(19.7);
	list1.push_front(20.1);
	list1.push_front(25.3);

	if (list1.empty()) {
		cout << "List is empty.." << endl;
	}
	else {
		cout << "List values: " << endl;
		iter = list1.begin();
		while (iter != list1.end()) {
			cout << *iter << ' ';
			iter++;
		}
	}

	cout << endl << endl;
	*/


	//Using STL to implement a priority queue of doubles
	/*
	double mydoubles[] = {2.2,3.5,4.4,7.7};

	priority_queue<double>first;
	priority_queue<double>second(mydoubles, mydoubles+4);
	priority_queue<double, vector<double>>third(mydoubles,mydoubles+4);

	typedef priority_queue<double, vector<double>, mycomparison> mypq_type;

	mypq_type fourth;                       // less-than comparison
	mypq_type fifth(mycomparison(true));	// greater-than comparison
	*/
	system("pause");
}