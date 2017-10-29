#include <iostream>
//Conor Griffin
//X00111602

using namespace std;
/*
An enumeration is a distinct type whose value is restricted to a range of values.
We are using a enumerator-list which is comma separated list of 
enumerator definitions, each of which is an identifier.
Enumerator we have created here is a list of players with a players count.

*/

enum players
{
	Fred,
	Paul,
	Jim,
	Allen,
	playersCount	//Count of players
};

/*
A function called scores is created with a reference in its
return type (int&). Our enumerator players is
passed in as an argument named challengers.
An array of type static int called scoreCard of size playersCount,
we return this array filled with our enumerator challengers, we can see this
in the code below in main.
This tells us that players enumerator is used as an array
of scores.
*/

int& scores(players challengers) {
	static int scoreCard[playersCount];
	return scoreCard[challengers];
}

/*
When we are running the code in main we see that scores function is called
and our players enumerator is called with each of our definitions that we passed
in earlier, first we see Fred then paul etc.. Since the scores function returns 
the score of the player that is passed in Fred = 5, so Fred has a score of 5.
scores() is an Lvalue because it continues to exist beyond the value that defines it.
5 on the right hand side is an Rvalue because it is a temporary value stored in
scores(Fred) It does not persist beyond the value that defines it.
Each scores is outputted to the screen through cout.

If we wanted to return the player count playersCount to see how many players we 
had all we would have to do is cout << playersCount..this would give us a value of 4
*/

int main() {

	scores(Fred) = 5;
	scores(Paul) = 10;
	scores(Jim) = 15;
	scores(Allen) = 20;

	cout << scores(Fred) << " " << endl;
	cout << scores(Paul) << " " << endl;
	cout << scores(Jim) << " " << endl;
	cout << scores(Allen) << " " << endl;

	//cout << playersCount << " players!!!" << endl;

	system("pause");
	return 0;
		
}