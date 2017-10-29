#include <iostream>
using namespace std;

class Money {
	friend const Money operator+(const Money&, const Money&);
	friend const Money operator*(const Money&, const Money&);
	friend const Money operator-(const Money&, const Money&);

public:
	Money();
	Money(int, int);

	friend const Money operator*(const Money&, int);
	friend const Money operator/(const Money&, double);

	friend bool operator==(const Money&, const Money&);
	friend bool operator<(const Money&, const Money&);
	friend bool operator>(const Money&, const Money&);
	friend istream& operator >> (istream&, Money&);
	friend ostream& operator << (ostream&, const Money&);

private:
	int euro;
	int cent;
};
