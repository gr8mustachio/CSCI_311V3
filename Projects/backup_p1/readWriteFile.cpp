#include<string>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

//argc = arguments count, 
//argv is an array of strings whose size equals to argc
int main(int argc, char *argv []){
        //argv[0] is always the name of executable file
        string t = "Hello ";
        string w = "world!";
        string z = t+w; //concatenation of two strings
        cout << z << endl << endl;
        string afile = argv[1];
        int x = atoi(argv[2]);
        double y = atof(argv[3]);
        string ofile = argv[4];//output file

        cout << "Total arguments: " << argc << endl;
        cout << afile << " " << x << " " << y << endl;

        //open a file to read it
        ifstream in;
        in.open(afile);
        if(!in){
            cerr << "Error: could not open the file " << afile << endl;
            return 0;
        }   
        string aline;
        while(getline(in, aline)){
            cout << aline << endl;
        }
        in.clear();
        in.close();
        
        vector<string> v;
        string aword;
        in.open(afile);
        in >> aword; // cin >> aword
        while(!in.eof()){
            v.push_back(aword);
            in >> aword;
        }
        in.clear();
        in.close();

        ofstream out;
        out.open(ofile);

        for(int i = 0; i < (int)v.size(); i++){
            out << v[i] << endl;
        }
        out.close();
        out.clear();
}












