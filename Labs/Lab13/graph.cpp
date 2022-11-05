#include<climits>
#include<algorithm>
#include<queue>
#include<math.h>
#include<vector>
#include<iostream>
#include<string>
#include<utility>
using namespace std;

#include "graph.h"

Graph::Graph(int N){

	size = N;
	
	Adj.resize(size);
	distance.resize(size);
	parents.resize(size);
	colors.resize(size);
	stamps.resize(size);

}//default

void Graph::addEdge(int u, int v){
	Adj[u].push_back(edge(v, 0));
}

void Graph::addEdge(int u, int v, int weight){
	Adj[u].push_back(edge(v, weight));
}

void Graph::printGraph(){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < (int)Adj[i].size(); j++){
			int v = Adj[i][j].neighbor;
			cout << v << " " ;
		}//for j
		cout << endl;
	}
}//printGraph

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

		for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
			}
		}//for
	}//while

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

}//dfs

void Graph::dfsVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

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



// isCycle
bool Graph::isCycle(){
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;

	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			bool res = isCycleVisit(i, t);
			if(res)
				return true;
		}//if
	}//for
	return false;
}//dfs

bool Graph::isCycleVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				bool res = isCycleVisit(v, t);
				if(res)
					return true;
				// else keep looking for a cycle via next neighbor
			}
			else if(colors[v] == 'G') {
				return true; // a cycle has been found
			}
			else if(colors[v] == 'B') {

			} // do nothing
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
	return false;
}//isCycleVisit	

bool Graph::isSameCycleVisit(int u, int &t, int s, int r){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				bool res = isSameCycleVisit(v, t, s, r);
				if(res)
					return true;
				// else keep looking for a cycle via next neighbor
			}
			else if(colors[v] == 'G' && v == s) {
				backtrack(v);
				return true; // a cycle has been found with s
			}
			else if(colors[v] == 'B') {

			} // do nothing
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
	return false;
}//isCycleVisit	

void Graph::backtrack(int r) {
	if(r == parents[r])
		return;
	else {
		int p = parents[r];
		for(int i = 0; i < Adj[p].size(); i++) {
			int n = Adj[r][i].neighbor;
			if(n == r) {
				Adj[p][i].w = -1;
				backtrack(p);
			}
		}
	}
}

bool Graph::backtrack_SC(int r, int key) {
	if(r == parents[r] && r != key)
		return false;
	else if (r == parents[r] && r == key)
		return true;
	else {
		int p = parents[r];
		for(int i = 0; i < Adj[p].size(); i++) {
			int n = Adj[r][i].neighbor;
			if(n == r) {
				Adj[p][i].w = -1;
				return backtrack_SC(p, key);
			}
		}
	}
}

bool Graph::sameCycle(int s, int r) {
	for(int i = 0; i < size; i++){
		parents[i] = i;
		colors[i] = 'W';
	}	
	int t = 0;
	if(!isCycle())
		return false;
	
	for(int i = 0; i < Adj[s].size(); i++) {
		if(colors[i] == 'W'){
			//color[i] = 'G';
			bool res = isSameCycleVisit(i, t, s, r);
			if(res) {
				cout << "s is: " << s << " and r is:" << r << endl;
				cout << "vertex " << i << " has color " << colors[i] << endl;
				backtrack(i);

			} // if there is a cycle
		}//if
	}//for

	// for(int i = 0; i < Adj[s].size(); i++) {
	// 	int v = Adj[s][i].neighbor;

	// }
	return false;	
}

void Graph::collectPath(int v, vector<int> &apath) {
	if(distance[v] == INT_MAX)
		return;
		if(parents[v] == v) {
			apath.push_back(v);
			return;
		}
		collectPath(parents[v], apath);
		apath.push_back(v);
}

//even cycle
int Graph::evenCycle() {
	for(int i = 0; i < size; i++){
	parents[i] = i;
	colors[i] = 'W';
	distance[i] = -1;
	}	
	int t = 0;
	int res  = -1;
	for(int i = 0; i < size; i++){
		if(colors[i] == 'W'){
			//color[i] = 'G';
			distance[i] = 0;
			res =  evenCycleVisit(i, t);
			if(res > 0)
				break;
		}//if
	}//for
	return res;
}

int Graph::evenCycleVisit(int u, int &t){
	colors[u] = 'G';
	stamps[u].d = t;
	t++;

	for(int i = 0; i < (int)Adj[u].size(); i++){
			int v = Adj[u][i].neighbor;
			if(colors[v] == 'W'){
				parents[v] = u;
				colors[v] = 'G';
				distance[v] = distance[u] + 1;
				int res = evenCycleVisit(v, t);
				if(res > 0)
					return res;
			}
			else if(colors[v] == 'G') {
				int length = distance[u] - distance[v] + 1;
				if(length % 2 == 0) {
					printCycle(v, u);
					cout << v << endl;
					return length;
				}
			}
	}//for
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
	return -1;
}//dfsVisit	

void Graph::printCycle(int start, int cur) {
	if(cur == start) {
		cout << cur << " ";
		return;
	}
	printCycle(start, parents[cur]);
	cout << cur << " ";
}