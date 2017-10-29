#include "ListOfDoubles.h"

//Constructor
ListOfDoubles::ListOfDoubles() {
	head = NULL; //an empty list to start
}

void ListOfDoubles::insert(double value) {
	DoubleListNode *newNode;
	newNode = new DoubleListNode();
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
	cout << " " << endl;
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

//Couldnt get the solution to deleteDouble(int pos)
//Found code online which I wasnt too sure about
//I manipulated the online code to work with my code and it works
void ListOfDoubles::deleteDouble(int pos) {
	DoubleListNode *current = head;
	DoubleListNode *trail = NULL;

	// if linked list is empty 
	if (current == NULL)
		return;

	// store head node in trail pointer
	trail = current;

	// if head needs to be removed
	if (pos == 0) {
		current = trail->next;	// change head
		free(trail);			// free old head
		return;
	}

	// Find previous node of the node to be deleted
	for (int i = 0; trail != NULL && i < pos - 1; i++)
		trail = trail->next;

	// if position is more than the number of nodes
	if (trail == NULL || trail->next == NULL)
		return;

	// node trail->next is the node to be deleted
	// store pointer to the next of the node to be deleted
	DoubleListNode *next = trail->next->next;

	// unlink the node from the linked list
	free(trail->next);	// free memory

	trail->next = next; // unlink the deleted node from the list
}

//Copy Constructor
ListOfDoubles::ListOfDoubles(const ListOfDoubles &obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	DoubleListNode* temp = obj.head;		//Assigning temp node pointer to list head

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
	cout << "Freeing memory!\n";
	while (ptr != NULL) {
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