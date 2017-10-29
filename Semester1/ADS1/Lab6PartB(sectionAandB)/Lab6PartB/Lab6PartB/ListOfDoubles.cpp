#include "ListOfDoubles.h"

ListOfDoubles::ListOfDoubles() {
	head = NULL; //an empty list to start
}

void ListOfDoubles::insert(double value) {
	DoubleListNode *newNode = new DoubleListNode(value);
	
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

void ListOfDoubles::displayList() {
	ListNodePtr tempptr = head;
	while (tempptr != NULL) {
		cout << "Value : " << tempptr->value << endl;
		tempptr = tempptr->next;
	}
	cout << endl;
}

void ListOfDoubles::deleteMostRecent() {
	ListNodePtr trail = head;							//1)assign trail = head
	ListNodePtr lead = trail->next;						//2)assign lead = trail pointer to next value as lead pointer is one value ahead of trail pointer

	for (lead = head; lead->next; lead = lead->next) {	//3)Loop through lead pointer
		trail = lead;									//4)assign trail to lead
	}
	cout << "Deleting..." << endl;
	trail->next = NULL;									//5)set trail next to null
	delete lead;										//6)delete lead
	
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
	else {
		// Find previous node of the node to be deleted
		for (int i = 0; trail != NULL && i < pos - 1; i++)
			trail = trail->next;

		// node trail->next is the node to be deleted
		// store pointer to the next of the node to be deleted
		DoubleListNode *next = trail->next->next;
		// unlink the node from the linked list
		free(trail->next);	// free memory
		trail->next = next; // unlink the deleted node from the list

	}
	
}

ListOfDoubles::~ListOfDoubles() {
	cout << "Freeing memory..." << endl;
	while (head) {
		deleteMostRecent();
	}
}

