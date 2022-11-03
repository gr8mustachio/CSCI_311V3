#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<cmath>
using namespace std;

#include "graph.h"

int main(){
	int N;
	cin >> N;

    Graph ag(N);
	string command;
	while(cin >> command){
		if(command == "addEdge"){
			int u, v;
			cin >> u >> v;
			cin.ignore();
			ag.addEdge(u, v);
		}else if(command == "printGraph"){
			ag.printGraph();
		}else if(command == "sameCycle"){
			int s, r;
			cin >> s >> r;
			cin.ignore();
			bool res = ag.sameCycle(s, r);
			if(res)
				cout << s << " and " << r << " are on the same cycle." << endl;
			else
				cout << s << " and " << r << " are not on the same cycle." << endl;
		}else if(command == "longestCycle"){
			int s;
			cin >> s;
			cin.ignore();
			int L = ag.longestCycle(s);
			cout << "The length of the longest cycle, on which " << s << " lies is " << L << endl;
		}else if(command == "twoPaths"){
			int s, r;
			cin >> s >> r;
			cin.ignore();
			bool res = ag.twoPaths(s, r);
			if(res)
				cout << "There are two distinct paths from " << s << " to " << r << "." << endl;
			else
				cout << "There are no two distinct paths from " << s << " to " << r << "." << endl;
		}else if(command == "isOnPath"){
			int s, r, q;
			cin >> s >> r >> q;
			cin.ignore();
			bool res = ag.isOnPath(s, r, q);
			if(res)
				cout << q << " is on the shortest path from " << s << " to " << r << "." << endl;
			else
				cout << q << " is not on the shortest path from " << s << " to " << r << "." << endl;
		}else{
			cerr << "ERROR: command " << command << " is not recognized." << endl;
		}
	}//while
  
  return 0;
}
