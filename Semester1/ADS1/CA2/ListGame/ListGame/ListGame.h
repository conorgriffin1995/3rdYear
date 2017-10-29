#pragma once
#include "Node.h"

using namespace std;

class ListGame {
public:
	ListGame();
	void insert(string, string);
	void display();
	void deleteMostRecent();
	void deleteFromPosition(int);
	int getName(string);

	//The Big Three
	ListGame(const ListGame& list);
	ListGame& operator=(const ListGame& list);
	~ListGame();
private:
	Node *head;
};
