#include "Money.h"
#include <iostream>

Money::Money() {
	euro = 0;
	cent = 0;
}

Money::Money(int e, int c) {
	euro = e;
	cent = c;
}

const Money operator+(const Money& op1, const Money& op2) {
	Money temp(op1.euro + op2.euro, op1.cent + op2.cent);
	cout << "Answer : ";
	return temp;
	
}

const Money operator*(const Money& op1, int i) {
	cout << "Answer : ";
	return Money(op1.euro * i, op1.cent * i);
}

const Money operator*(const Money& op1, const Money& op2) {
	Money temp(op1.euro * op2.euro, op1.cent * op2.cent);
	cout << "Answer : ";
	return temp;
}

const Money operator/(const Money& op1, double i) {
	cout << "Answer : ";
	return Money(op1.euro / i, op1.cent / i);

}

const Money operator-(const Money& op1, const Money& op2) {
	Money temp(op1.euro - op2.euro, op1.cent - op2.cent);
	cout << "Answer : ";
	return temp;
}

bool operator==(const Money& op1, const Money& op2) {
	if (op1.euro == op2.euro, op1.cent == op2.cent) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const Money& op1, const Money& op2) {
	if (op1.euro + op1.cent < op2.euro + op2.cent) {
		return true;
	}
	else {
		return false;
	}
}

bool operator>(const Money& op1, const Money& op2) {
	if (op1.euro + op1.cent > op2.euro + op2.cent) {
		return true;
	}
	else {
		return false;
	}
}

istream& operator >> (istream& input, Money& m) {
	input >> m.euro >> m.cent;
	return input;
}

ostream& operator << (ostream& output, const Money& m) {
	output << m.euro << " Euro and " << m.cent <<  " Cent";
	return output;
}

