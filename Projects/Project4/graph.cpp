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

bool Graph::twoPaths(int s, int r) {
	bool foundPath = false;
	//int numOfPaths = 0;
	for(int i = 0; i < size; i++){
    	distance[i] = INT_MAX;
    	parents[i] = i;
  	}//for
 	distance[s] = 0;
  	queue<int> aq;
  	aq.push(s);
  	while(!aq.empty()){
    	int u = aq.front();
    //cout << u << " " ; 
    	aq.pop();

    	for(int i = 0; i < (int)Adj[u].size(); i++){
      		int v = Adj[u][i].neighbor;
      		if(distance[v] == INT_MAX){
				distance[v] = distance[u] + 1;
				parents[v] = u;
				aq.push(v);
				if(v == r)
					break;
      		}
    	}//for
  	}//while
	if(distance[r] == INT_MAX) // if r is unreachable
		return false;
	else {
		backtrack(r);
		foundPath = true;
	}
	// second BFS run
	for(int i = 0; i < size; i++) {
		distance[i] = INT_MAX;
		parents[i] = i;
	}
	distance[s] = 0;
	// clear queue of past bfs
	for(int i = 0; i < aq.size(); i++)
		aq.pop();
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
	if(distance[r] != INT_MAX && foundPath)
		return true;
	else
		return false;
	//return false;
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
				return backtrack_SC(v, r);  // a cycle has been found with s
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
			int n = Adj[p][i].neighbor;
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
			if(n == r && n != key) {
				Adj[p][i].w = -1;
				return backtrack_SC(p, key);
			}
			else if(n == r && n == key) {
				Adj[p][i].w = -1;
				return true;
			}
		}
		return false;
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
				// cout << "s is: " << s << " and r is:" << r << endl;
				// cout << "vertex " << i << " has color " << colors[i] << endl;
				return true;

			} // if there is a cycle
		}//if
	}//for

	// for(int i = 0; i < Adj[s].size(); i++) {
	// 	int v = Adj[s][i].neighbor;

	// }
	return false;	
}

int Graph::longestCycle(int s) {
	int curMaxLen = -1;
	int dist = 0;
	for(int i = 0; i < size; i++) {
		parents[i] = i;
		colors[i] = 'W';
		distance[i] = 0;
	}
	int t = 0;
	longestCycleVisit(s, t, dist, curMaxLen);
	if(curMaxLen == -1)
		return 0;
	return curMaxLen;
}

void Graph::longestCycleVisit(int u, int &t, int &dist, int &curMax) {
	//int cur;
	colors[u] = 'G';
	stamps[u].d = t;
	distance[u] = dist;
	t++;

	for(int i = 0; i < Adj[u].size(); i++) {
		int v = Adj[u][i].neighbor;
		if(colors[v] == 'G') {
			int len = distance[u]+1;
			if(parents[v] == v) {
				if(len > curMax)
					curMax = len;
			}
		}
		else if(colors[v] == 'W')
		{
			distance[v] = distance[u]+1;
			dist = distance[u]+1;
			parents[v] = u;
			colors[v] = 'G';
			longestCycleVisit(v, t, dist, curMax);
		}
	}
	colors[u] = 'B';
	stamps[u].f = t;
	t++;
} // longestCycleVisit

bool Graph::isOnPath(int s, int r, int q) {
	int curMinLen = INT_MAX;
	int distance = 0;
	bool qOnPath = false;
	bfs(s);
	int temp = r;
	while(parents[temp] != temp) {
		if(parents[temp] == q)
			return true;
		else
			temp = parents[temp];
	}
	if(r == q)
		return true;
	else
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

// Graph::printMySources(int v) {
// 	for(int i = 0; i < )
// }