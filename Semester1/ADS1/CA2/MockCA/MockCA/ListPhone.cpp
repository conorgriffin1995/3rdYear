#include "ListPhone.h"

ListPhone::ListPhone() {
	head = NULL;
}

void ListPhone::insert(int id, string name) {
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

void ListPhone::display() const {
	nodePtr temp = head;
	while (temp != NULL) {
		cout << "ID: " << temp->p.id;
		cout << "\tName: " << temp->p.name << endl;
		temp = temp->next;
	}
	cout << " " << endl;
}

void ListPhone::deleteMostRecent() {
	nodePtr trail = head;
	nodePtr lead = trail->next;
	for (lead; lead->next; lead = lead->next) {
		trail = lead;
	}
	cout << "Deleting Most Recent..." << endl;
	trail->next = NULL;
	delete lead;
}

int ListPhone::getContact(int id) {
	nodePtr temp = head;
	while (temp != NULL) {
		temp = temp->next;
		if (temp->p.id == id); {
			cout << "ID: " << temp->p.id << endl;
			cout << "Name: " << temp->p.name << endl;

		}
		return 1;
	}
}

//The Big Three
ListPhone::ListPhone(const ListPhone& obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;

	nodePtr temp = obj.head;
	while (temp != NULL) {
		insert(temp->p.id, temp->p.name);
		temp = temp->next;
	}
	temp = 0;
	delete temp;
}

ListPhone& ListPhone::operator =(const ListPhone& obj) {
	Node *temp = obj.head;
	if (this != &obj) {

		while (temp != NULL) {
			insert(temp->p.id, temp->p.name);
			temp = temp->next;
		}
		head = temp;	
	}
	return *this;
}

ListPhone::~ListPhone() {
	Node* ptr = head;
	while (ptr != NULL) {
		Node* next = ptr->next;
		delete ptr;
		ptr = next;
	}
	head = 0;
}

