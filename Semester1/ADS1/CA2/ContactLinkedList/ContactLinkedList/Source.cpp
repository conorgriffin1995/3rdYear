#include "ContactList.h"

using namespace std;

int main() {
	ContactList* cl1 = new ContactList();
	string name;
	while (true) {

		cout << "Enter the name of the contact you would like to add or q to quit." << endl;
		cin >> name;
		if (name == "q") {
			break;	
		}
		else {
			cl1->addToHead(name);
		}
		
	}
	

	cl1->displayName(name);
	system("pause");


}