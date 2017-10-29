#include "ContactList.h"
using namespace std;

ContactList::ContactList() {
	size = 0;
}

void ContactList::addToHead(const string& name) {

	Contact* newOne = new Contact();

	if (head == 0)
	{
		head = newOne;
	}
	else 
	{
		newOne->next = head;
		head = newOne;
	}
	size++;
	
}

void ContactList::displayName(string name) {
	ListNodePtr tempptr = head;
	while (tempptr != NULL) {
		cout << "Name : " << tempptr->name << endl;
		tempptr = tempptr->next;
	}
}