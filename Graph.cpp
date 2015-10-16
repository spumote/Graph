#ifndef _GRAPH_CPP_
#define _GRAPH_CPP_

#include "Graph.h"

int Graph::getSize() {
	return E.size();
}

void Graph::bfs(int S) {
	int n = E.size();
	for (int i = 0; i < n; i++) {
		V[i]->setDist(INF);
	}
	V[S]->setDist(0);
	queue<int> q;
	q.push(S);

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		for (int i = 0; i < (int)E[cur].size(); i++) {
			int y = E[cur][i]->getTo();
			if (V[y]->getDist() == INF) {
				V[y]->setDist(V[cur]->getDist() + 1);
				q.push(y);
			}
		}
	}
}

Graph::Graph(const vector<vector<FlowEdge*> >& FlowE, const vector<Vertex*>& FlowV, int minG) {
	E.resize(FlowE.size());
	EdgeCount = 0;
	for (int i = 0; i < (int)FlowE.size(); i++) {
		E[i].resize(0);
		for (int j = 0; j < (int)FlowE[i].size(); j++) {
			if (FlowE[i][j]->getG() >= minG) {
				int y = FlowE[i][j]->getTo();
				E[i].push_back(new Edge(i, y, FlowE[i][j]->getId()));
				EdgeCount++;
			}
		}
	}

	V = FlowV;
}

#endif