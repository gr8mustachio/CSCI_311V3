#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>
using namespace std;

int main(int argc, char *argv []) {
    cout << "Total arguments is " << argc << endl;
    for(int i=0; i < argc; i++) {
        cout << argv[i] << endl;
    }
    int x = atoi(argv[3]);
    double y = atof(argv[4]);
    x++;
    y = y+ 4;
    cout << x << " " << y << endl;

    //to read from a file
    string inpfile = argv[1];
    //declare input file string object
    ifstream in;
    in.open(inpfile);
    if(!in) {
        cerr << "ERROR: ciould not open file " << inpfile << endl;
        return 1;
    }
    string aline;
    cout << "Reading lines from a file" << endl; 
    while(getline(in, aline)){
        cout << aline << endl;
    }
    in.close(); in.clear();

    ofstream out;
    out.open(argv[2]);
    in.open(inpfile);
    cout << "Reading words from a file" << endl;
    string aword;
    in >> aword;
    while(!in.eof()) {
        out << aword << endl;
        in >> aword;
    }
    in.close(); in.clear();
    
    // cin >> word; //to read a word
    //getline(cin, aline); //to read an entire line
    return 0;

}