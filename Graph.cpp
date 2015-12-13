#ifndef _GRAPH_CPP_
#define _GRAPH_CPP_

#include "Graph.h"

int Graph::getSize() {
	return edges.size();
}

void Graph::bfs(int start) {
	int n = edges.size();
	for (int i = 0; i < n; i++) {
		vertexes[i]->setDist(INF);
	}
	vertexes[start]->setDist(0);
	queue<int> q;
	q.push(start);

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		for (int i = 0; i < (int)edges[cur].size(); i++) {
			int y = edges[cur][i]->getTo();
			if (vertexes[y]->getDist() == INF) {
				vertexes[y]->setDist(vertexes[cur]->getDist() + 1);
				q.push(y);
			}
		}
	}
}

Graph::Graph(const vector<vector<FlowEdge*> >& flowEdges, const vector<Vertex*>& flowVertexes, int minG) {
	edges.resize(flowEdges.size());
	EdgeCount = 0;
	for (int i = 0; i < (int)flowEdges.size(); i++) {
		edges[i].resize(0);
		for (int j = 0; j < (int)flowEdges[i].size(); j++) {
			if (flowEdges[i][j]->getRest() >= minG) {
				int y = flowEdges[i][j]->getTo();
				edges[i].push_back(new Edge(i, y, flowEdges[i][j]->getId()));
				EdgeCount++;
			}
		}
	}

	vertexes = flowVertexes;
}

#endif