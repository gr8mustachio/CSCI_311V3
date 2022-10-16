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


int main(int argc, char* argv[]) {
	BST dictionary;
	ifstream in;
	string x;
	int prefLen = atoi(argv[3]);
	in.open(argv[1]);
	if(!in) {
		cerr << "ERROR: can't open file " << argv[1] << endl;
		return 1;
	}
	while(in >> x){
		int len = (int)x.size();
		if(len >= prefLen) {
			string pref = x.substr(0,prefLen);
			dictionary.insert(pref, x);
		}
	}//while
	in.close(); in.clear();

	dictionary.print_inorder();
	cout << endl;
	dictionary.heightPrint();
	cout << endl;
	dictionary.printBF();
	cout << endl;
	in.open(argv[2]);
	if(!in) {
		cerr << "ERROR: could not open file " << argv[2] << endl;
		return 1;
	}
	while(in >> x) {
		dictionary.findPrint(x);
	}


	return 0;

}//main()
