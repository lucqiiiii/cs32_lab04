//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h

#include <string>
#include "entry.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Table{

public:

	Table(unsigned int max_entries = 100);

	Table(unsigned int entries, istream& input);

	void put(unsigned int key, string data);

	void put(Entry e);

	string get(unsigned int key) const;

	bool remove(unsigned int key);

	
	void printTable();

	string toString(Entry e);

	int partition(std::vector<Entry> &A, int left, int right, int pivot);

	void qsort(std::vector<Entry> &A, int left, int right);

	void swap(Entry &e1, Entry &e2);
	
private:
	unsigned int max_entries;
	unsigned int entries;
	vector<Entry> table;
	static unsigned int accesses;
	int hash(unsigned int key, int module) const;
	unsigned int used;
	unsigned int capacity;
	
};

ostream& operator<< (ostream& out, const Table& t);

#endif /* table_h */
