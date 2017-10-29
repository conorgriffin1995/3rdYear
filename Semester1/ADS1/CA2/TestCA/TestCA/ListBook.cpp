#include <iostream>
#include <string>
#include "ListBook.h"
using namespace std;

ListBook::ListBook() {
	head = NULL;
}

void ListBook::insert(string name, double price) {
	Node *newNode = new Node(name, price);	//1)Create a new node
											//2)Next if head == NULL then newNode next = head and head = newNode
	if (head == NULL) {								
		newNode->next = head;
		head = newNode;
	} 
	else {
		nodePtr temp;									 //3)Create temp pointer,
		for (temp = head; temp->next; temp = temp->next);//4)loop through it
		temp->next = newNode;							 //5)assign temp next to newNode
	}
}

void ListBook::display() {
	nodePtr temp = head;							//1)create temp node = to head
	while (temp != NULL) {							//2) Loop: while head != NULL
		cout << "Name: " << temp->b.name << endl;	//3)display name
		cout << "Price: " << temp->b.price << endl; //4)display price
		temp = temp->next;							//5)temp = temp to next node
	}
	cout << endl;
}

void ListBook::deleteMostRecent() {	//We need two pointer, a trail and a lead
	nodePtr trail = head;								//1)assign trail = head
	nodePtr lead = trail->next;							//2)assign lead = trail pointer to next value as lead pointer is one value ahead of trail pointer

	for (lead = head; lead->next; lead = lead->next) {	//3)Loop through lead pointer
		trail = lead;									//4)assign trail to lead
	}
	cout << "Deleting..." << endl;						
	trail->next = NULL;									//5)set trail next to null
	delete lead;										//6)delete lead

}

bool ListBook::getBook(string name) {
	nodePtr temp = head;							 //1)assign trail = head
	while (temp != NULL) {							 //2)loop through while temp!=null
		temp = temp->next;							 //3)temp pointer = next value (this points to the next value in the loop)
		if (temp->b.name == name) {					 //4)if we land on price entered
			cout << "Name: " << temp->b.name << endl;//5)print out values
			cout << "Price: " << temp->b.price << endl;
			cout << endl;
		}
		return true;	//return true
	}
}

//The Big Three
//1) Copy Constructor
ListBook::ListBook(const ListBook& obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;							//1) assign head to NULL
	nodePtr temp = obj.head;				//2)create temp pointer = to passed in object head
	while (temp != NULL) {					//3)loop through while temp != NULL
		insert(temp->b.name, temp->b.price);//4)insert object values
		temp = temp->next;					//5)assign temp = to next (points to next value in loop)
	}
	temp = 0;								//6)set temp to 0
	delete temp;							//7)delete temp 
}

//2) Overloaded Assignment
ListBook& ListBook::operator =(const ListBook& obj) {
	cout << "Overloaded Assignment..." << endl;
	nodePtr temp = obj.head;					//1)create temp pointer = to passed in object head
	if (this != &obj) {							//2)if this != obj
		while (temp != NULL) {					//3)loop through while temp!=NULL
			insert(temp->b.name, temp->b.price);//4)insert object values
			temp = temp->next;					//5)temp = temp next
		}
	}
	return *this;								//6)return this

}

//3) Destructor
ListBook::~ListBook() {
	cout << "Freeing memory..." << endl;
	nodePtr temp = head;						//1)create temp = to head
	//while (temp != NULL) {					//2)loop through while temp!=NULL
	//	nodePtr next = temp->next;				//3)create another pointer = to temp next
	//	delete temp;							//4)delete temp
	//	temp = next;							//5)assign temp = to next
	//}
	//head = 0;									//6)assign head = to 0
	while (temp != NULL) {
		deleteMostRecent();
	}
	delete temp;
	head = 0;
}
