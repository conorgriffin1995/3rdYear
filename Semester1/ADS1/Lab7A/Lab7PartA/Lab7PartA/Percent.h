#include <iostream>
using namespace std;
class Percent
{
	friend const Percent operator+(const Percent&, const Percent&);
	friend const Percent operator*(const Percent&, const Percent&);
	friend const Percent operator-(const Percent&, const Percent&);
public:
	Percent(int = 0);

	friend bool operator==(const Percent& first, const Percent& second);
	friend bool operator<(const Percent& first, const Percent& second);
	friend istream& operator >> (istream& inputStream, Percent& aPercent);
	friend ostream& operator <<(ostream& outputStream, const Percent& aPercent);

	
	//There will be other members and friends.
private:
	int value;
};

