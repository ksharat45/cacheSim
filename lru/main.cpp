// MAIN.CPP

#include<iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "cacheSim.cpp"

using namespace std;

int main (int argc, char* argv[])
{
	if (argc != 5 )
	{
		cout << "Error \n <capacity> <block_size> <associativity> <trace_file> " << endl;
		return 1;
	}

	int capacity = stoi(argv[1]);
	int block_size = stoi(argv[2]);
	int assoc = stoi(argv[3]);
	string trace_file = argv[4];

	cacheSim<int> cache(capacity, block_size, assoc);
	cache.readAddressesFromFile(trace_file);
	cache.print();


	return 0;
}
