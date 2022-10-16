#include<iostream>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H

class BST{
	public:
		BST():  root(NULL) {};
		~BST(){ clean(root); root = NULL; };

		void insert(string akey, string aval){ 
			if(root == NULL){
				root = new Tnode(akey, aval);
			}else
				insert(root, akey, aval); 
		};
		void print_inorder(){ print_inorder(root);
			cout << endl;
		};
		void heightPrint() {
			heightPrint(root);
		};
		void findPrint(string akey) {
			findPrint(root, akey);
		};
	private:
		void findPrint(Tnode *cur, string akey);
		void heightPrint(Tnode* cur);
		void insert(Tnode* cur, string akey, string aval);
		void print_inorder(Tnode *cur);
		Tnode *root = NULL;
		void clean(Tnode* cur);
};


#endif
