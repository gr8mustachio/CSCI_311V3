#include<iostream>
using namespace std;

#include "bst.h"


int getHeight(Tnode *cur) {
	if(cur == NULL)
		return -1;
  	else
		return cur->height;
}

void BST::print_inorder(Tnode *cur){
	if(cur == NULL)
		return;
	print_inorder(cur->left);
	cout << "(" << cur->key << "){";
	int size = (int)(cur->value.size());
	for(int i = 0; i < size; i++) {
		cout << cur->value[i] << " ";
	}
	cout << "}" << " ";
	print_inorder(cur->right);
}//print_inorder


void BST::clean(Tnode *cur){
	if(cur == NULL)
			return;
	clean(cur->left);
	clean(cur->right);
	delete cur;
}//clean()

void BST::insert(Tnode* cur, string akey, string aval){
	if(akey < cur->key){
		if(cur->left == NULL){
			cur->left = new Tnode(akey, aval);
			return;
		}
		else {
			insert(cur->left, akey, aval);
			int hL = getHeight(cur->left);
			int hR = getHeight(cur->right);
			int maxH = (hL > hR) ? hL:hR;
			cur->height = maxH;
		}
	}//if 
	else if(akey > cur->key){
		if(cur->right == NULL){
			cur->right = new Tnode(akey, aval);
			return;
		}
		else
			insert(cur->right, akey, aval);
	}//else if
	else{
		//we found key in tree
		//add word to existing node
		//dont update height
		cur->value.push_back(aval);
	}
	int hL = getHeight(cur->left);
	int hR = getHeight(cur->right);
	int maxH = (hL > hR) ? hL : hR;
	cur->height = maxH+1;
	return;
}//insert()

void BST::findPrint(Tnode *cur, string akey) {
	if(cur == NULL)
		return;
	if(akey == cur->key) {
		for(int i = 0; i < (int)cur->value.size(); i++)
			cout << cur->value[i] << " ";
		//write for loop to print all words from vector value
		//format: word and space
		cout << endl;
	}
	else if(akey < cur->key)
		findPrint(cur->left, akey);
	else if(akey > cur->key)
		findPrint(cur->right, akey);
}

void BST::heightPrint(Tnode* cur) {
	if(root == NULL)
		cout << -1 << endl;
	if(cur == NULL)
		return;
	heightPrint(cur->left);
	cout << cur->height << " ";
	heightPrint(cur->right);
}

