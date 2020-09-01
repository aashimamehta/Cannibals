//Author: Aashima Mehta
//CSS 342 Assignment #2 cannibals and explorers

#include "cannibals.h"
using namespace std;

//default constuctor
cannibals::cannibals() {
	this->option = 0;
	this->size = 0;
	this->cann = 0;
	this->expo = 0;
	right = new string[size];
	left = new string[size];
	boat = new string[2];
	cout << "There are no explorers or cannibals to move!" << endl;
}


cannibals::cannibals(int n) {
	this->option = 0;
	if (n < 1) {
		cout << "invalid input" << endl;
	}
	else {
		this->size = n;
		if (n % 2 == 1) {               //if number is odd then by deafault make cannibals more than expo
			this->cann = n / 2;
			this->expo = n / 2 + 1;
		}
		else {                          //if number is even then make cann and expo equal
			this->cann = size / 2;
			this->expo = size / 2;
		}
		right = new string[size];
		left = new string[size];
		boat = new string[2];
		boat[0] = empty;
		boat[1] = empty;

		for (int i = 0; i < expo; i++) {
			right[i] = "E";
			left[i] = empty;
		}
		for (int i = expo; i < size; i++) {
			right[i] = "C";
			left[i] = empty;
		}
		
	}
}

cannibals::cannibals(int c, int e) {
	this->option = 0;
	this->size = c + e;
	this->cann = c;
	this->expo = e;
	right = new string[size];
	left = new string[size];
	boat = new string[2];
	boat[0] = empty;
	boat[1] = empty;
	if (c > e) {
		cout << "All explorers died because the number of cannibals was greater." << endl;
	}
	else {
		for (int i = 0; i < e; i++) {
			right[i] = "E";
			left[i] = empty;
		}
		for (int i = e; i < size; i++) {
			right[i] = "C";
			left[i] = empty;
		}
	}
}


//Accessors
string cannibals::getRight(int n) const {
	string word = this->right[n];
	return word;
}

string cannibals::getLeft(int n) const {
	return this->left[n];
}

string cannibals::getBoat(int n) const {
	return this->boat[n];
}

int cannibals::getSize() const {
	return this->size;
}

//Mutators
void cannibals::setRight(string n, int index){
	right[index] = n;
}
void cannibals::setLeft(string n, int index){
	left[index] = n;
}
void cannibals::setBoat(string n, int index) {
	boat[index] = n;
}


//get explorers from right
//int cannibals::getExpoRight(cannibals& c) const {
int cannibals::getExpoRight() const{
	int count = 0;
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getRight(i) == "E") {
			count++;
		}
	}
	return count;
}

//get explorers from left
//int cannibals::getExpoLeft(cannibals& c) const {
int cannibals::getExpoLeft() const {
	int count = 0;
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getLeft(i) == "E") {
			count++;
		}
	}
	return count;
}

//get cannibals from right
int cannibals::getCanRight() const {
	int count = 0;
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getRight(i) == "C") {
			count++;
		}
	}
	return count;
}

//get cannibals from left
int cannibals::getCanLeft() const {
	int count = 0;
	for (int i = 0; i < this->getSize(); i++) {
		if (this->getLeft(i) == "C") {
			count++;
		}
	}
	return count;
}


//check if solved
bool cannibals::isSolved() {
	
		if ((getCanRight() == 0) && (getExpoRight() == 0) && !isKilled()){
			return true;
	}
	return false;
}

//checks to see killed -- returns true if killed
//returns true when can > expo && expo != 0 // expos are killed if true
bool cannibals::isKilled() {
	if (((this->getCanLeft() > this->getExpoLeft()) && this->getExpoLeft() != 0)||
		((this->getCanRight() > this->getExpoRight()) && this->getExpoRight() != 0)){
	return true;				
}
	return false;
}

bool cannibals::safe() {
	//check how many expos and cans are in the left
	//print initial state
	if (isSolved()) {
		return true;
	}
	if (getExpoLeft() == 0 && getCanLeft() == 0) {
		printLeft();
	}
	if (size < 1) {
		cout << "ERROR";
		return false;
	}
	string choose = "";
	int rememberC = 0;
	int rememberE = 0;
	int remember = 0;
	//first look into the right side -- decide what can you take?


	//"EC"
	if (getCanRight() == getExpoRight() && getExpoRight() != 2) {

		rememberE = 0;
		rememberC = 0;
		choose = "EC";
		remember = 0;
		//FIND IT PUT IT INTO THE BOAT
		for (int i = 0; i < size; i++) {
			if (right[i] == "E") {
				setBoat(getRight(i), 0);
				setRight(empty, i);
				remember = i;
				for (int j = 0; j < size; j++) {
					if (right[j] == "C") {
						setBoat(getRight(j), 1);
						setRight(empty, j);
						rememberC = j;
						break;
					}
				}
				break;
			}
		}
		print();
		////now at the left shore?
			//drop the passengers
		setLeft("E", remember);
		setLeft("C", rememberC);
		setBoat(empty, 0);
		setBoat(empty, 1);
		printRight();
		if (isSolved()) {
			return true;
		}
		//decide which one to leave?
		if ((getCanLeft() > getExpoLeft())) {
			setBoat("C", 0);
			setLeft(empty, rememberC);
			print();
			setRight("C", rememberC);
		}
		else if (getExpoLeft() > getCanLeft()) {
			setBoat("E", 0);
			print();
			setLeft(empty, remember);
			setRight("E", remember);
		}
		else if((getCanLeft() == getExpoLeft())&& getCanLeft() == 1) {		//equal
			setBoat("E", 0);
			setLeft(empty, remember);
			print();
			setRight("E", remember);
		}

		if (isSolved()) {
			return true;
		}
		//printLeft();
		//reached the other shore therefore empty out the boat!
		else{    //(!isSolved()){
			if (getBoat(0) == "C") {
				setRight(getBoat(0), rememberC);
			}
			else {
				setRight(getBoat(0), remember);
			}
			setBoat(empty, 0);
			printLeft();
			if (isSolved()) {
				return true;
			}
			else {
				safe();
			}
		}
	}


	//"EE" ---- C --- CC = EEE --- ACTUAL C EEE
	if ((getExpoRight() == 2 && getCanRight() == 2) ||
		(getExpoRight() - 2 >= getCanRight())) {
		//FIND "E" TO PUT IT INTO THE BOAT
		for (int i = 0; i < size; i++) {
			if (right[i] == "E") {
				setBoat(getRight(i), 0);
				setRight(empty, i);
				remember = i;
				for (int j = i + 1; j < size; j++) {
					if (right[j] == "E") {
						setBoat(getRight(j), 1);
						setRight(empty, j);
						rememberE = j;
						break;
					}
				}
				break;
			}
		}
		//getting transfered
		print();
		//take the passengers out of the boat
		setLeft("E", remember);
		setLeft("E", rememberE);
		setBoat(empty, 0);
		setBoat(empty, 1);
		printRight();

		if (isSolved()) {
			return true;
		}

		//what to take with
		if (getCanLeft() == getExpoLeft()) {
			//take "EC"
			for (int i = 0; i < size; i++) {
				if (left[i] == "E") {
					setBoat("E", 0);
					setLeft(empty, i);
					remember = i;
					for (int j = 0; j < size; j++) {
						if (left[j] == "C") {
							setBoat("C", 1);
							setLeft(empty, j);
							rememberC = j;
							break;
						}
					}
					break;
				}

			}
			print();
			setRight("E", remember);
			setRight("C", rememberC);
			//empty the boat
			setBoat(empty, 0);
			setBoat(empty, 1);
			printLeft();
		}
		else if (getCanLeft() >= getExpoLeft() || getExpoRight() == 0) {
			//find "C"
			for (int i = 0; i < size; i++) {
				if (left[i] == "C") {
					setBoat("C", 0);
					setLeft(empty, i);
					rememberC = i;
					print();
					break;
				}
			}
			setRight("C", rememberC);
			setBoat(empty, 0);
			setBoat(empty, 1);
			printLeft();
		}
		else {
			setBoat("E", 0);
			setLeft(empty, remember);
			print();
			setRight("E", remember);
			setBoat(empty, 0);
			setBoat(empty, 1);
			printLeft();
		}
		if (isSolved()) {
			return true;
		}
		else {
			safe();
		}
	}

	//"CC" CASE -- E more on right than left
	if ((getExpoRight() - 1 == getCanRight()) || (getCanRight() < getExpoRight()) || (getCanRight() > getExpoRight())) {
		choose = "CC";
		remember = 0;
		rememberC = 0;
		//FIND IT PUT IT INTO THE BOAT
		for (int i = 0; i < size; i++) {
			if (right[i] == "C") {
				setBoat(getRight(i), 0);
				setRight(empty, i);
				remember = i;
				for (int j = i + 1; j < size; j++) {
					if (right[j] == "C") {
						setBoat(getRight(j), 1);
						setRight(empty, j);
						rememberC = j;
						break;
					}
				}
				break;
			}
		}

		if (isSolved()) {
			return true;
		}
		print();
		if (isKilled()) {
			setRight("C", remember);
			setBoat(empty, 0);
			setRight("C", rememberC);
			setBoat(empty, 1);
			safe();
		}
		//now lets take care of the left side
		else {
			//drop the passengers
			setLeft("C", remember);
			setLeft("C", rememberC);
			setBoat(empty, 0);
			setBoat(empty, 1);
			printRight();
			//decide which one to TAKE BACK?
			if (getExpoLeft() > getCanLeft()) {
				//find "E"
				for (int i = 0; i < size; i++) {
					if (left[i] == "E") {
						setBoat("E", 0);
						setLeft(empty, i);
						rememberE = i;
						print();
						break;
					}
				}
				setRight("E", rememberE);
				//printRight();
			}
			else {
				setBoat("C", 0);
				setLeft(empty, rememberC);
				if (isKilled()) { //(getCanLeft() > getExpoLeft())) {
					setBoat("C", 1);
					setLeft(empty, remember);
					print();
					setRight("C", remember);
				}
				else {
					print();
				}
				setRight("C", rememberC);
				//printLeft();
			}
		}
		//drop the passengers on the left
		setBoat(empty, 0);
		printLeft();

		if (isSolved()) {
			return true;
		}
		else {
			safe();
		}
	}


	//"E"

	if (getCanRight() < getExpoRight()) {
		rememberC = 1;
		choose = "E";
		//FIND "C" TO PUT IT INTO THE BOAT
		for (int i = 0; i < size; i++) {
			if (right[i] == "E") {
				setBoat(getRight(i), 0);
				setRight(empty, i);
				printLeft();
				rememberC = i;
				break;
			}
		}
		//print the boat

		//take it to the other shore //empty out the boat
		setLeft("E", rememberC);
		setBoat(empty, 0);
		print();
		if (isSolved()) {
			return true;
		}
		//check what to take on the left side?
		else {
			if (getExpoLeft() > getCanLeft()) {
				//find "C"
				for (int i = 0; i < size; i++) {
					if (left[i] == "E") {
						setBoat("E", 0);
						setLeft(empty, i);
						rememberE = i;
						printRight();
						break;
					}
				}
				setRight("E", rememberE);
				setBoat(empty, 0);

			}
			else {
				setBoat("C", 0);
				setLeft(empty, rememberC);
				printRight();
				setRight("C", rememberC);
				setBoat(empty, 0);
			}
		}
		//drop off passengers
		printRight();
		if (isSolved()) {
			return true;
		}
		else {
			safe();
		}
	}

	//"C"
	if (getCanRight() < getExpoRight()) {
		rememberE = 0;
		choose = "C";
		//FIND "E" TO PUT IT INTO THE BOAT
		for (int i = 0; i < size; i++) {
			if (right[i] == "C") {
				setBoat(getRight(i), 0);
				setRight(empty, i);
				rememberE = i;

				break;
			}
		}
		//print the boat
		print();
		//take it to the other shore //empty out the boat
		setLeft("C", rememberE);
		setBoat(empty, 0);
		printRight();

		if (isSolved()) {
			return true;
		}
		//check what to take on the left side?
		else {
			if (getCanLeft() < getExpoLeft()) {
				//find "E"
				for (int i = 0; i < size; i++) {
					if (left[i] == "E") {
						setBoat("E", 0);
						setLeft(empty, i);
						rememberC = i;
						print();
						break;
					}
				}
				setRight("E", rememberC);
				setBoat(empty, 0);
				printLeft();
			}
			else {
				setBoat("C", 0);
				setLeft(empty, rememberE);
				print();
				setRight("C", rememberE);
				setBoat(empty, 0);
				printLeft();
			}
		}
		if (isSolved()) {
			return true;
		}
		else {
			safe();
		}
	}


	if (isSolved()) {
		return true;
	}

	//print the right side after deciding

	//print the middle portion in the boat

	//transfer everything to the left
	//look into if solved() or not
	//if not solved then what can you bring back?

	return false;
}

	//print the right side after deciding

	//print the middle portion in the boat

	//transfer everything to the left
	//look into if solved() or not
	//if not solved then what can you bring back?




void cannibals::print() {
	for (int i = 0; i < size; i++) {
		cout << right[i];
	}
	cout << "          \\ ";
	for(int i = 0; i < 2; i++) {
		cout << boat[i];
	}
	cout << " /         ";
	for (int i = 0; i < size; i++) {
		cout << left[i];
	}
	cout << endl;
}

void cannibals::printLeft() {
	for (int i = 0; i < size; i++) {
		cout << right[i];
	}
	cout << "   \\ ";
	for (int i = 0; i < 2; i++) {
		cout << boat[i];
	}
	cout << " /                ";
	for (int i = 0; i < size; i++) {
		cout << left[i];
	}
	cout << endl;
}

void cannibals::printRight() {
	for (int i = 0; i < size; i++) {
		cout << right[i];
	}
	cout << "                \\ ";
	for (int i = 0; i < 2; i++) {
		cout << boat[i];
	}
	cout << " /   ";
	for (int i = 0; i < size; i++) {
		cout << left[i];
	}
	cout << endl;
}

ostream& operator<<(ostream& ostr, const cannibals& c) {
	for (int i = 0; i < c.size; i++) {
		ostr << c.right[i];
	}
	cout << " _______ ";
	for (int i = 0; i < c.size; i++) {
		ostr << c.left[i];
	}
	return ostr;
}

istream& operator>>(istream& istr, const cannibals& c) {
	return istr >> c.expo >> c.cann;
}

