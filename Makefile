
simulator_Q1: main.o HashTable.o 
	g++ main.o HashTable.o  -o simulator_Q1 -std=c++11
	
main.o: main.cpp
	g++ -c main.cpp -std=c++11

HashTable.o: HashTable.cpp
	g++ -c HashTable.cpp

	
clean:
	rm *.o simulator_Q1