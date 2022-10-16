#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<climits>
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::cerr;

void print(const vector<int> &A){
	int size = (int)A.size();
	for(int i = 0; i < size; i++)
		cout << A[i] << " ";
	cout << endl;
}

void print(const vector<vector<int> > &P){
	int size = (int)P.size();
	for(int i = 0; i < size; i++){
		print(P[i]);
	}//for
}

void print(queue<string> &p){
	while(!p.empty()){
		string s = p.front();
		p.pop();
		cout << s << endl;
	}//while
}

int recMin(const vector<int> &A, int start, int fin);
void subarraySums(const vector<int> &A, vector<int> &B, int fin);
bool recPal(const vector<int> &A, int first, int last);
bool recFindSorted(const vector<int> &A, int k, int start, int fin);
int findIndex(const vector<int> &A, int start, int fin);
bool recFind(const vector<int> &A, int k, int start, int fin);
void powerSet(const vector<int> &A, vector< vector<int> > &P, int last);
void findPerms(const string &s, queue<string> &p, int first);

//Challenge problem
bool findInMatrix(const vector<vector<int> > &M, int uR, int uC, int lR, int lC, int k);

int main(){
	string command;
	while(cin >> command){
		if(command == "recMin"){
			int size;
			cin >> size;
			vector<int> A;
			for(int i = 0; i < size; i++)
			{	int x;
				cin >> x;
				A.push_back(x);
			}//for
			cout << "Array A: " << endl;
			print(A);
			int amin = recMin(A, 0, size - 1);
			cout << "Min of A: " << amin << endl;
		}//recMin
		else if(command == "subarraySums"){
			int size;
			cin >> size;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			vector<int> B(A.size(), 0);
			cout << "Array A:" << endl;
			print(A);
			subarraySums(A, B, size - 1);
			cout << "The sums of subarrays of A are:" << endl;
			print(B);
		}//subarraySums
		else if(command == "recPal"){
			int size;
			cin >> size;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			cout << "Array A:" << endl;
			print(A);
			bool res = recPal(A, 0, size-1);
			if(res)
				cout << "A is a palindrome." << endl;
			else
				cout << "A is NOT a palindrome." << endl;
		}//recPal
		else if(command == "recFindSorted"){
			int size, k;
			cin >> size >> k;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			cout << "Array A:" << endl;
			print(A);
			bool res = recFindSorted(A, k, 0, size - 1);
			if(res)
				cout << k << " is in A." << endl;
			else
				cout << k << " is NOT in A." << endl;
		}//recFindSorted
		else if(command == "findIndex"){
			int size;
			cin >> size ;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			cout << "Array A:" << endl;
			print(A);
			int index = findIndex(A, 0, size);
			if(index < 0 || index >= size)
				cout << "Index i such that i = A[i] is NOT found." << endl;
			else 
				cout << "Index " << index << " is equal to A[" << index << "] = " << A[index] << endl;
		}//findIndex
		else if(command == "recFind"){
			int size, k;
			cin >> size >> k ;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			cout << "Array A:" << endl;
			print(A);
			bool res = recFind(A, k, 0, size - 1);
			if(res)
				cout << k << " is found in unordered A." << endl;
			else
				cout << k << " is NOT found in unordered A." << endl;

		}//recFind
		else if(command == "powerSet"){
			int size;
			cin >> size;
			vector<int> A;
			for(int i = 0; i < size; i++){
				int x;
				cin >> x;
				A.push_back(x);
			}//for
			vector< vector<int> > P;
			cout << "Array A:" << endl;
			powerSet(A, P, size - 1);
			print(P);

		}//powerSet
		else if(command == "findPerms"){
			string s;
			cin >> s;
			queue<string> p;
			findPerms(s, p, 0);
			cout << "String s = " << s << ", all permutations of s are:" << endl;
			print(p);
		}//findPerms
		// else if(command == "findInMatrix"){
		// 	//bool findInMatrix(const vector<vector<int> > &M, int uR, int uC, int lR, int lC, int k);
		// 	int rows, cols, k, x;
		// 	cin >> rows >> cols >> k ;
		// 	vector< vector<int> > M;
		// 	for(int i = 0; i < rows; i++){
		// 		vector<int> arow;
		// 		for(int j = 0; j < cols; j++){
		// 			cin >> x;
		// 			arow.push_back(x);
		// 		}
		// 		M.push_back(arow);
		// 	}//for

		// 	bool res = findInMatrix(M, 0, 0, rows-1, cols - 1, k);
		// 	if(res)
		// 		cout << k << " is found in matrix M." << endl;
		// 	else
		// 		cout << k << " is NOT found in matrix M." << endl;
		// }//findInMatrix
		// else{
		// 	cerr << "ERROR: the command " << command << " is not valid." << endl;
		// 	exit(0);
		// }
	}//while

}//main()

int recMin(const vector<int> &A, int start, int fin) {
	if(start==fin)
		return A[start];
	else {
		int mid = (start+fin)/2;
		int Lmin = recMin(A, start, mid);
		int Rmin = recMin(A, mid+1, fin);
		if(Lmin < Rmin)
			return Lmin;
		else
			return Rmin;
	}
}

bool recFind(const vector<int> &A, int k, int start, int fin) {
	bool foundInt = false;
	if(start == fin) {
		if(A[start] == k)
			return true;
		else
			return false;
	}
	int mid = (start + fin)/2;
	bool Lfind = recFind(A, k, start, mid);
	bool Rfind = recFind(A, k, mid+1, fin);
	if(Lfind && Rfind)
		foundInt = true;
	else
		foundInt = (Lfind || Rfind);
	return foundInt;
}

void subarraySums(const vector<int> &A, vector<int> &B, int fin) {
	if(fin == 0) {
		B[0] = A[0];
		return;
	}
	else {
		subarraySums(A, B, fin-1);
		B[fin] = B[fin-1] + A[fin];
		return;
	}
}

bool recPal(const vector<int> &A, int first, int last) {
	if( A.size() <= 1 || first == last)
		return true;
	if(A[first] == A[last]) {
		if(first < last)
			return recPal(A, first+1, last-1);
		if(first > last)
			return true;
	}
	return false;
}

bool recFindSorted(const vector<int> &A, int k, int start, int fin) {
	if(start == fin) {
		if(A[start] == k)
			return true;
		else
			return false;
	}
	int mid = (start+fin)/2;
	if(k <= A[mid])
		return recFindSorted(A, k, start, mid);
	else
		return recFindSorted(A, k, mid+1, fin);
}

int findIndex(const vector<int> &A, int start, int fin) {
	if(A[start] == start)
		return A[start];
	if(A[fin] == fin)
		return A[fin];
	if(start == fin) {
		if(A[start] != start)
			return -1;
	}
	if(start != fin && start < A.size() && fin >= 0)
		return findIndex(A, start+1, fin-1);
	else
		return -1;
}


void powerSet(const vector<int> &A, vector< vector<int> > &P, int last) {
	if(last == 0) {
		vector<int> temp;
		temp.push_back(A[last]);
		P.push_back(temp);
		return;
	}
	powerSet(A,P,last-1);
	int size = P.size();
	vector<int> temp (1, A[last]);
	P.push_back(temp);
	for(int i = 0; i < size; i++) {
		vector<int> temp2 = P[i];
		temp2.push_back(A[last]);
		P.push_back(temp2);
	}
}

// void findPerms(const string &s, queue<string> &p, int first) {
// 	if(first == s[s.size()-1]) {
// 		string temp = "";
// 		temp += s[first];
// 		p.push(temp);
// 		return;
// 	}
// 	findPerms(s, p, first+1);
// 	string front = p.front();
// }

void findPerms(const string &s, queue<string> &p, int first) {
	if(first == s.size()-1) {
		string temp = "";
		temp += s[first];
		p.push(temp);
		return;
	}
	if(p.size() == 0)
		p.push(s);
	findPerms(s,p,first+1); //2
	// cout << "Q.size() = " << p.size() << endl;
	int size = p.size();
	char ch = s[first]; //a
	for(int i = 0; i < size; i++) {
		string fStr = p.front();
		for(int j = 0; j < fStr.size(); j++) {
			// front += ch;
			fStr[j] = ch;
		}
		string newPerm = fStr;
		cout << "fstr: " << fStr << " " << p.front() << endl;
		p.pop();
		p.push(newPerm);
	}
	

}

