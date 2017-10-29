#include "ListGame.h"
#include <iostream>

using namespace std;

ListGame::ListGame() {
	head = NULL;
}

void ListGame::insert(string n, string p) {
	Node* newNode = new Node(n, p);
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

void ListGame::display() {
	nodePtr temp = head;
	while (temp != NULL) {
		cout << "Name:  " << temp->g.name << "\tPrice:  " << temp->g.price << endl;
		temp = temp->next;
	}
	cout << endl;
}

void ListGame::deleteMostRecent() {
	cout << "Deleting Most Recent Game..." << endl;
	nodePtr trail = head;
	nodePtr lead = trail->next;
	for (lead = head; lead->next; lead = lead->next) {
		trail = lead;
	}
	trail->next = NULL;
	delete lead;
}


int ListGame::getName(string price) {
	if (head->g.price == price) {
		cout << head->g.name << endl;
		return 1;
	}
	nodePtr temp = head;
	while (temp != NULL) {
		temp = temp->next;
		if (temp->g.price == price) {
			cout << temp->g.name << endl;
			return 1;
		}
	}
	return 0;
}

void ListGame::deleteFromPosition(int pos) {
	nodePtr lead = head;
	nodePtr trail = NULL;
	int counter = 0;

	if (pos == 0) {
		head = head->next;
		delete lead;
		lead = NULL;
	}
	else {
		while (lead != NULL) {
			if (counter == pos) {
				nodePtr temp = lead->next;
				delete lead;
				trail->next = temp;
				break;
			}
			trail = lead;
			lead = trail->next;
			counter++;
		}
	}
	cout << "Attempting to delete entry..." << endl;
}


//The Big Three
ListGame::ListGame(const ListGame& list) {
	cout << "Copying Constructor.." << endl;
	head == NULL;
	nodePtr temp = list.head;
	while (temp != NULL) {
		insert(temp->g.name, temp->g.price);
		temp = temp->next;
	}
}

ListGame& ListGame::operator=(const ListGame& list) {
	cout << "Overloading Assignment.." << endl;
	nodePtr temp = list.head;
	if (this != &list) {
		while (temp != NULL) {
			insert(temp->g.name, temp->g.price);
			temp = temp->next;
		}
	}
	return *this;
}

ListGame::~ListGame() {
	nodePtr temp = head;
	while (temp != NULL) {
		nodePtr ptr = temp->next;
		delete temp;
		temp = ptr;
	}
	head = 0;
}