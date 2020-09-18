#include "HashTable.h"
#include<iostream>
#include <fstream>
#include <string>
/**
* Author: Emre Derman
* ID: 21703508
* Section: 1
* Assignment: 4
*/
using namespace std;

int main(int argc, char* argv[]) {
	char operationType;
	int item;
	ifstream input;
	input.open(argv[1]);


	HashTable t(5, HashTable::CollisionStrategy::QUADRATIC);
	int i = 9;

	while (i > 0) {


		input >> operationType;
		input >> item;

		if (operationType == 'I') {
			if (t.insert(item)) {
				cout << item << " inserted " << endl;
			}
			else {
				cout << item << " not inserted " << endl;
			}
		}

			if (operationType == 'R')
			{
				if (t.remove(item)) {
					cout << item << " removed " << endl;
				}
				else {
					cout << item << " not removed " << endl;
				}
			}

			if (operationType == 'S')	
			{

				int numProbes = 0;
				if (t.search(item, numProbes)) {
					cout << item << " searched and numProbes " << numProbes << endl;
				}
				else {
					cout << item << " not searched " << endl;
				}
			}
			i--;
		}

		t.display();
		 
		int numSucc = 0;
		int numUnsuc = 0;
		t.analyze(numSucc, numUnsuc);
		
		cout << " numSuccesfull : " << numSucc << endl;
		cout << " num Unsuccesfull : " << numUnsuc << endl;
	}
