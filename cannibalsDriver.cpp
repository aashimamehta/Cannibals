//Author: Aashima Mehta
//Driver 

#include <iostream> 
#include "cannibals.h"
using namespace std;


int main() {
	cannibals can = cannibals(6);
	
	cout << "Sequence of moves" << endl;
	cout << endl;
	can.safe();

}

