#include <stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

#include "bst.h"

//look at main.cpp in Lab6/

int main(int argc, char* argv[]){

	ifstream in;
	in.open(argv[1]);

    BST numbers;
	string x;
	in >> x;
	int len = atoi(argv[3]);
    while(!in.eof()){
		if((int)x.length() >= len){
			numbers.insert(x.substr(0,len), x);
			//cout << x << endl;
		}
		in >> x;
    }//while
	in.close(); in.clear();

	numbers.print_inorder();
	cout <<  endl;
	numbers.heightPrint();
	cout <<  endl;
    numbers.printBF();
    cout  << endl;
	in.open(argv[2]); 
	in >> x;
	while(!in.eof()){
		numbers.findPrint(x);
		in >> x;
	}
	in.close(); in.clear();

    return 0;

}//main()
