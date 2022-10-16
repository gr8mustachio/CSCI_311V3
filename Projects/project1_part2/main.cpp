#include<cctype>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;

void readFromFile(string &S, string filename);
void convertToLower(string &S);
bool lessThan(const string &S, int first, int second);
int partition(const string &S, vector<double> &A, int low, int high, int pivotInd);
void quicksort(const string &S, vector<double> &A, int low, int high);
void insertion(const string &S, vector<double> &A, int low, int high);
void mergeSort(const string &S, vector<double> &A, int low, int high);
void merge(const string &S, vector<double> &A, int low, int m, int high);




int main(int argc, char *argv []) {
    if(argc < 2) {
        cerr << "ERROR: provide more arguments." << endl;
        return 1;
    }
    string afile = argv[1]; // input file name
    string S("");
    readFromFile(S, afile);
    convertToLower(S);
    //cout << S;
    vector<double> indices(S.size());
    double currTime = 0;
    for(int i = 0; i < (int)S.size(); i++)
        indices[i] = i;

    //Quicksort
    auto Qstart = chrono::steady_clock::now();
    quicksort(S, indices, 0, S.size() -1 );
    auto Qend = chrono::steady_clock::now();
    currTime = chrono::duration_cast<chrono::duration<double>>(Qend-Qstart).count(); // amount of time the algorithm took
    cout << "Length of S: " << S.size() << ". Time elapsed for quicksort: " << currTime << " seconds." << endl;
    for(int i = 0; i < (int)S.size(); i++)
        indices[i] = i;

    // Insertionsort
    auto Istart = chrono::steady_clock::now();
    insertion(S, indices, 0, S.size() - 1);
    auto Iend = chrono::steady_clock::now();
    currTime = chrono::duration_cast<chrono::duration<double>>(Iend-Istart).count(); // amount of time the algorithm took
    cout << "Length of S: " << S.size() << ". Time elapsed for insertionsort: " << currTime << " seconds." << endl;
    for(int i = 0; i < (int)S.size(); i++)
        indices[i] = i;

    
    // Mergesort
    auto Mstart = chrono::steady_clock::now();
    mergeSort(S, indices, 0, S.size() - 1);
    auto Mend = chrono::steady_clock::now();
    currTime = chrono::duration_cast<chrono::duration<double>>(Mend-Mstart).count(); // amount of time the algorithm took
    cout << "Length of S: " << S.size() << ". Time elapsed for mergesort: " << currTime << " seconds." << endl;
    cout << endl;
}

void readFromFile(string &S, string filename){
    ifstream in;
    in.open(filename);
    if(!in) {
        cerr << "ERROR: could not open file " << filename << endl;
        return;
    }
    string aline;
    while(getline(in, aline)) {
        S = S + aline;
    }
    in.close(); in.clear();
}

void convertToLower(string &S){
    int size = (int)S.size();
    for(int i = 0; i < size; i++) {
        S[i] = tolower(S[i]);
    }
}

bool lessThan(const string &S, int first, int second) {
    // return true if suffix at index "first" is smaller than at index "second"
    int size = (int)S.size();
    for( ; first < size && second < size; first++, second++) {
        if(S[first] == S[second])
            continue;
        else if(S[first] < S[second])
            return true;
        else // when S[first] > S[second]
            return false;
    }
    if(first == size)
        return true;
    return false; //change later
}

int partition(const string &S, vector<double> &A, int low, int high, int pivotInd) {
    int pivot = A[pivotInd];
    A[pivotInd] = A[high];
    A[high] = pivot;
    int i = low, j = high-1;
    while(i <= j) {
        while(i < high && lessThan(S, A[i], pivot))
            i++;
        while(j >= low && lessThan(S, pivot, A[j]))
            j--;
        if(i < j) {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;

        }
    }
    A[high] = A[i];
    A[i] = pivot;
    return i; //change later
}

void quicksort(const string &S, vector<double> &A, int low, int high) {
    if(low < high) {
        int pivotIndex = partition(S, A, low, high, high);
        quicksort(S, A, low, pivotIndex-1);
        quicksort(S, A, pivotIndex + 1, high);
    }
}

void insertion(const string &S, vector<double> &A, int low, int high) {
    int size = (int)A.size();
    for(int j = low+1; j < size; j++) {
        int key = A[j];
        int i = j - 1;
        while(i >= 0 && lessThan(S, key, A[i])){
            A[i+1] = A[i];
            i--;
        }//while
        A[i+1] = key;
    }//for
}

void mergeSort(const string &S, vector<double> &A, int low, int high) {
    if(low==high)
        return;
    int m = (low+high) >> 1; //same as divide by 2
    mergeSort(S,A,low,m);
    mergeSort(S,A,m+1,high);
    merge(S,A,low,m,high);
}

void merge(const string &S, vector<double> &A, int low, int m, int high) {
    int leftSize = m - low + 1;
    int rightSize = high-m;
    vector<double> left(leftSize);
    vector<double> right(rightSize);
    int j = 0;
    for(int i = low; i <=m; i++) 
        left[j++] = A[i];
    j = 0;
    for(int i = m+1; i <= high; i++)
        right[j++] = A[i];
    
    int l = 0,  r = 0;
    j = low;
    while(l < leftSize && r < rightSize) {
        if(lessThan(S,left[l], right[r]))
            A[j++] = left[l++];
        else
            A[j++] = right[r++];
    }
    if(l == leftSize) {
        for( ; r < rightSize; r++)
            A[j++] = right[r];
    } else if(r == rightSize) {
        for( ; l < leftSize; l++)
            A[j++] = left[l];
    }

}
