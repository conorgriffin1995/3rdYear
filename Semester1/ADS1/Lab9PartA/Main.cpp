// Lee Healy 
// X00120179
// Lab 9 Part A


//Explain the following code
#include <iostream>
using namespace std;

// Creating an enumeration of 4 players and a count.
enum players
{
		Fred,
		Paul,
		Jim,
		Allen,
		playersCount	// Count of players
};

int& scores(players challengers)
{
	static int scoreCard[playersCount];
	return scoreCard[challengers];
}

int main()
{
	// Giving the players their scores.
	// scores(player) is the LValue as it must be on the left.
	// The score itself is an RValue as it must be on the right.
	scores(Fred) = 5;
	scores(Paul) = 10;
	scores(Jim) = 15;
	scores(Allen) = 20;

	// Displaying the players' scores.
	cout << scores(Fred) << " " << endl;
	cout << scores(Paul) << " " << endl;
	cout << scores(Jim) << " " << endl;
	cout << scores(Allen) << " " << endl;
	
	// Adding in a display of playersCount.
	//cout << playersCount << " " << endl;
	
	system("pause");

	return 0;
}
