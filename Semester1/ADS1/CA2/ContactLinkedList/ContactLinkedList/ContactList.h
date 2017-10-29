#ifndef CONTACTLIST_H_
#define CONTACTLIST_H_

#include "Contact.h"

class ContactList
{
public:
	ContactList();
	void addToHead(const string&);
	void displayName(string);

private:
	int size;
	Contact* head;
	
};

#endif //CONTACTLIST_H_
