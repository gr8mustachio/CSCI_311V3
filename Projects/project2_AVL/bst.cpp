#include<iostream>
using namespace std;

#include "bst.h"


// string BST::findLCA(Tnode* cur, string k1, string k2) {
// 	if(cur) {
// 		if(cur->key > k1 && cur->key > k2)
// 			string left = findLCA(cur->left, k1, k2);
// 		else if (cur->key < k1 && cur->key < k2)
// 			string right = findLCA(cur->right, k1, k2);
// 		else
// 			return cur->key;
// 	}
// 	return "";
// }
string BST::findLCA(Tnode* cur, string k1, string k2) {

  if(cur != NULL) {
	if(cur->key > k1 && cur->key > k2)
		return findLCA(cur->left, k1, k2);
	else if(cur->key < k1 && cur->key < k2)
		return findLCA(cur->right, k1, k2);
	else
		return cur->key;
  }
  else
		return "";
}

void BST::printLongestPath(Tnode* cur) {
	if(getHeight(cur->left) == -1 && getHeight(cur->right) == -1) {
		if(cur->left == NULL && cur->right == NULL) {
			cout << cur->key << " ";
			return;
		}
	}
	else {
		cout << cur->key << " ";
		if(getHeight(cur->left) >= getHeight(cur->right))
			printLongestPath(cur->left);
		else
			printLongestPath(cur->right);
	}
}

string BST::findKthSmallest(Tnode* cur, int k) {
	//works
	vector<string> v;
	inorder_collection(root, v);
	for(int i = 0; i < v.size(); i++) {
		//cout << v[i] << " ";
		if(i == k-1)
			return v[i];
	}
	return "";
	/* old code that doesnt work:
	if(cur == NULL)
		return "";
	int lSize = getSize(root->left);
	if(lSize+1 == k) //lSize+1th spot in the tree is the root position
		return root->key;
	else if(lSize+1 > k)
		return findKthSmallest(cur->left, k);
	else
		return findKthSmallest(cur->right, k-(lSize+1));
	return "";
	*/
}		

/* findKthSmallest old code:
	;*/



Tnode* BST::restoreBalance(Tnode* cur){
	if(cur == NULL)
		return cur;
	int bf = balanceFactor(cur);
	if(bf > 1){//left subtree is higher
		if(balanceFactor(cur->left) >= 0){
			cur = rightRotation(cur);//height is updated
		}//outside case
		else{
			cur->left = leftRotation(cur->left);
			cur = rightRotation(cur);
		}//inside case
	}//bf = 2
	else if(bf < -1){
		if(balanceFactor(cur->right) <= 0){
			cur = leftRotation(cur);
		}//outside case
		else{
			cur->right = rightRotation(cur->right);
			cur = leftRotation(cur);
		}
	}//if bf = -2
	return cur;
}



void BST::updateSize(Tnode* cur) {
	if(cur == NULL)
		return;
	cur->size = getSize(cur->left) + getSize(cur->right) + 1;
}


Tnode* BST::remove(Tnode* cur, string ak){
	if(cur == NULL)
		return NULL;
	if(ak < cur->key){
		cur->left = remove(cur->left, ak);
		updateHeight(cur);
		updateSize(cur);						
	}else if(ak > cur->key){
		cur->right = remove(cur->right, ak);
		updateHeight(cur);
		updateSize(cur);	
	}else{//found the key
		if(cur->left == NULL){
			Tnode* temp = cur->right;
			delete cur;
			return temp;
		}else if(cur->right == NULL){
			Tnode* temp = cur->left;
			delete cur;
			return temp;
		}else{
			Tnode *leftMost = getleftmost(cur->right);
			cur->key = leftMost->key;
			cur->value = leftMost->value;
			cur->right = remove(cur->right, leftMost->key);
			updateHeight(cur);
			updateSize(cur);	
		}//two children
	
	}//found key
	int bf = balanceFactor(cur);
	if(bf > 1 || bf < -1){//left subtree is higher
		cur = restoreBalance(cur);
	}//if bf = -2
	updateHeight(cur);
	updateSize(cur);
	return cur;
}//remove

Tnode* BST::getleftmost(Tnode* cur){
	if(cur == NULL)
		return NULL;
	if(cur->left == NULL)
		return cur;
	return getleftmost(cur->left);
}//getleftmost

void BST::printBF(Tnode *cur){
	if(cur != NULL){
		printBF(cur->left);
		int bf = balanceFactor(cur);
		cout << bf << " " ;
		printBF(cur->right);
	}//if
}//printBF

void BST::updateHeight(Tnode *cur){
	if(cur == NULL)
		return;
	int hl = getHeight(cur->left);
	int hr = getHeight(cur->right);
	cur->height = (hl > hr) ? (hl + 1) : (hr + 1);

}//updateHeight
				
int BST::balanceFactor(Tnode *cur){
	if(cur == NULL)
		return 0;
	
	return getHeight(cur->left) - getHeight(cur->right);
}
				
Tnode* BST::rightRotation(Tnode *cur){
	Tnode *L = cur->left;
	cur->left = L->right;
	updateHeight(cur);
	updateSize(cur);
	L->right = cur;
	updateHeight(L);
	updateSize(L);
	return L;
}

Tnode* BST::leftRotation(Tnode *cur){
	Tnode *R = cur->right;
	cur->right = R->left;
	updateHeight(cur);
	updateSize(cur);
	R->left = cur;
	updateHeight(R);
	updateSize(R);
	return R;
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

void BST::printSize(Tnode* cur){
	if(cur != NULL){
		printSize(cur->left);
		cout << cur->size << " ";
		printSize(cur->right);
	}
}

void BST::collectSubtree(Tnode* cur, vector<string> &v, string akey){
	if(cur == NULL)
		return;
	if(cur->key == akey)
		inorder_collection(cur, v);
	collectSubtree(cur->left, v, akey);
	collectSubtree(cur->right, v, akey); 
}

void BST::inorder_collection(Tnode* cur, vector<string> &v) {
	if(cur == NULL)
		return;
	inorder_collection(cur->left, v);
	v.push_back(cur->key);
	inorder_collection(cur->right, v);
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
			}//if found place
		else{
			cur->left = insert(cur->left, akey, aval);
				
		}//else
	}//if 
	else if(akey > cur->key){
		if(cur->right == NULL){
			cur->right = new Tnode(akey, aval);
			updateHeight(cur);
		}
		else{
			cur->right = insert(cur->right, akey, aval);						
		}
	}//else if
	else{
		(cur->value).push_back(aval);
	}
	int bf = balanceFactor(cur);
	if(bf > 1 || bf < -1){//left subtree is higher
		cur = restoreBalance(cur);
	}//if bf = -2
	updateSize(cur);
	updateHeight(cur);
	return cur;
}//insert()

