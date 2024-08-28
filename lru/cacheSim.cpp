#include<iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

template <typename T> class cacheSim{

	struct caches{ 
		bool modify_bit;
		T tag;
	};	


		
	private:
		// user input 
		int capacity;
		int block_size;
		int assoc;

		//calculated value
		int blocks;
		int sets;
		int offset_bits;
		int index_bits;
		int tag_bits;
		int hits;
		int misses;
		vector<list<T>> cache;

	public: 
	
	cacheSim(int cap_ct,int bloc,int assoctv)
	{
		capacity = cap_ct;
		block_size = bloc;
		assoc = assoctv;
		createCache(capacity, block_size, assoc);
	}


	void createCache(int capacity,int block_size,int assoc)
	{	
		blocks 	= capacity/block_size;
		sets	= blocks/assoc;
		offset_bits = log(block_size)/log(2);
		index_bits = log(sets)/log(2);
		tag_bits = 32 - offset_bits - index_bits;
		
		hits	= 0;
		misses	= 0;
		
		cache.resize(sets);	
	}

	void readAddressesFromFile(const string& filename) 
	{
        	ifstream infile(filename);
        	string line;
        
        	while (getline(infile, line)) 
		{
            	// Assuming each line in the file contains a hexadecimal address
            		if (!line.empty()) {
                	// Convert hexadecimal string to integer
                		T address = static_cast<T>(stoul(line, nullptr, 16));
                		processAddress(address);
            		}
        	}
        
        	infile.close();
    	}


	void processAddress(T address)
	{
		int offset = address & ((1 << offset_bits) - 1);
		int index = (address >> offset_bits) & ((1 << index_bits) - 1);
		T tag = address >> (offset_bits + index_bits);

		list<T>& cacheSet = cache[index];
		typename list<T>::iterator itr = find(cacheSet.begin(), cacheSet.end() , tag);

		if (itr != cacheSet.end())
		{
			cacheSet.erase(itr);
			cacheSet.push_front(tag);
			hits++;
		}
		
		else
		{
			if (cacheSet.size() >= assoc)
				cacheSet.pop_back();

			cacheSet.push_front(tag);
			misses ++;
		}

	}


	void print()
	{
		cout << "Hits: " << hits << endl;
		cout << "misses: "<< misses << endl; 
		cout << "Miss ratio: "<< static_cast<double> (misses) / (hits + misses) << endl;
	}
};
