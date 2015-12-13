#ifndef _FLOWGRAPH_H_
#define _FLOWGRAPH_H_

#include "FlowEdge.h"
#include "Vertex.h"

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iostream>

using namespace std;

class FlowGraph {
private:
	int EdgeCount;
	vector<vector<FlowEdge*> > flowEdges;
	vector<Vertex*> flowVertexes;

public:
	FlowGraph() {}

	int getSize();
	int getMaxCap();
	void get();
	long long pushFlow(int start, long long flow, int minG, int finish);
	long long Dinic(int start, int finish);
	void printFlow();

	void push(FlowEdge* edge);
	void relabel(int vertex);
	void initPreflow(int start);

	void discharge(int u, int start, int finish, queue<int>& q, vector<int>& used);
	long long RelabelToFront(int start, int finish);
	void Gap();
};

#include "FlowGraph.cpp"

#endif