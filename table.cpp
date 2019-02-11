#include "table.h"
#include <iostream>
#include <vector>
using namespace std;

Table::Table(unsigned int max_entries){
	this -> max_entries = max_entries;
	table = new vector<Entry>[max_entries];
	inserted = 0;	
}

Table::Table(unsigned int entries, std::istream& input){
	max_entries  = entries;
	table = new vector<Entry>[max_entries];
	int index;
	Entry e;
	for(int i = 0; i < max_entries; i++){
		input >> e;
		this -> put(e);
	}
}

void Table::put(unsigned int key, std::string data){
	int index = hashFunction(key);
	int i;
	for(i = 0; i < table[index].size(); i++){
		if(table[index][i].get_key() == key){
			table[index][i].set_data(data);
			return;
		}
	}
	Entry e (key, data);
	table[index].push_back(e);
	inserted++;
}

void Table::put(Entry e){
	int index = hashFunction(e.get_key());
	for(int i = 0; i < table[index].size(); i++){
		if(table[index][i].get_key() == e.get_key()){
			table[index][i].set_data(e.get_data());
			return;
		}
	}
	table[index].push_back(e);
	inserted++;
}

string Table::get(unsigned int key) const{
	int index = hashFunction(key);
	for(vector<Entry>::iterator i = table[index].begin(); i < table[index].end(); i++){
		if(i -> get_key() == key){
			return i -> get_data();
		}
	}
	return "";
}

bool Table::remove(unsigned int key){
	int index = hashFunction(key);
	for(vector<Entry>::iterator i = table[index].begin(); i < table[index].end(); i++){
		if(i -> get_key() == key){
			table[index].erase(i);
			inserted--;
			return true;
		}
	}
	return false;
}

int Table::hashFunction(unsigned int key) const{
	return key % max_entries;
}
	
int Table::get_max_entries() const{
	return max_entries;
}


int Table::get_inserted() const{
	return inserted;
}

vector<Entry> Table::get_table(int i ) const{
	return table[i];
}

void merge(Entry data[], int n1, int n2){
	Entry *temp;
	int copied = 0;
	int copied1 = 0;
	int copied2 = 0;
	int i;

	temp = new Entry[n1 + n2];
	
	while((copied1 < n1) && (copied2 < n2)){
		if(data[copied1].get_key() < (data + n1)[copied2].get_key())
			temp[copied++] = data[copied1++];
        	else
	    		temp[copied++] = (data + n1)[copied2++];
   	}	
	while(copied1 < n1)
        	temp[copied++] = data[copied1++];
    	while(copied2 < n2)
        	temp[copied++] = (data + n1)[copied2++];

    	for(i = 0; i < n1 + n2; i++){
        	data[i] = temp[i];
    	}
    	delete [] temp;
}

void mergesort(Entry temp[], int size){
	int n1;
	int n2;
	if(size > 1){
		n1 = size / 2;
		n2 = size - n1;
		mergesort(temp, n1);
		mergesort((temp + n1), n2);
		merge(temp, n1, n2);
	}
}

std::ostream& operator << (std::ostream& out,const Table& t){
	Entry temp[t.get_inserted()];//an array
	int index = 0;
	for(int i = 0; i < t.get_max_entries(); i++){
		for(int j = 0; j < t.get_table(i).size(); j++){
			temp[index++] = (t.get_table(i))[j];
		}
	}
	mergesort(temp, t.get_inserted());
	for(int k = 0; k < t.get_inserted(); k++){
		out << temp[k] << endl;
	}
	return out;
}

