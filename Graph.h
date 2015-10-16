#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Edge.h"
#include "Vertex.h"
#include "FlowEdge.h"

#include <vector>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

class Graph {
private:
	int EdgeCount;
	vector<vector<Edge*> > E;
	vector<Vertex*> V;

public:
	Graph() {}
	Graph(const vector<vector<FlowEdge*> >& FlowE, const vector<Vertex*>& FlowV, int minG);
	int getSize();
	void bfs(int S);
};

#include "Graph.cpp"

#endif