#include<iostream>
using namespace std;

#include "item.h"
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

class PriorityQueue{
        public:
        PriorityQueue(){
			aheap = new Item[2];
			keys = new int[2];
			size = 0;
			capacity = 2;
			totalKeys = 0;
			capacityKeys = 2;
		};
		
		//takes a pointer to an input array with Item objects and constructs a heap from it
		PriorityQueue(Item *array, int length);
		//a copy constructor: copies data members from another
		PriorityQueue(const PriorityQueue &another);  
		~PriorityQueue(){
			if(aheap){
				delete [] aheap;
				aheap = NULL;
			}
			if(keys){
				delete [] keys;
				keys = NULL;
			}
		}; //destructor of the class: deallocates space taken by the heap
		PriorityQueue& operator=(const PriorityQueue &another);

		int getCapacity() const{ return capacity; };
		int getSize() const { return size; };
		void reheapifyUp(int i);
		void reheapifyDown(int i);
		void pop();
		Item getMin();
		bool push(int akey, int apr);
		bool updatePriority(int akey, int apr);  
		void print();

		private:
		Item* aheap = NULL;
		int *keys = NULL;
		int size; //total items stored in aheap
		int capacity; //total entries in aheap array
		int totalKeys; //total keys from the start of the program, can be more than size
		int capacityKeys; //total entries of "keys" array
};

#endif
