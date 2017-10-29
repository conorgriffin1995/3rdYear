#include "ListGame.h"
#include <iostream>
using namespace std;

int main() {
	ListGame g1;

	g1.insert("Snake", "22.99");	//0
	g1.insert("Tomb", "25.99");		//1
	g1.insert("Sawing", "35.99");	//2
	g1.insert("Chess", "30.99");	//3

	g1.display();

	g1.deleteMostRecent();

	g1.display();
	
	g1.getName("22.99");
	cout << endl;
	
	g1.deleteFromPosition(1);

	g1.display();
	/*
	ListGame g2(g1);

	g2.display();

	ListGame g3;
	g3 = g1;

	g3.display();*/

	system("pause");
	return 0;
}