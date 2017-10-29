#include "ListOfDoubles.h"

ListOfDoubles::ListOfDoubles() {
	head = NULL; //an empty list to start
	size = 0;
}

void ListOfDoubles::insert(double value) {
	DoubleListNode *newNode;
	newNode = new DoubleListNode;
	newNode->value = value;
	if (head == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		ListNodePtr temp;
		for (temp = head; temp->next; temp = temp->next);
		temp->next = newNode;
	}

}

void ListOfDoubles::displayList() const{
	ListNodePtr tempptr = head;
	while (tempptr != NULL) {
		cout << "Value : " << tempptr->value << endl;
		tempptr = tempptr->next;
	}
	cout << " " << endl;
}

double ListOfDoubles::displayTop() {
	double returnValue = 0.00;
	DoubleListNode *end = head;

	if (end->next != NULL) {
		returnValue = end->value;
	}
	return returnValue;
	
}

double ListOfDoubles::deleteMostRecent() {

	if (head->next != NULL) {
		DoubleListNode *end = head;
		head = end->next;
		cout << "Deleting: " << end->value << endl;
		delete end;
	}
	return 1;
}

double ListOfDoubles::getSize() {
	return size;
}


ListOfDoubles::~ListOfDoubles() {
	DoubleListNode* ptr = head;
	while (ptr != 0) {
		DoubleListNode* next = ptr->next;
		delete ptr;
		ptr = next;
	}
	head = 0;
}