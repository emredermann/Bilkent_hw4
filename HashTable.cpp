#include "HashTable.h"
/**
* Author: Emre Derman 
* ID: 21703508 
* Section: 1 
* Assignment: 4 
*/

#include <iostream>
using namespace std;

enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
HashTable::HashTable(const int tableSize, const CollisionStrategy option)
{
	this->tableSize = tableSize;
	arr = new int[tableSize];
	strategy = option;
	for (int i = 0; i < tableSize; i++) {
		arr[i] = NULL;
	}
	maxIteration = 0;
	dataCounter = 0;
}


HashTable::~HashTable()
{
	delete[] arr;
}


bool HashTable::insert(const int item)
{
	if (dataCounter < tableSize) {
		// classical hash function
		int itemMod = modConverter(item);

		// if there is a collison
		if (arr[itemMod] != NULL) {
			return collisionResolution(item);
		}
		else {
			// regular insertion
			arr[itemMod] = item;
			dataCounter++;
			return true;
		}
	}
	return false;
}

int HashTable::modConverter(int k){
	return  k % tableSize;
}
 
bool HashTable::collisionResolution(int item)
{
	
		// check for each strategy situation
		int modItem = modConverter(item);
		int timesCalled = 0;
		int i = 0;
		int count = 0;

			while (arr[modItem] != NULL  && count < tableSize * tableSize)  {
				if (strategy == LINEAR)
				{
					modItem = modConverter(strategyLinear(modItem));
					
				}
				if (strategy == QUADRATIC) 
				{
					modItem = modConverter(strategyQuadratic(item, timesCalled));
				}
				if (strategy == DOUBLE)
				{
					modItem = modConverter(strategyDouble(item, timesCalled));
					 
				}
				count++;
				if (count > maxIteration)
				{
					maxIteration = count;
				}
				
			}
			if (count >= 2 * tableSize) { return false; }
			else {
				arr[modItem] = item;
				cout << " inserted item " << item << endl;

				dataCounter++;
				return true;
			}
}


int HashTable::strategyLinear(int  modItem)
{
	modItem = modItem + 1;
	return modItem;
}

int HashTable::strategyDouble(int modItem, int & timesCalled)
{
	int result;
	result  = modConverter(modItem) + (timesCalled * secondHashFunc(modItem));
	timesCalled++;
	return result;
}

int HashTable::strategyQuadratic(int modItem, int & timesCalled)
{	
	int result;
	result = modConverter(modItem) + (timesCalled * timesCalled);
	timesCalled++;
	return result;
}

void HashTable::analyze(int& numSuccProbes, int& numUnsuccProbes)
{
	int load = 0;
	int Unload = 0;
	int carrier = 0;
	int Uncarrier = 0;
	int Unsuccesfullcounter = 0;
	int Succesfullcounter = 0;

	if(strategy == DOUBLE){
		// for succesfull search
			for (; carrier < tableSize; carrier++) {
				if (arr[carrier] != NULL) {
					Succesfullcounter = 1;
					int target = arr[carrier];
					int timesCalled = 0;

					while (modConverter(target) != carrier)
					{
				
						Succesfullcounter++;
						target = target + (timesCalled * secondHashFunc(arr[carrier]));
						timesCalled++;

					}
					load = Succesfullcounter + load;
				}
			}
		// for UnSuccesfull search
		numUnsuccProbes = -1;
		numSuccProbes = load / dataCounter;
	}
	if(strategy == LINEAR  ) {
		// for succesfull search
	
		for (; carrier < tableSize; carrier++) {
			if (arr[carrier] != NULL) {
				Succesfullcounter = 1;
				int target = arr[carrier];

				while(modConverter(target)  != carrier)
				{
					Succesfullcounter++;
					target++;
				}			
				load = Succesfullcounter + load;
			}
		}
	
		// for UnSuccesfull search
		for (; Uncarrier < tableSize; Uncarrier++) {
			if (arr[Uncarrier] != NULL) {
				Unsuccesfullcounter = 1;
				for (int j = Uncarrier; arr[modConverter(j)] != NULL; j++) {
					Unsuccesfullcounter++;
				}
				Unload = Unsuccesfullcounter + Unload;
			}
		}

		numSuccProbes = load / dataCounter;
		numUnsuccProbes = Unload / dataCounter;
	}

	if (strategy == QUADRATIC) {
		// for succesfull search
		for (; carrier < tableSize; carrier++) {
			if (arr[carrier] != NULL) {
				Succesfullcounter = 1;
				int target = arr[carrier];
				int timesCalled = 0;
		
				while (modConverter(target) != carrier)
				{
					Succesfullcounter++;
					target = target + (timesCalled * timesCalled);
					timesCalled++;
					
				}
				load = Succesfullcounter + load;
			}

		}
		// for UnSuccesfull search
		int counter = 0;
		for (int i = 0; i < tableSize; i++) {
			if (arr[i] != NULL) {
				counter = 0;
				int timesCalled = 0;
				for (int j = i; arr[modConverter(j)] != NULL; j = j + (timesCalled * timesCalled)) {
					counter++;
					timesCalled++;
				}
				Unload = Unload + counter;
			}
		}
		Uncarrier = Unload / dataCounter;

		numSuccProbes = load / dataCounter;
		numUnsuccProbes = Unload / dataCounter;
	}

}
	

bool HashTable::remove(const int item)
{

	int timesCalled = 0;
	int modItem = modConverter(item);
	
	int a = 0;
	bool flag = true;
	if(search(item,a)){
		while (flag) {
			if (strategy == LINEAR)
			{
				modItem = modConverter(strategyLinear(modItem));
			}
			if (strategy == QUADRATIC)
			{
				modItem = modConverter(strategyQuadratic(item, timesCalled));
			}
			if (strategy == DOUBLE)
			{
				modItem = modConverter(strategyDouble(item, timesCalled));
			
			}
			if (arr[modItem] == item)
			{
			
				arr[modItem] = NULL;
				return true;
			}
		}
	}
	cout<<"the item could not finded"<<endl;
	return false;

	
}


bool HashTable::search(const int item, int& numProbes)
{
	int modItem = modConverter(item);
	int timesCalled = 0;

	int counter = 0;
	if (arr[modItem] == item) {
		return true;
	}
	while (arr[modItem] != item && counter <= maxIteration)
	{
		if (strategy == LINEAR)
		{
			modItem = modConverter(strategyLinear(modItem));
		}
		if (strategy == QUADRATIC)
		{
			modItem = modConverter(strategyQuadratic(item, timesCalled));
		
		}
		if (strategy == DOUBLE)
		{
			modItem = modConverter(strategyDouble(item, timesCalled));
			
		}
		numProbes++;
		counter++;

	}
	if (arr[modItem] == item) {
			
			return true;
		}
		else {
			return false;
		}

}

void HashTable::display()
{
	for (int i = 0; i < tableSize; i++) {
		if (arr[i] != NULL)
			cout <<i<<" : "<< arr[i] <<endl;
		else {
			cout << i << " : " << endl;
		}
	}
}

int HashTable::secondHashFunc(int key)
{
	int reversedNum = 0, remainder;
	while (key != 0)
	{
		remainder = key % 10;
		reversedNum = reversedNum * 10 + remainder;
		key /= 10;
	}
	return reversedNum;
}
