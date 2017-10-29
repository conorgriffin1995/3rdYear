#include "ListOfEmployees.h"

ListOfEmployees::ListOfEmployees() {
	head = NULL;
}

void ListOfEmployees::insert(string name, double salary) {
	EmpNode *newNode = new EmpNode(name, salary);

	if (head == NULL) {
		newNode->next = head;
		head = newNode;
	}
	else {
		nodePtr tempPtr;
		for (tempPtr = head; tempPtr->next; tempPtr = tempPtr->next);
		tempPtr->next = newNode;
	}
}

void ListOfEmployees::display() const {
	nodePtr tempPtr = head;
	while (tempPtr != NULL) {
		cout << "Name\t: " << tempPtr->emp.name << endl;
		cout << "Salary\t: " << tempPtr->emp.salary << endl;
		tempPtr = tempPtr->next;
	}
	cout << " " << endl;
}

void ListOfEmployees::deleteMostRecent() {
	if (head != NULL) {
		EmpNode *end = head;

		head = end->next;
		cout << "\nDeleting : " << end->emp.name;
		cout << "\nDeleting : " << end->emp.salary << endl;
		delete end;
	}
}


double ListOfEmployees::getSalary(string name) {
	nodePtr tempPtr = head;
	while (tempPtr != NULL) {
		tempPtr = tempPtr->next;
		if (tempPtr->emp.name == name) {
			cout << "\nName\t: " << tempPtr->emp.name;
			cout << "\nSalary\t: " << tempPtr->emp.salary << endl;
			return 1;
		}
	}


}

//Copy Constructor
ListOfEmployees::ListOfEmployees(const ListOfEmployees &obj) {
	cout << "Copying Constructor..." << endl;
	head == NULL;
	nodePtr temp = obj.head;
	while (temp != NULL) {
		this->insert(temp->emp.name, temp->emp.salary);
		temp = temp->next;
	}
	temp == NULL;
	delete temp;
}

//An = assignment operator
ListOfEmployees& ListOfEmployees::operator=(const ListOfEmployees &obj) {
	if (this != &obj) {
		while (head != NULL) {
			deleteMostRecent();
			return *this;
		}
		EmpNode* current = obj.head;
		while (current != NULL) {
			insert(current->emp.name, current->emp.salary);
			current = current->next;
		}
		head = current;
		return *this;
	}
}

//Destructor
ListOfEmployees::~ListOfEmployees() {
	cout << "Freeing memory!\n";
	EmpNode* ptr = head;
	while (ptr != NULL) {
		EmpNode* next = ptr->next;
		delete ptr;
		ptr = next;
	}
	head = 0;
}

//Overloading the << Operator
ostream& operator << (ostream& output, const ListOfEmployees& obj) {
	obj.display();
	return output;
}