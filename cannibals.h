//Author: Aashima Mehta
//header file
#pragma once
#ifndef CANNIBALS_H
#define CANNIBALS_H
#include <iostream>  
#include <fstream>
#include <string>
using namespace std;

class cannibals {
private:
	int option;
	string const empty = "-";      //didn't used anywhere
	int size;                      //total length of the array
	int cann;                      //number of cann
	int expo;                      //number of expo
	string *right;                 //right side array which should be full in the beginning
	string *left;                  //left side array which should be empty in the beginning
	string* boat;

public:
	//CONSTRUCTOR
	cannibals();
	cannibals(int n);
	cannibals(int c, int e);

	//Accessor to get a value from a particular index in the array
	string getRight(int n) const;
	string getLeft(int n) const;
	string getBoat(int n) const;
	int getSize() const;

	//Mutator -- to change the value on a particular index in the array
	void setRight(string n, int index);
	void setLeft(string n, int index);
	void setBoat(string n, int index);

	//Accessors for the number of Explorers and Cannibles on left and right side of the river bank.
	int getExpoRight() const;
	int getExpoLeft() const;
	int getCanRight() const;
	int getCanLeft() const;


	//isSolved -- checks if the explorers are safe
	bool isSolved();

	//isKilled --- checks if the explorers might get killed 
	bool isKilled();


	//safe() -- to solve the problem of taking all the explorers and cannibals safely to the other side of the bank
	bool safe();

	//extra method
	//void print(string word);
	void printRight();
	void printLeft();
	void print();

	//OSTREAM
	friend ostream& operator<<(ostream& ostr, const cannibals& c);
	friend istream& operator>>(istream& istr, const cannibals& c);
};

#endif