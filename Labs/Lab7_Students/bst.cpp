#include<iostream>
using namespace std;

#include "bst.h"

int BST::getHeight(Tnode *cur) {
	if(cur == NULL)
		return -1;
	else
		return cur->height;
}

void BST::updateHeight(Tnode *cur) {
	if(cur == NULL)
		return;
	int hL = getHeight(cur->left);
	int hR = getHeight(cur->right);
	int maxH = (hL > hR) ? hL : hR;
	cur->height = maxH + 1;
}

int BST::balanceFactor(Tnode *cur) {
	if(cur == NULL)
		return 0;
	return getHeight(cur->left) - getHeight(cur->right);
	// int bf = 0, hL = 0, hR = 0;
	// if(cur->left) 
	// 	hL = getHeight(cur->left);
	// if(cur->right) 
	// 	hR = getHeight(cur->right);
	// bf = hL - hR;
	// return bf;
}

void BST::printBF(Tnode *cur) {
	//same as printHeight, use balanceFactor function
	if(cur == NULL)
		return;
	printBF(cur->left);
	cout << balanceFactor(cur) << " ";
	printBF(cur->right);
}

Tnode* BST::restoreBalance(Tnode* cur, int bf) {
	if(cur == NULL)
		return cur;
	//left subtree is higher
	if(bf > 1) {
		if(balanceFactor(cur->left) >= 0) //inside case
			cur = rightRotation(cur);
		else { //outside case
			cur->left = leftRotation(cur->left);
			cur = rightRotation(cur);
		}
	} //bf = 2
	// right subtree is higher
	else if(bf < -1) {
		if(balanceFactor(cur->right) <=0) //inside case
			cur = leftRotation(cur);
		else {
			cur->right = rightRotation(cur->right); //outside case
			cur = leftRotation(cur);
		}
	}
	return cur;
}


void BST::heightPrint(Tnode *cur){
	if(cur != NULL){
		heightPrint(cur->left);
		cout << cur->height << " ";
		heightPrint(cur->right);
	}
}


void BST::findPrint(Tnode *cur, string akey){
	if(cur != NULL){
		if(cur->key == akey){
			int asize = (int)(cur->value).size();
			for(int i = 0; i < asize ; i++)
					cout << (cur->value)[i] << " ";
			cout << endl;
			return;
		}else if(akey < cur->key)
			findPrint(cur->left, akey);
		else
			findPrint(cur->right, akey);
	}
}//findPrint()



Tnode* BST::rightRotation(Tnode *cur) {
	Tnode *leftChild = cur->left;
	cur->left = cur->left->right;
	updateHeight(cur);
	leftChild->right = cur;
	updateHeight(leftChild);
	//print_inorder(root);
	return leftChild;
}


Tnode* BST::leftRotation(Tnode *cur) {
	Tnode *rightChild = cur->right;
	cur->right = cur->right->left;
	updateHeight(cur);
	rightChild->left = cur;
	updateHeight(rightChild);
	//print_inorder(root);
	return rightChild;
}

void BST::print_inorder(Tnode *cur){
	if(cur == NULL)
		return;
	print_inorder(cur->left);
	cout << "(" << cur->key << "){";
	int asize = (int)(cur->value).size();
	for(int i = 0; i < asize; i++)
		cout << (cur->value)[i] << " " ;
	cout << "} ";
	print_inorder(cur->right);
}//print_inorder


void BST::clean(Tnode *cur){
	if(cur == NULL)
			return;
	clean(cur->left);
	clean(cur->right);
	delete cur;
}//clean()


Tnode* BST::insert(Tnode *cur, string akey, string aval){
	if(akey < cur->key){
		if(cur->left == NULL){
			cur->left = new Tnode(akey, aval);
			//cout << "Inserting new node: " << aval << endl;
			//updateHeight(cur);
		}
		else {
			cur->left = insert(cur->left, akey, aval);
			int bf = balanceFactor(cur);
			if(bf > 1 || bf < -1){
				cur = restoreBalance(cur, bf);
	}
		}
	}//if 
	else if(akey > cur->key){
		if(cur->right == NULL) {
			cur->right = new Tnode(akey, aval);
			//cout << "Inserting new node: " << aval << endl;
			//updateHeight(cur);
		}
		else {
			cur->right = insert(cur->right, akey, aval);
			int bf = balanceFactor(cur);
			if(bf > 1 || bf < -1){
				cur = restoreBalance(cur, bf);
	}
		}
	}//else if
	else {
		//cout << "Inserting: " << aval << endl;
		(cur->value).push_back(aval);
	}
	// int bf = balanceFactor(cur);
	// if(bf > 1 || bf < -1){
	// 	cur = restoreBalance(cur, bf);
	// }
	updateHeight(cur);
	return cur;
}//insert()


