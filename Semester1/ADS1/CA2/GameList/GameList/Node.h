#pragma once
#include <string>

using namespace std;

class Node {
	friend class GameList;
	friend class Game;
public:
	Node();
	Node(string, string);

private:
	struct Game {
		string name;
		string price;
	};
	Game g;
	Node *next;
};
typedef Node* nodePtr;
