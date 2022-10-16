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
int partition(const string &S, vector<int> &A, int low, int high, int pivotInd);
void quicksort(const string &S, vector<int> &A, int low, int high);
void insertion(const string &S, vector<int> &A, int low, int high);
void mergeSort(const string &S, vector<int> &A, int low, int high);
void merge(const string &S, vector<int> &A, int low, int m, int high);


int main(int argc, char *argv []) {

    // if(argc < 3){
    //     cerr << "ERROR: provide more arguments." << endl;
    //     return 1;
    // }
    // string afile = argv[1];
    // string command = argv[2];
    // string S("");
    // readFromFile(S, afile);
    // convertToLower(S);
    // vector<int> indices(S.size());
    // for(int i = 0; i < (int)S.size(); i++)
    //         indices[i] = i;
    // if(command == "QuickSort"){
    //     quicksort(S, indices, 0, S.size() - 1);
    // }else if(command == "Insertion")
    // {
    //     insertion(S, indices, 0, S.size() - 1);
    // }
    // else
    //     mergeSort(S, indices, 0, S.size() - 1);
    // for(int i = 0; i < (int)S.size(); i++)
    //         cout << indices[i] << " ";
    // cout << endl;
    // return 0;

    cout << "HELLO" << endl;
    cout << argv[0] << endl;
    if(argc < 3) {
        cerr << "ERROR: provide more arguments." << endl;
        return 1;
    }
    string afile = argv[1]; // input file name
    string command = argv[2];
    string S("");
    vector<int> indicies(S.size());
    readFromFile(S, afile);
    convertToLower(S);
    double currTime;
    for(int i = 0; i < (int)S.size(); i++)
        indicies[i] = i;
    if(command == "Quicksort") {
        auto Qstart = chrono::steady_clock::now(); // starts clock before function call
        quicksort(S, indicies, 0, S.size()-1);
        auto Qend = chrono::steady_clock::now();
        currTime = chrono::duration_cast<chrono::duration<double>>(Qend-Qstart).count();//time the algorithm took
        //cout << command << " took: " << currTime << " seconds." << endl;
    } else if(command == "Insertion") {
        auto Istart = chrono::steady_clock::now(); // starts clock before function call
        insertion(S,indicies,0,S.size()-1);
        auto Iend = chrono::steady_clock::now();
        currTime = chrono::duration_cast<chrono::duration<double>>(Iend-Istart).count();//time the algorithm took
        //cout << command << " took: " << currTime << " seconds." << endl;
    }
    else {
        auto Mstart = chrono::steady_clock::now(); // starts clock before function call
        mergeSort(S,indicies,0,S.size()-1);
        auto Mend = chrono::steady_clock::now();
        currTime = chrono::duration_cast<chrono::duration<double>>(Mend-Mstart).count();//time the algorithm took
        //cout << command << " took: " << currTime << " seconds." << endl;
    }
    return 0;
}

void readFromFile(string &S, string filename){
    ifstream in;
    if(!in) {
        cerr << "ERROR: could not open file " << filename << endl;
        return;
    }
    in.open(filename);
    string aline;
    while(getline(cin, aline)) {
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

int partition(const string &S, vector<int> &A, int low, int high, int pivotInd) {
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
            i++; j--;

        }
    }
    A[high] = A[i];
    A[i] = pivot;
    return 0; //change later
}

void quicksort(const string &S, vector<int> &A, int low, int high) {
    if(low < high) {
        int pivotIndex = partition(S, A, low, high, high);
        quicksort(S, A, low, pivotIndex-1);
        quicksort(S, A, pivotIndex + 1, high);
    }
}

void insertion(const string &S, vector<int> &A, int low, int high) {
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

void mergeSort(const string &S, vector<int> &A, int low, int high) {
    if(low==high)
        return;
    int m = (low+high) >> 1; //same as divide by 2
    mergeSort(S,A,low,m);
    mergeSort(S,A,m+1,high);
    merge(S,A,low,m,high);
}

void merge(const string &S, vector<int> &A, int low, int m, int high) {
    int leftSize = m - low + 1;
    int rightSize = high-m;
    vector<int> left(leftSize);
    vector<int> right(rightSize);
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
            A[j++] = right[r++];
    } else {
        for( ; l < leftSize; l++)
            A[j++] = left[l];
    }

}
