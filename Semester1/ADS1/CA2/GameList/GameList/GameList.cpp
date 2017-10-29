#include "GameList.h"
#include <iostream>

GameList::GameList() {
	head = NULL;
}

void GameList::insert(string name, string price) {
	Node* newNode = new Node(name, price);
	if (head == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		nodePtr temp = head;
		for (temp = head; temp->next; temp = temp->next);
		temp->next = newNode;
	}
}

void GameList::display() {
	nodePtr temp = head;
	while (temp != NULL) {
		cout << "Name: " << temp->g.name << "\tPrice: " << temp->g.price << endl;
		temp = temp->next;
	}
	cout << endl;
}

void GameList::deleteMostRecent() {
	nodePtr trail = head;
	nodePtr lead = trail->next;
	
	for (lead = head; lead->next; lead = lead->next) {
		trail = lead;
	}
	cout << "Deleting Most Recent Game.." << endl;
	trail->next = NULL;
	delete lead;	
}

void GameList::getName(string name) {
	nodePtr temp = head;
	while (temp != NULL) {
		if (temp->g.name == name) {
			cout << temp->g.price << endl;
		}
		temp = temp->next;
	}
	if (temp == NULL) {
		cout << "No Games Match This Name.." << endl;
	}
	
}

//The Big Three
GameList::GameList(const GameList& list) {
	head == NULL;
	nodePtr temp = list.head;
	while (temp != NULL) {
		insert(temp->g.name, temp->g.price);
		temp = temp->next;
	}
	cout << "Copying Constructor..." << endl;

}

GameList& GameList::operator=(const GameList& list) {
	cout << "Overloading Assignment..." << endl;
	nodePtr temp = list.head;
	if (this != &list) {
		while (temp != NULL) {
			insert(temp->g.name, temp->g.price);
			temp = temp->next;
		}
	}
	return *this;
}

GameList::~GameList() {
	cout << "Freeing memory..." << endl;
	nodePtr temp = head;
	while (temp != NULL) {
		nodePtr next = temp->next;
		delete temp;
		temp = next;
	}
	head = 0;
}

void GameList::deleteFromPosition(int pos) {
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

