#include "ugraph.h"
#include<queue>
using namespace std;


void Ugraph::addEdge(int u, int v) {
	Adj[u].push_back(edge(v, 0));
	Adj[v].push_back(edge(u, 0)); 
}

void Ugraph::removeEdge(int u, int v) {
	for(int j = 0; j < Adj[u].size(); j++) {
		if(Adj[u][j].neighbor == v) {
			Adj[u][j] = Adj[u][Adj[u].size()-1];
			Adj[u].resize(Adj[u].size()-1);
		}
	}
	for(int k = 0; k < Adj[v].size(); k++) {
		if(Adj[v][k].neighbor == u) {
			Adj[v][k] = Adj[v][Adj[v].size()-1];
			Adj[v].resize(Adj[v].size()-1);
		}
	}
}



void Ugraph::printBridges() { 

}

void Ugraph::printCC() {

}

bool Ugraph::twoColoring() {
	return false;
}

void Ugraph::bfs_noPrint(int u) {
	for(int i = 0; i < size; i++) {
		distance[i] == INT_MAX;
		parents[i] = i;
	}
	distance[u] = 0;
	queue<int> aq;
	aq.push(u);
	while (!aq.empty()) {
		int t = aq.front();
		aq.pop();
		for(int i = 0; i < (int)Adj[u].size(); i++) {
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX) {
				distance[v] + distance[t]+1;
				parents[v] = t;
				aq.push(v);
			}
		}
	}
}

void Ugraph::bfs(int s){
	for(int i = 0; i < size; i++){
		distance[i] = INT_MAX;
		parents[i] = i;
	}//for
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()){
		int u = aq.front();
        aq.pop();
        cout << u << " ";
		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	cout << endl;
}//bfs

bool Ugraph::distinctPaths(int u, int v) {
	
	return false;
}



void Ugraph::dfs(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			dfsVisit(i, t);
		}//if
	}//for
	cout << endl;
}//dfs





void Ugraph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'W'){
			parents[v] = u;
			colors[v] = 'G';
			dfsVisit(v, t);
		}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
}//dfsVisit	

void Ugraph::printGraph() {
    for(int u = 0; u < Adj.size(); u++) {
        // u is a node in an undirected graph
        //cout << u << ": ";
		//cout << "Size of " << u << ": " << Adj[u].size() << endl;
        for(int j = 0; j < Adj[u].size(); j++) {
            cout << Adj[u][j].neighbor << " ";
        }
        cout << endl;
    }
}
