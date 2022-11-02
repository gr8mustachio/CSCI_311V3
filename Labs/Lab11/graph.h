#include "timestamp.h"
#include<vector>
#include<queue>
#ifndef GRAPH_H
#define GRAPH_H

class Graph{
    public:
        Graph(); // default co nstructor
        void printGraph();
        void printNeighbors(int u); //prints neightbors of u
        // isNeighbor returns true if V is neightor of U
        bool isNeighbor(int u, int v);
        void bfs(int s); // runs bfs on graph and s
        void dfs();
        void dfsVisit(int u, int &t); // t is timestamp
        void printPath(int v); // prints path from s to v 
    private:
        vector<vector<int> > Adj; // Adjacency Lists
        vector<int> distance;
        vector<int> parents;
        vector<char> colors; // use it for DFS
        vector<TimeStamp> stamps; // use for DFS
        int size; // total nodes in the Graph class

};

#endif