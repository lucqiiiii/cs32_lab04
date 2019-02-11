//
//  table.h
//  W19 - Lab04
//
#ifndef table_h
#define table_h

#include "entry.h"
#include <vector>

class Table{

public:

	Table(unsigned int max_entries = 100);

	Table(unsigned int entries, std::istream& input);

	void put(unsigned int key, std::string data);

	void put(Entry e);

	std::string get(unsigned int key) const;

//	int get_inserted() const;

//	int get_max_entries() const;

	bool remove(unsigned int key);

	//void mergesort(Entry temp[], int n);

	//void merge(Entry temp[], int n1, int n2);		
	

private:
	unsigned int max_entries;
	std::vector<Entry>* table;
	int hashFunction(unsigned int key) const;
	int inserted; // size	
};

std::ostream& operator << (std::ostream& out, const Table& t);

#endif /* table_h */
