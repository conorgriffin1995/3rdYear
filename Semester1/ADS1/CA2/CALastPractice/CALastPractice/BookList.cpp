#include "BookList.h"
#include <iostream>

using namespace std;

BookList::BookList() {
	head = NULL;
}

void BookList::insert(string id, string name) {
	Node* newNode = new Node(id, name);
	if (head == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		nodeptr temp;
		for (temp = head; temp->next; temp = temp->next);
		temp->next = newNode;
	}
}

void BookList::display() const {
	nodeptr temp = head;
	while (temp != NULL) {
		cout << "ID:   " << temp->b.id << "\tName:   " << temp->b.name << endl;
		temp = temp->next;
	}
	cout << endl;
}

void BookList::deleteMostRecent() {
	nodeptr trail = head;
	nodeptr lead = trail->next;
	for (lead = head; lead->next; lead = lead->next) {
		trail = lead;
	}
	trail->next = NULL;
	delete lead;
}

int BookList::getName(string id) {
	cout << "Getting Book by ID.." << endl;
		nodeptr temp = head;
		while (temp != NULL) {
			if (temp->b.id == id) {
				cout << "Name:   " << temp->b.name << endl;
				return 0;
			}
			temp = temp->next;
		}	
}

void BookList::deleteFromPosition(int pos) {
	nodeptr lead = head;
	nodeptr trail = NULL;
	int counter = 0;

	if (pos == 0) {
		head = head->next;
		delete lead;
		lead = NULL;
	}
	else {
		while (lead != NULL) {
			if (counter == pos) {
				nodeptr temp = lead->next;
				delete lead;
				trail->next = temp;
				break;
			}
			trail = lead;
			lead = lead->next;
			counter++;
		}
	}
	cout << "Deleting Position..." << endl;
}


BookList::BookList(const BookList& list) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	nodeptr temp = list.head;
	while (temp != NULL) {
		insert(temp->b.id, temp->b.name);
		temp = temp->next;
	}

}

BookList& BookList::operator=(const BookList& list) {
	cout << "Overloading Assignment..." << endl;
	nodeptr temp = list.head;
	if (this != &list) {
		while (temp != NULL) {
			insert(temp->b.id, temp->b.name);
			temp = temp->next;
		}
	}
	return *this;
}

BookList::~BookList() {
	cout << "Freeing Memory..." << endl;
	nodeptr temp = head;
	while (temp != NULL) {
		nodeptr ptr = temp->next;
		delete temp;
		temp = ptr;
	}
	head = 0;
}

ostream& operator<<(ostream& output, const BookList& list) {
	list.display();
	return output;
}




