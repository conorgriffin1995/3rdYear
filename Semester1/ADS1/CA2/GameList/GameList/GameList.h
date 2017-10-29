#pragma once
#include "Node.h"

using namespace std;

class GameList {
public:
	GameList();

	void insert(string, string);
	void display();
	void deleteMostRecent();
	void deleteFromPosition(int pos);

	void getName(string);

	//The Big Three
	GameList(const GameList& list);
	GameList& operator =(const GameList& list);
	~GameList();
private:
	Node *head;
};
