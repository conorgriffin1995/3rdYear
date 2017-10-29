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

void ListOfDoubles::displayList() const {
	ListNodePtr tempptr = head;
	while (tempptr != NULL) {
		cout << "Value : " << tempptr->value << endl;
		tempptr = tempptr->next;
	}
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

//Copy Constructor
ListOfDoubles::ListOfDoubles(const ListOfDoubles &obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	DoubleListNode* temp = obj.head;			//Assigning temp node pointer to list head

	while (temp != NULL) {
		this->insert(temp->value);				//adds items from the obj list to temp node
		temp = temp->next;
	}
	temp == NULL;
	delete temp;
}

//An = assignment operator
ListOfDoubles& ListOfDoubles::operator =(const ListOfDoubles &obj) { //assignment operator
	if (this != &obj) {
		while (head != NULL) {	//first empty list 
			deleteMostRecent();
			return *this;
		}
		DoubleListNode* current = obj.head;	//set pointer to the first link
		while (current != NULL) {			//until pointer points beyond last Node
			insert(current->value);			//print value
			current = current->next;		//move to the next Node
		}
		head = current;
		return *this;
	}

}

//Destructor
ListOfDoubles::~ListOfDoubles() {
	DoubleListNode* ptr = head;
	while (ptr != 0) {
		DoubleListNode* next = ptr->next;
		delete ptr;
		ptr = next;
	}
	head = 0;
}

//Overloading the << Operator
ostream& operator << (ostream& output, const ListOfDoubles& obj) {
	obj.displayList();
	return output;
}