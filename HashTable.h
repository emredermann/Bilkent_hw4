/**
* Author: Emre Derman
* ID: 21703508
* Section: 1
* Assignment: 4
*/

class HashTable 
{
public:
	enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
	HashTable(const int tableSize, const CollisionStrategy option);
	HashTable(const int tableSize);
	~HashTable();
	bool  insert(const int item);
	int modConverter(int k);
	bool collisionResolution(int key);
	int strategyLinear(int key);
	int strategyDouble(int key, int &);
	int strategyQuadratic(int key, int& timesCalled);

	//check each search operation also the deleted array if the item that is looking for LASTLY deleted, 
	//then check the next strategical item location. If it is also LASTLY deleted then check the next location. 
	bool  search(const int item, int& numProbes);
	
	void  display();
	int secondHashFunc(int key);
	int loadFactor();
	// open a holder array for remove... like deleted items array and 
	void  analyze(int& numSuccProbes, int& numUnsuccProbes);
	bool  remove(const int item);
 
private:
	CollisionStrategy strategy;
	int tableSize;
	int* arr;
	int dataCounter;
	int maxIteration;
};