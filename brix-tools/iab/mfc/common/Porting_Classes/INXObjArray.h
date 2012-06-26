#pragma once

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class INXObjArray:public vector<T>{
public:
	// add object to a vector
	void Add(T obj){
		push_back(obj);
	};
	// get object from a vector
	T GetAt(unsigned int index){
		return at(index);
	};
	int GetCount(){
		return size();
	};
	int GetUpperBound(){
		return (int)size() - 1;	
	};
	int GetSize(){
		return size();
	};
	void InsertAt(unsigned int index, T obj){
		insert(begin() + index, obj);
	};
	bool IsEmpty(){
		return empty();
	};
	void SetAt(unsigned int index, T obj){
		at(index) = obj;
	};
	void SetAtGrow(unsigned int index,T obj){
		if(GetUpperBound() < (int)index){
			// resize it
			resize(index + 1);
			// add the item
			at(index) = obj;
		}else at(index) = obj;	
	};
	void RemoveAt(unsigned int index){
		erase(begin() + index);
	};
	void RemoveAll(){
		erase(begin(), end());
	};
};