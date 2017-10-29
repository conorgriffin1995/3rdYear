#include <iostream>
#include <string>
#include "ListBook.h"
using namespace std;

ListBook::ListBook() {
	head = NULL;
}

void ListBook::insert(string name, double price) {
	Node *newNode = new Node(name, price);

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

void ListBook::display() {
	nodePtr temp = head;
	while (temp != NULL) {
		cout << "Name: " << temp->b.name << endl;
		cout << "Price: " << temp->b.price << endl;
		temp = temp->next;
	}
	cout << endl;
}

void ListBook::deleteMostRecent() {
	nodePtr trail = head;
	nodePtr lead = trail->next;
	for (lead = head; lead->next; lead = lead->next) {
		trail = lead;
	}
	cout << "Deleting..." << endl;
	trail->next = NULL;
	delete lead;
}

bool ListBook::getBook(string name) {
	nodePtr temp = head;
	while (temp != NULL) {
		temp = temp->next;
		if (temp->b.name == name) {
			cout << "Name: " << temp->b.name << endl;
			cout << "Price: " << temp->b.price << endl;
			cout << endl;
		}
		return true;
	}
}

//The Big Three
ListBook::ListBook(const ListBook& obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	nodePtr temp = obj.head;
	while (temp != NULL) {
		insert(temp->b.name, temp->b.price);
		temp = temp->next;
	}
	temp = 0;
	delete temp;
}

ListBook& ListBook::operator =(const ListBook& obj) {
	nodePtr temp = obj.head;
	if (this != &obj) {
		while (temp != NULL) {
			insert(temp->b.name, temp->b.price);
			temp = temp->next;
		}
		head = temp;
	}
	return *this;
}

ListBook::~ListBook() {
	cout << "Freeing Memory..." << endl;
	nodePtr temp = head;
	while (temp != NULL) {
		nodePtr ptr = temp->next;
		delete temp;
		temp = ptr;
	}
	head = 0;
}