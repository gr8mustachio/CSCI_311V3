#include<iostream>
#include<vector>
#include<climits>
#include<set>

#include "timestamp.h"
using namespace std;

#ifndef UGRAPH_H
#define UGRAPH_H

class Ugraph {
	public:
		// step 1
		Ugraph(int N); /*{
			Adj.resize(N);
			parents.resize(N);
			for(int i = 0; i < parents.size(); i++)
				parents[i] = i;
			distance.assign(N, INT_MAX);
			colors.assign(N, 'W');
			stamps.resize(N);
			size = N;
		};*/
		void addEdge(int u, int v);
		void addEdge(int u, int v, int weight);
		void removeEdge(int u, int v);
		void bfs(int s);
		void dfs();
		void dfsVisit(int u, int &t);
		void printGraph();
		void collectPath(int v, vector<int> &apath);
		// step 2
		// problem 1
		bool distinctPaths(int u, int v); // problem 1
		void printBridges(); // problem 2
		void printCC(); // most of code is given in lecture for problem 3
		bool twoColoring(); // problem 4

		
		struct edge {
			int neighbor; // adjacent node
			int w; // keeps auxilliary information
			edge() {
				neighbor = 0;
				w = 0;
			};
			edge(int i, int j) {
				neighbor = i;
				w = j;
			};
		};
	private:
		vector<vector<edge>> Adj;
		vector<int> parents;
		vector<int> distance;
		vector<char> colors;
		vector<TimeStamp> stamps;
		int size;
		// helper functions
		// set<int> dfsDistinct(int u, int v);
		// void dfsVisit_Distinct(int u, int v, int &t, set<int> &edgeSet, bool found);
		void bfs_noPrint(int u);
		void backtrack(int r);
		void visit(int i, vector<int> &sorted); 
		void bfsDistinctPaths(int s);
		void printPath(int v);
		void printPathRec(int v);
		void findBridges(int u, vector<int> &parents, vector<int> &discovery, vector<bool> &visited, vector<int> &low);
};
#endif