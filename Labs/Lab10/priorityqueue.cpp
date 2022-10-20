#include<iostream>
#include<string>

using namespace std;

#include "priorityqueue.h"


PriorityQueue::PriorityQueue(Item *array, int length){ //takes a pointer to an input array with Item objects and constructs a heap from it
	if(array == NULL)
		return;
	int firstParent = (length - 2)/2;
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete [] keys;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	capacityKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = array[i];
		int ind = aheap[i].key;
		keys[ind] = i;
	}
	for(int j = firstParent; j >= 0; j--)
		reheapifyDown(j);
	
}
PriorityQueue::PriorityQueue(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	capacityKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
}
PriorityQueue& PriorityQueue::operator=(const PriorityQueue &another){
	if(aheap){
		delete [] aheap;
		aheap = NULL;
	}
	if(keys)
		delete[] keys;
	int length = another.size;
	aheap = new Item[length];
	keys = new int[length];
	size = length;
	capacity = length;
	totalKeys = length;
	capacityKeys = length;
	for(int i = 0; i < length; i++){
		aheap[i] = another.aheap[i];
		int ind = another.aheap[i].key;
		keys[ind] = i;
	}
	return *this;
}



//Implemented member functions:
bool PriorityQueue::push(int akey, int apr) {
	if(akey != totalKeys)
		return false;
	
	if(size == capacity) {
		capacity *= 2; 
		Item *temp = new Item[capacity];
		for(int i = 0; i < size; i++) {
			temp[i] = aheap[i];
		}
		delete [] aheap;
		aheap = temp;
		temp = NULL;
	}
	if(totalKeys == capacityKeys) { // do the same for keys: if totalKeys == capacityKeys
		Item *newNode = new Item(akey, apr); // add new item 
		aheap[size] = *newNode; // insert new item at aheap[size]
		keys[akey] = size; // and update keys at keys[akey] to size
	}
	size++, totalKeys++; // increment size, increment totalKeys
	reheapifyUp(size); // call reheapify up
	return true;
}

void PriorityQueue::print() {
	Item *heapIndex = &aheap[0];
	for(int i = 0; i < size; i++) { 
		cout << heapIndex->priority << " "; // first line
		heapIndex++;
	}
	cout << endl;
	heapIndex = &aheap[0];
	for(int i = 0; i < size; i++) { 
		cout << heapIndex->key << " "; // second line
		heapIndex++;
	}
	cout << endl;
	int *keyIndex = &keys[0];
	for(int i = 0; i < totalKeys; i++) {
		cout << *keyIndex << " "; // third line
		keyIndex++;
	}
	cout << endl;
}

void PriorityQueue::reheapifyUp(int i) {

}

void PriorityQueue::reheapifyDown(int i) {

}

void PriorityQueue::pop() {
	// set keys[key of the root] to -1 
	// overwrite the root with element at size-1 index
	// decrement size, NOT totalKeys
	// call reheapify down
}

Item PriorityQueue::getMin() {
	return Item();
}

bool PriorityQueue::updatePriority(int akey, int apr) {
	return false;
}