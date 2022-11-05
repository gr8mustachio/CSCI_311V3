#include<string>
#include<iostream>
using namespace std;

#include "timestamp.h"
#ifndef GRAPH_H
#define GRAPH_H

struct edge{
	int neighbor; // adjacent node
	int w; //keeps auxiliary information
	edge(){
		neighbor = 0;
		w = 0;
	};
	edge(int i, int j){
		neighbor = i;
		w = j;
	};
};

class Graph{
public:
	Graph(int N);
	void bfs(int s);
	void dfs();
	void dfsVisit(int u, int &t);
	void printGraph();
	void addEdge(int u, int v);
	void addEdge(int u, int v, int weight);

	//Problem 1
	bool sameCycle(int s, int r);
	bool isSameCycleVisit(int u, int &t, int s, int r);
	
    //Problem 2.
	int longestCycle(int s);
	
    //Problem 3
	bool twoPaths(int s, int r);
	
    //Problem 4
	bool isOnPath(int s, int r, int q);//returns true if q is on the shortest path from s to r

	// Lab
	bool isCycle();
	bool isCycleVisit(int u, int &t);
	// collect nodes on shortest path dfrom s to v after bfs on s
	void collectPath(int v, vector<int> &apath);

	// Lecture
	int evenCycle();
	int evenCycleVisit(int u, int &t);

	void printCycle(int start, int cur);

private:
	vector< vector<edge> > Adj; //adjacency lists of the graph 
	vector<int> distance; //for BFS and DFS
	vector<int> parents; //for BFS and DFS
	vector<char> colors; //for DFS
	vector<TimeStamp> stamps; //for DFS: stamps[v].d returns discovery time of v, and stamps[v].f finishing time.
    int size;
	//bool sameCycleVisit(int u, int )
	void backtrack(int r);
	bool backtrack_SC(int r, int key);
};

#endif
