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


void PriorityQueue::print() {
	//Item *heapIndex = &aheap[0];
	for(int i = 0; i < size; i++) { 
		cout << aheap[i].priority << " "; //priorities of items
		// heapIndex++;
	}
	cout << endl;
	//heapIndex = &aheap[0];
	for(int i = 0; i < size; i++) { 
		cout << aheap[i].key << " "; // second line: keys of items
		//heapIndex++;
	}
	cout << endl;
	//int *keyIndex = &keys[0];
	for(int i = 0; i < totalKeys; i++) {
		// if(keys[i] == size)
		// 	cout << 0 << " ";
		// else
		cout << keys[i] << " "; // third line: indices stored in the array pointed by keys
		//keyIndex++;
	}
	cout << endl;
}

bool PriorityQueue::push(int akey, int apr) {
	//cerr << "pq.push " << akey << " " << apr << endl;
	if(akey != totalKeys)
        return false;

	//cerr << "pq size:" << size << "capacity " << capacity << endl;
	
    if(size == capacity){
        capacity *= 2;
        Item *Htemp = new Item[capacity];
        for(int i = 0; i < size; i++){
            Htemp[i] = aheap[i];
        }
        delete [] aheap;
        aheap = Htemp;
        Htemp = NULL;
    }
	//cerr << "keys size:" << totalKeys << "capacityKeys: "  << capacityKeys << endl;
	if(totalKeys == capacityKeys) { // do the same for keys: if totalKeys == capacityKeys
		capacityKeys *= 2;
		int *Ktemp = new int[capacityKeys];
		for(int i = 0; i < totalKeys; i++) {
			Ktemp[i] = keys[i];
		}
		delete [] keys;
		keys = Ktemp;
		Ktemp = NULL;
	}
	//pushing

	aheap[size] = Item(akey, apr);// insert new item at aheap[size]
	if(size == 0)
		keys[akey] = 0;
	keys[akey] = size; // and update keys at keys[akey] to size
	size++, totalKeys++; // increment size, increment totalKeys
	// cout << "Display" << endl;
	// for(int i = 0; i < size; i++) { 
	// 	cout << aheap[i].priority << " ";
	// 	// heapIndex++;
	// }
	// cout << endl;
	// //heapIndex = &aheap[0];
	// for(int i = 0; i < size; i++) { 
	// 	cout << aheap[i].key << " "; // second line: keys of items
	// 	//heapIndex++;
	// }
	//cout << endl;
	reheapifyUp(size-1); // call reheapify up
	return true;
}
void PriorityQueue::reheapifyUp(int i) {
	int parent = (i-1)/2;
	int child = i;
	if(i <= 0 || aheap[parent].priority <= aheap[child].priority)
		return;
	else if(aheap[parent].priority > aheap[child].priority) {
		//updating aheap
		//cout << "Parent: " << parent << " child: " << child << endl;
		Item temp = aheap[parent];
		aheap[parent] = aheap[child];
		aheap[child] = temp;
		//updating keys
		//cout << "Keys of parent: " << keys[parent] << " keys of child: " << keys[child] << endl;
		// cout << keys[parent] << parent << keys[child] << child << endl;
		int keyTemp = keys[aheap[parent].key];
		keys[aheap[parent].key] = keys[aheap[child].key];
		keys[aheap[child].key] = keyTemp;
		reheapifyUp(parent);
	}
}

void PriorityQueue::reheapifyDown(int i) {
	int left = 2*i+1;
	int right = 2*i+2;
	int parent = i;	
	if((left > size && right > size) || 
	(aheap[left].priority >= aheap[parent].priority && aheap[right].priority >= aheap[parent].priority)) {
		return;
	}
	if(aheap[left].priority <= aheap[right].priority) {
		if((left < size && aheap[left].priority < aheap[parent].priority)){
			// updating aheap
			Item temp = aheap[left];
			aheap[left] = aheap[parent];
			aheap[parent] = temp;
			
			// updating keys
			int keyTemp = keys[aheap[left].key];
			keys[aheap[left].key] = keys[aheap[parent].key];
			keys[aheap[parent].key] = keyTemp;
			parent = left; // swapping with left child
			reheapifyDown(left);
		}
	}
	else {
		if(right < size && aheap[right].priority < aheap[parent].priority) {
			// updating aheap
			Item temp = aheap[right];
			aheap[right] = aheap[parent];
			aheap[parent] = temp;
			// updating keys
			int keyTemp = keys[aheap[right].key];
			keys[aheap[right].key] = keys[aheap[parent].key];
			keys[aheap[parent].key] = keyTemp;
			parent = right; // swapping with right child
			reheapifyDown(right);
		}
	}
	// if(parent < i) {

	// }
}

void PriorityQueue::pop() {
	if(size == 0)
		return;
	keys[aheap[0].key] = -1; // set keys[key of the root] to -1 
	aheap[0] = aheap[size-1]; // overwrite the root with element at size-1 index
	keys[aheap[size-1].key] = 0; // swap to root
	size--; // decrement size, NOT totalKeys
	reheapifyDown(0);// call reheapify down
	//cout << "size of heap: " << size << endl;
}

Item PriorityQueue::getMin() {
	return aheap[0];
}

bool PriorityQueue::updatePriority(int akey, int apr) {
	bool found = false;
	for(int i = 0; i < size; i++) {
		if(i == akey && keys[akey] != -1) {
			found = true;
			break;
		}
		// else if(keys[akey] == -1)
		// 	return false;
	}
	//cout << "Element found? " << found << endl;
	if(found) {
		// cout << "Updating priority for key: " << aheap[keys[akey]].key << " from "
		// << aheap[keys[akey]].priority << " to: " << apr << endl;

		if(aheap[keys[akey]].priority < apr)
			return false;
		aheap[keys[akey]].priority = apr;
		reheapifyUp(keys[akey]);
		return found;

	}
	else
		return found;
}