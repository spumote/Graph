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
	vector<vector<FlowEdge*> > E;
	vector<Vertex*> V;

public:
	FlowGraph() {}

	int getSize();
	int getMaxCap();
	void get();
	long long pushFlow(int S, long long flow, int minG, int T);
	long long Dinic(int S, int T);
	void printFlow();

	void push(FlowEdge* e);
	void relabel(int a);
	void initPreflow(int S);

	void discharge(int u, int S, int T, queue<int>& q, vector<int>& used);
	long long RelabelToFront(int S, int T);
	void Gap();
};

#include "FlowGraph.cpp"

#endif