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
	vector<vector<Edge*> > edges;
	vector<Vertex*> vertexes;

public:
	Graph() {}
	Graph(const vector<vector<FlowEdge*> >& flowEdges, const vector<Vertex*>& flowVertexes, int minG);
	int getSize();
	void bfs(int start);
};

#include "Graph.cpp"

#endif