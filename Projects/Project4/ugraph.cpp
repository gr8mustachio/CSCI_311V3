#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
#include "ugraph.h"
using namespace std;

Ugraph::Ugraph(int N) {
	Adj.resize(N);
	parents.resize(N);
	for(int i = 0; i < parents.size(); i++)
		parents[i] = i;
	distance.assign(N, INT_MAX);
	colors.assign(N, 'W');
	stamps.resize(N);
	size = N;
}

void Ugraph::addEdge(int u, int v) {
	Adj[u].push_back(edge(v, 0));
	Adj[v].push_back(edge(u, 0)); 
}

void Ugraph::addEdge(int u, int v, int weight) {
	Adj[u].push_back(edge(v, weight));
	Adj[v].push_back(edge(u, weight)); 
}

void Ugraph::removeEdge(int u, int v) {
	int Usize = Adj[u].size();
	for(int j = 0; j < Usize; j++) {
		if(Adj[u][j].neighbor == v) {
			Adj[u][j] = Adj[u][Usize-1];
			Adj[u].resize(Usize-1);
		}
	}
	int Vsize = Adj[v].size();
	for(int k = 0; k < Vsize; k++) {
		if(Adj[v][k].neighbor == u) {
			Adj[v][k] = Adj[v][Vsize-1];
			Adj[v].resize(Vsize-1);
		}
	}
}

bool Ugraph::distinctPaths(int u, int v) {
	bfs_noPrint(u);
	cout << "hello\n";
	int count = 0;
	vector<int> apath;
	// while(distance[r] != INT_MAX) {
	// 	bfs(u);
	// 	count++;
	// 	collectPath(u, apath);
	// 	backtrack(v);
	// }
	return false;
	if(distance[v] == INT_MAX)
		return false;
	count++;
	backtrack(v);
	bfsDistinctPaths(u);
	if(distance[v] == INT_MAX)
		return false;
	count++;
	cout << "VALUE OF COUNTER: " << count << endl;
	if(count == 2) {
		bfs_noPrint(u);
		printPath(v);
		bfsDistinctPaths(u);
		printPath(v);
		return true;
	}
	
}

void Ugraph::collectPath(int v, vector<int> &apath) {
	if(distance[v] == INT_MAX)
		return;
		if(parents[v] == v) {
			apath.push_back(v);
			return;
		}
		collectPath(parents[v], apath);
		apath.push_back(v);
}


void Ugraph::findBridges(int u, vector<int> &parents, vector<int> &discovery, vector<bool> &visited, vector<int> &soonest) {
	if(visited[u]) // if u has already been visited
		return;
	// else mark as visited and look for possible bridge
	visited[u] = true;
	static int t = 0;
	soonest[u] = discovery[u] = ++t;
	for(int i = 0; i < Adj[u].size(); i++) {
		int v = Adj[u][i].neighbor;
		if(!visited[v]) {
			parents[v] = u;
			findBridges(v, parents, discovery, visited, soonest);
			soonest[u] = min(soonest[u], soonest[v]);
			if(soonest[v] > discovery[u]) {
				cout << u << " " << v << endl;
			}
		}
		else if(v != parents[u]) {
			soonest[u] = min(soonest[u], discovery[v]);
		}
	}
}

void Ugraph::printBridges() {
	vector<bool> visited(size, false); 
	for(int i = 0; i < size; i++) {
		parents[i] = i;
	}
	vector<int> discovery(size, -1);
	vector<int> soonest(size, -1);
	for(int i = 0; i < size; i++) {
		findBridges(i, parents, discovery, visited, soonest);
	}
	return;
}

void Ugraph::printCC() {
	vector<int> sorted;
	for(int i = 0; i < size; i++) {
		parents[i] = i;
		colors[i] = 'W';
	}
	for(int j = 0; j < size; j++) {
		if(colors[j] == 'W') {
			visit(j, sorted);
			sort(sorted.begin(), sorted.end());
			for(int i = 0; i < sorted.size(); i++)
				cout << sorted[i] << " ";
			cout << endl;
			sorted.clear();
		}
	}
}

void Ugraph::visit(int i, vector<int> &sorted) {
	if(colors[i] == 'G') // if i has already been visited then return 
		return;
	colors[i] = 'G';
	sorted.push_back(i);
	for(int j = 0; j < Adj[i].size(); j++) {
		int v = Adj[i][j].neighbor;
		if(colors[v] == 'W')
			visit(v, sorted);
	}
}


bool Ugraph::twoColoring() {
	vector<int> twoColors(size, -1);
	for(int i = 0; i < size; i++) {
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[0] = 0;
	queue<int> aq;
	aq.push(0);
	while(!aq.empty()) {
		int u = aq.front();
		aq.pop();
		for(int i = 0; i < Adj[u].size(); i++) {
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX && twoColors[v] == -1) {
				twoColors[v] = 1 - twoColors[u];
				distance[v] = distance[u]+1;
				parents[v] = u;
				aq.push(v);
			}
			else if(twoColors[v] == twoColors[u])
				return false;
		}
	}
	return true;
}

void Ugraph::bfs_noPrint(int u) {
	for(int i = 0; i < size; i++) {
		distance[i] = INT_MAX;
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
				distance[v] = distance[t]+1;
				parents[v] = t;
				aq.push(v);
			}
		} // for
	} // while
} // bfsNoPrint

void Ugraph::bfsDistinctPaths(int s) {
	for(int i = 0; i < size; i++) {
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[s] = 0;
	queue<int> aq;
	aq.push(s);
	while(!aq.empty()) {
		int u = aq.front();
		aq.pop();
		for(int i = 0; i < Adj[u].size(); i++) {
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX && Adj[u][i].w != -1) {
				distance[v] = distance[u] + 1;
				parents[v] = u;
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

void Ugraph::backtrack(int r) {
	if(r == parents[r])
		return;
	else {
		int p = parents[r];
		for(int i = 0; i < Adj[p].size(); i++) {
			int n = Adj[p][i].neighbor;
			if(n == r) {
				Adj[p][i].w = -1;
				backtrack(p);
			}
		}
	}
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

void Ugraph::printPath(int v) {
  	if(distance[v] != INT_MAX) {
    	printPathRec(v);
    	cout << endl;
  	}
}

void Ugraph::printPathRec(int v) {
  	if(distance[v] == 0) {
    	cout << v << " ";
    	return;
  	}
  	printPathRec(parents[v]);
  	cout << v << " ";
}