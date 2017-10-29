#include "Percent.h"
#include <iostream>
using namespace std;

Percent::Percent(int i) {
	value = i;
}

const Percent operator+(const Percent& first, const Percent& second) {
	Percent temp(first.value + second.value);
	return temp;
}

const Percent operator*(const Percent& first, const Percent& second) {
	Percent temp(first.value * second.value);
	temp = temp.value / 100;
	return temp;	
}

const Percent operator-(const Percent& first, const Percent& second) {
	Percent temp(first.value - second.value);
	return temp;
}

bool operator==(const Percent& first, const Percent& second) {
	return first.value == second.value;
}

bool operator<(const Percent& first, const Percent& second) {
	if (first.value < second.value) {
		return true;
	}
	else {
		return false;
	}
}

istream& operator >> (istream& inputStream, Percent& aPercent){
	inputStream >> aPercent.value;
	return inputStream;
}

ostream& operator << (ostream& outputStream, const Percent& aPercent) {
	outputStream << aPercent.value;
	return outputStream;

}