#include<iostream>
#include "graph.h"
using namespace std;

Graph::Graph() {
    int N, M;
    cin >> N >> M;
    Adj.resize(N);
    distance.resize(N);
    colors.resize(N);
    parents.resize(N);
    stamps.resize(N);
    for(int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        Adj[u].push_back(v); // add v to adjacency list of u

    }
    size = N;

}

void Graph::printGraph() {
    for(int u = 0; u < size; u++) {
        // u is a node in a graph
        cout << u << " ";
        for(int j = 0; j < (int)Adj.at(u).size(); j++) {
            int v = Adj.at(u).at(j); // v is neighbor of u, j is index not neighbor
            cout << v << " ";
        } // for
        cout << endl;
    }
}


void Graph::bfs(int s){
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
			int v = Adj[u][i];
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while
	cout << endl;
}//bfs

void Graph::dfs(){
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

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;
	cout << u << " ";
	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i];
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

void Graph::printPath(int v) {
    if(distance[v] == INT_MAX) // no path from s to v
        return; // v is not reachable from s
    if(parents[v] == v) {
        cout << v << " ";
        return;
    }
    printPath(parents[v]);
    cout << v << " ";
}

void Graph::printNeighbors(int u) {

}

bool Graph::isNeighbor(int u, int v) {
    return false;
}