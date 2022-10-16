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


int main(){

    BST dictionary;
	string command;
    while(cin >> command){
        if(command == "print_inorder"){
            dictionary.print_inorder();
            cout << endl;
        }else if(command == "heightPrint"){
            dictionary.heightPrint();
            cout << endl;
        }
        else if(command == "printBF"){
            dictionary.printBF();
            cout << endl;
        }
        else if(command == "findPrint"){
            string akey;
            cin >> akey;
            dictionary.findPrint(akey);
        }
        else if(command == "insert"){
            string word;
            int len;
            cin >> word >> len;
            string pref = word.substr(0, len);
            dictionary.insert(pref, word);
        }
        else if(command == "remove"){
            string akey;
            cin >> akey;
            dictionary.remove(akey);
        }
        else{
            cerr << "ERROR: command " << command << " is not found." << endl;
        }
    }//while

    return 0;

}//main()