#include "table.h"
#include <iostream>
#include <vector>
#include <iterator>
#include "entry.h"

Table::Table(unsigned int max_entries){
	this -> max_entries = max_entries;
	table = new std::vector<Entry>[max_entries];
	inserted = 0;	
}

Table::Table(unsigned int entries, std::istream& input){
	max_entries  = entries;
	table = new std::vector<Entry>[max_entries];
	int index;
	Entry e;
	for(int i = 0; i < entries; i++){
		input >> e;
		this -> put(e);
	}
}

void Table::put(unsigned int key, std::string data){
	int index = hashFunction(key);
	for(int i = 0; i < table[index].size(); i++){
		if(table[index][i].get_key() == key){
			table[index][i].set_data(data);
			return;
		}
	}
	Entry e(key, data);
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

std::string Table::get(unsigned int key) const{
	int index = hashFunction(key);
	for(std::vector<Entry>::iterator i = table[index].begin(); i < table[index].end(); i++){
		if(i -> get_key() == key){
			return i -> get_data();
		}
	}
	return "";
}

bool Table::remove(unsigned int key){
	int index = hashFunction(key);
	for(std::vector<Entry>::iterator i = table[index].begin(); i < table[index].end(); i++){
		if(i -> get_key() == key){
			table[index].erase(i);
			inserted--;
			return true;
		}
	}
	return false;
}

int Table::hashFunction(int key) const{
	return key%max_entries;
}
	
/*int Table::get_max_entries() const{
	return max_entries;
}


int Table::get_inserted() const{
	return inserted;
}

vector<Entry> Table::get_table(int i ) const{
	return table[i];
}
*/
void merge(Entry arr[], int n1, int n2){
	Entry *temp;
	int copied = 0;
	int copied1 = 0;
	int copied2 = 0;
	int i;

	temp = new Entry[n1 + n2];
	
	while((copied1 < n1) && (copied2 < n2)){
		if(arr[copied1].get_key() < ((arr + n1)[copied2].get_key()))
			temp[copied++] = arr[copied1++];
        	else
	    		temp[copied++] = (arr + n1)[copied2++];
   	}	
	while(copied1 < n1)
        	temp[copied++] = arr[copied1++];
    	while(copied2 < n2)
        	temp[copied++] = (arr + n1)[copied2++];

    	for(i = 0; i < n1 + n2; i++){
        	arr[i] = temp[i];
    	}
    	delete []temp;
}

Table::~Table(){
	delete []table;
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

/*void Table::copy(int size){
	int num = size;
	Entry* temp = new Entry[num];
	num = 0;
	for(int i = 0; i < )
}
*/
std::ostream& operator<< (std::ostream& out,const Table& t){
	Entry arr[t.inserted];//an array
	int temp = 0;
	for(int i = 0; i < t.max_entries; i++){
		for(int j = 0; j < t.table[i].size(); j++){
			arr[temp++] = t.table[i][j];
		}
	}
	mergesort(arr, t.inserted);
	for(int k = 0; k < t.inserted; k++){
		out << arr[k] << std::endl;
	}
	return out;
/*	int size = t.get_inserted();
	Entry *temp;
	temp = t.copy(size);
	mergesort(temp, t.get_inserted());
	for(int i = 0; i < t.get_inserted(); i++){
		out << temp[i] << endl;
	}
	return out;*/
}

