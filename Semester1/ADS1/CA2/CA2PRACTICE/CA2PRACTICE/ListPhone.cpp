#include "ListPhone.h"


ListPhone::ListPhone() {
	head = NULL;
}
//Inserting at End

void ListPhone::insertAtEnd(string id, string name) {
	Node *newNode = new Node(id, name);
	
	if (head == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		nodePtr temp;
		for (temp = head; temp->next; temp = temp->next);
		temp->next = newNode;
	}

}

//Inserting at start
void ListPhone::insertAtStart(string id, string name) {
	Node *newNode = new Node(id, name);
	newNode->next = head;
	head = newNode;
}

void ListPhone::display() {
	nodePtr tempptr = head;
	cout << "List of phones:" << endl;
	while (tempptr)
	{
		cout << "ID: " << tempptr->p.id << "\tName: "<< tempptr->p.name << endl;
		tempptr = tempptr->next;
	}
}

void ListPhone::displayTop() {
	nodePtr lead = head;

	for (lead = head; lead->next; lead = lead->next);
	cout << "Displaying Most Recent.." << endl;
	cout << "ID: " << lead->p.id << "\tName: " << lead->p.name << endl;
}

//Deleting most recent from inserting at End!!!

void ListPhone::deleteEnd() {
	nodePtr trail = head;
	nodePtr lead = trail->next;

	for (lead = head; lead->next; lead = lead->next) {
		trail = lead;
	}
	cout << "Deleting..." << endl;
	trail->next = NULL;
	delete lead;

}


//Deleting most recent from inserting at Start!!!
void ListPhone::deleteStart() {
	if (head->next != NULL) {
		nodePtr temp = head;
		head = temp->next;
		cout << "Deleting..." << endl;
		delete temp;
	}
}

void ListPhone::deletePosition(int position)
{
	nodePtr tempptr = head;
	nodePtr trailptr = NULL;
	int counter = 0;

	if (position == 0)
	{
		head = head->next;
		delete tempptr;
		tempptr = NULL;
	}
	else
	{
		while (tempptr != NULL) {
			if (counter == position) {
				nodePtr temp = tempptr->next;
				delete tempptr;
				trailptr->next = temp;
				break;
			}
			trailptr = tempptr;
			tempptr = trailptr->next;
			counter++;
		}
	}
	cout << "Attempting to delete entry ";
}

bool ListPhone::getPhone(string name) {
	nodePtr temp = head;
	while (temp != NULL) {
		if (temp->p.name == name) {
			cout << "ID: " << temp->p.id << "\tName: " << temp->p.name << endl;
		}
		temp = temp->next;
		return true;
	}
}

ListPhone::ListPhone(const ListPhone& list) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	nodePtr temp = list.head;
	while (temp != NULL) {
		insertAtStart(temp->p.id, temp->p.name);
		temp = temp->next;
	}
	temp = 0;
	delete temp;
	
}

ListPhone& ListPhone::operator = (const ListPhone& list) {
	cout << "Overloading Assignment..." << endl;
	nodePtr temp = list.head;
	if (this != &list) {
		while (temp != NULL) {
			insertAtStart(temp->p.id, temp->p.name);
			temp = temp->next;
		}
	}
	return *this;

}

ListPhone::~ListPhone() {
	cout << "Freeing memory..." << endl;
	while (head) {
		deleteEnd();
	}
}