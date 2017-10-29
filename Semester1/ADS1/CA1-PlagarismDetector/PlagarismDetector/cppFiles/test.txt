#include <iostream>
#include "ITIntVector.h"
using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ITIntVector vec;    //vector object
    int len = 4;
    int numbs [] = {1,2,3,4};
    
    for (int i = 0; i < len; i++) { //ads all the numbers inside the numbs array inside the vector
            vec.push_back(numbs[i]);
    }
    
    vec.push_back(5);   //ads another value insidr the vector
    
    cout << "You have entered " << vec.size() << endl
        << " elements. There are:"
    << endl;
	
	if(len = 4){
		cout << "Hello";
	}
    
    for (int i = 0; i < vec.size(); i++) {
        cout << vec.at(i)
        << endl;
    }
    
    
    cout << "The length of the vector is: " << vec.size() << endl   //prints the size of the vector
    << "The capacity is: " << vec.capacity() << endl;   //prints the capacity of the vector
    return 0;
}

//2 FORS
//1 IF