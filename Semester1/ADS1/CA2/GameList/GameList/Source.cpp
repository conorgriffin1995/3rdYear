#include "GameList.h"
#include <iostream>

using namespace std;

int main() {
	GameList g1;

	g1.insert("Golf", "22.99");	  //0
	g1.insert("Aliens", "35.99"); //1
	g1.insert("Snake", "50.99");  //2
	g1.insert("Tombs", "15.99");  //3
	g1.insert("Blocks", "12.99"); //4

	g1.getName("Golf");

	g1.display();

	g1.deleteFromPosition(2);

	g1.display();

	g1.deleteMostRecent();

	g1.display();

	

	GameList g2(g1);
	g1.display();

	GameList g3;
	g3 = g2;

	g3.display();

	system("pause");
	return 0;
}