#include <stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

#include "priorityqueue.h"


int main(){

	
    PriorityQueue numbers;
	string command;
	while(cin >> command){//
		if(command == "getSize"){
			
			cout << "Size of the heap is " << numbers.getSize() << endl;
		}else if(command == "getCapacity"){
			cout << "Capacity of the heap is " << numbers.getCapacity() << endl;
		}else if(command == "push"){
			int akey, apr;
			cin >> akey >> apr;
			bool suc = numbers.push(akey, apr);
			if(!suc){
				cerr << "Warning: item with key " << akey << " was not enqueued." << endl;
			}
		}else if(command == "print"){
			numbers.print();
			cout << endl;
		}else if(command == "getMin"){
			Item amin = numbers.getMin();
			cout << "Min priority is " << amin.priority << " and key " << amin.key << endl;
		}
		else if(command == "pop"){
			
			numbers.pop();

		}else if(command == "updatePriority"){
			int akey, apr;
			cin >> akey >> apr;
			bool res = numbers.updatePriority(akey, apr);
			if(!res)
				cout << "Warning: could not update priority for the item with key " << akey << endl;
		}else if(command == "build"){
			int total;
			cin >> total;
			Item *temp = new Item[total];
			for(int j = 0; j < total; j++){
				int ak, apr;
				cin >> ak >> apr;
				temp[j] = Item(ak, apr);
			}
			PriorityQueue another(temp, total);
			numbers = another;
			numbers.print();
			delete [] temp;

		}else{
			cerr << "ERROR: command " << command << " is not found." << endl;
		}
	}//while

    return 0;

}//main()
