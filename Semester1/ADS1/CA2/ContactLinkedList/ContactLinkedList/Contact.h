#ifndef CONTACT_H_
#define CONTACT_H_

#include <iostream>
#include <string>

using namespace std;

class Contact {

	friend class ContactList;

public:
	Contact();
	

private:
	string name;
	Contact *next;

};
typedef Contact* ListNodePtr;

#endif //CONTACT_H_


