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
			return;
		}
		root = insert(root, akey, aval);
		
	};
	void print_inorder(){ print_inorder(root);
			cout << endl;
	};
	void findPrint(string akey){ findPrint(root, akey); };
	void heightPrint(){ 
		heightPrint(root); 
		cout << endl;
	};
	void printBF(){
		printBF(root);
		cout << endl;
	}
	void remove(string ak){
		root = remove(root, ak);
	};

	void printSize() { printSize(root); cout << endl; };
	string findLCA(string k1, string k2) { return findLCA(root, k1, k2); };
	void printLongestPath() { printLongestPath(root); }; 
	string findKthSmallest(int k) { return findKthSmallest(root, k); };
	void collectSubtree(string akey, vector<string> &v) { collectSubtree(root, v, akey); };

private:
	Tnode* remove(Tnode* cur, string ak);
	Tnode* getleftmost(Tnode* cur);

	void printSize(Tnode* cur);
	void printBF(Tnode *cur);
	int getHeight(Tnode *cur){
		if(cur == NULL)
			return -1;
		else
			return cur->height;
	};
		void updateHeight(Tnode *cur);
		void updateSize(Tnode* cur);
		int balanceFactor(Tnode *cur);
		Tnode* rightRotation(Tnode *cur);
		Tnode* leftRotation(Tnode *cur);
		void heightPrint(Tnode *cur);
		Tnode* insert(Tnode *cur, string akey, string aval);
		void print_inorder(Tnode *cur);
		Tnode *root = NULL;
		void clean(Tnode* cur);
		Tnode* copy(Tnode* cur);
		void findPrint(Tnode* cur, string key);
		int getSize(Tnode* cur) {
		if(cur == NULL)
			return 0;
		return cur->size;
		}
		Tnode* restoreBalance(Tnode* cur);
		string findLCA(Tnode* cur, string k1, string k2);
		void printLongestPath(Tnode* cur);
		string findKthSmallest(Tnode* cur, int k);
		void inorder_collection(Tnode* cur, vector<string> &v);
		void collectSubtree(Tnode* cur, vector<string> &v, string akey);


};


#endif
