//X00120179 Lee Healy

#include <iostream>
using namespace std;

void userInput(int& hour, int& minute);
bool conversion(int& hour, int&minute, char& timeFormat);
void output(int hour, int minute, char timeFormat);

int main() {

	int hour = 0;
	int minute = 0;
	char timeFormat = 'A';
	char end = 'n';
	bool pass;
    
    
	while (end ==  'n') {
        
		input(hour, minute);
		pass = conversion(hour, minute, timeFormat);
        
		if (pass) {
			print(hour, minute, timeFormat);
		}
		else {
			cout << "Time does not correspond.\n";
		}
        
		cout << "End program? (y/n)\n";
		cin >> end;
	}
	system("pause");

}

void userInput(int& hour, int& minute) {

	cout << "Please enter the time as two integers: \n";
	cin >> hour >> minute;

}

bool conversion(int& hour, int& minute, char& timeFormat) {
    
    //If time is A.M.
	if (hour == 0) {
		hour = 12;
		timeFormat = 'A';
		return true;
	}
    
    //If time is P.M.
	else if (hour >= 12 && hour <= 24) {
		hour = hour - 12;
		timeFormat = 'P';
		return true;
	}
    
	else {
		return false;
	}
}

void output(int hour, int minute, char timeFormat) {
    
	cout << "The time is " << hour << ":" << minute << timeFormat <<".M";
}

//3 IFS
//0 FORS