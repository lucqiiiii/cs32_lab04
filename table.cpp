#include "table.h"
#include <stdio.h>
#include <sstream>
#include <iostream>

using namespace std;


Table::Table(unsigned int max_entries){
	entries = max_entries;
	capacity = 6 * max_entries + 1;
	used = 0;
	for (int i = 0; i < capacity; i++){
		Entry temp; 
		table.push_back(temp);
	}
}

Table::Table(unsigned int entries, std::istream& input){
	this -> entries = entries;
	capacity = 6 * entries + 1;
	used = 0;
	for (int i = 0; i < capacity; i++){
		Entry temp;
		table.push_back(temp);
	}
	for (int i = 0; i < entries; i++){
		Entry newe;
		input >> newe;
		put(newe);
	}
}

void Table::put(unsigned int key, std::string data){
	Entry newe;
	newe.set_key(key);
	newe.set_data(data);
	put(newe);
}

void Table::put(Entry e){
	int num = 5;
	int position = hash(e.get_key(),capacity);
	while((table[position].get_data() != "") && (table[position].get_data() != "removed")){
		if(e.get_key() == table[position].get_key()){
			table[position] = e;
			return;
		}
		position = hash(position + num*num, capacity);
		num++;
	}
	table[position] = e;
	used++;
}

string Table::get(unsigned int key) const{
	int num = 5;
	int position = hash(key,capacity);
	while(table[position].get_data() != ""){
		if(table[position].get_key() == key){
			if(table[position].get_data() == "removed"){
				return "";
			}
			else{
				return (table[position].get_data());
			}
		}
		position = hash(position + num*num, capacity);
		num++;
	}
	return "";
}

bool Table::remove(unsigned int key){
	Entry deleted(key, "removed");
	int num = 5;
	int position = hash(key,capacity);
	if(table[position].get_data() == ""){
		return false;
	}
	while(table[position].get_key() != key){
		if(table[position].get_data() == ""){
			return false;
		}
		position = hash(position + num*num, capacity);
		num++;
	}
	if(table[position].get_data() == "removed"){
		return false;
	}
	table[position] = deleted;
	used--;
	return true;
}

int Table::hash(unsigned int key, int module) const{
	return key*611953 % module;
}

ostream& operator<< (ostream& out, const Table& t){

}

void Table::printTable(){
	string result = "";
	for(int i = 0; i < entries; i++){
		result += toString(table[i]) + "\n";
	}
	cout << result << endl;
}

string Table::toString(Entry e){
	stringstream s;
	s << e;
	return s.str();
}

int Table::partition(vector<Entry> &A, int left, int right, int target){
	for(int i = left; i < right; i++){
		if(A[i] <= target){
			swap(A[i], A[left]);
			left ++;
    		}
	}
	return left - 1;
}

void Table::qsort(vector<Entry>& A, int left, int right) {
	if (left >= right) {
		return;
	}
	int middle = left + (right - left) / 2;
	swap(A[middle], A[left]);
	int midpoint = partition(A, left + 1, right, A[left]);
	swap(A[left], A[midpoint]);
	qsort(A, left, midpoint);
	qsort(A, midpoint + 1, right);
}

void Table::swap(Entry &e1, Entry &e2){
	Entry temp = e2;	
	e2 = e1;
	e1 = temp;
}

unsigned int Table::accesses = 0;
/*
void Table::mergesort(vector<Entry> &A, int size){
	int n1;
	int n2;
	if(size > 1){
		n1 = size / 2;
		n2 = size - n1;
		mergesort(A, n1);
		mergesort((A + n1), n2);

		merge(A, n1, n2);
	}
}

void Table::merge(vector<Entry> &A, int n1, int n2){
	int *temp;
	int copied = 0;
	int copied1 = 0;
	int copied2 = 0;
	int i;

	temp = new int

}*/
