#include "deque.h"
#include "DequeEmpty.h"
#include "DequeFull.h"
#include <iostream>

using namespace std;

deque::deque(int s) {
	cArr[size];
	size = s;
	headIndex = 0;
	tailIndex = (size -1);
}

//bool deque::insertHead(int value) {
//	if (tailIndex < size) {
//
//		cArr[tailIndex] = value;
//		tailIndex--;
//		return true;
//	}
//	else {
//		return false;
//	}
//	
//}

//bool deque::insertTail(int value) {
//	if (headIndex < size) {
//
//		cArr[headIndex] = value;
//		headIndex++;
//		return true;
//	}
//	else {
//		return false;
//	}
//}

//bool deque::removeTail(int & item) {
//	cArr[tailIndex] = item;
//	if(tailIndex == size -1){
//		tailIndex = -1;
//		headIndex++;
//		return true;
//	}
//	else {
//		return false;
//	}
//}

//bool deque::removeHead(int & item) {
//	cArr[headIndex] = item;
//	if (headIndex == size) {
//		headIndex = 0;
//		tailIndex++;
//		return true;
//	}
//	else {
//		return false;
//	}
//}

bool deque::isEmpty() {
	if (headIndex == 0) {
		return true;
	}
	else {
		return true;
	}
}

bool deque::isFull() {
	if (tailIndex >= size -1) {
		return true;
	}
	else {
		return false;
	}
}

void deque::insertHead(int value) {
	try {
		if (isFull()) {
			throw DequeFull();
		}	
	}
	catch (DequeFull ex) {
		cout << "Cannot insert from the head \n";
	}
	if (tailIndex < size) {
		cArr[tailIndex] = value;
		tailIndex--;
	}
}

void deque::insertTail(int value) {
	try {
		if (isFull()) {
			throw DequeFull();
			
		}
	}
	catch (DequeFull ex) {
		cout << "Cannot insert from the back \n";
	}
	if (headIndex < size) {
		cArr[headIndex] = value;
		headIndex++;
	}
}

int deque::removeHead(int& item) {
	try {
		if (isEmpty()) {
			throw DequeEmpty();
		}	
	}
	catch (DequeEmpty ex) {
		cout << "Cannot remove from the front \n";
		return item;
	}
	cArr[headIndex] = item;
	if (headIndex == size) {
		headIndex = 0;
		tailIndex++;
		return item;
	}
}

int deque::removeTail(int& item) {
	try {
		if (isEmpty() == true) {
			throw DequeEmpty();
		}
	}
	catch (DequeEmpty ex) {
		cout << "Cannot remove from the back \n";
	}
	cArr[tailIndex] = item;
	if(tailIndex == size -1){
		tailIndex = -1;
		headIndex++;
		return true;
	}
}

ostream & operator<<(ostream & output, const deque & obj) {
	for (int i = 0; i < obj.size; i++) {
		output << obj.cArr[i] << endl;
	}
	return output;
}

