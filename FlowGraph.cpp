#ifndef _FLOWGRAPH_CPP_
#define _FLOWGRAPH_CPP_

#include "FlowGraph.h"

int FlowGraph::getSize() {
	return flowEdges.size();
}

int FlowGraph::getMaxCap() {
	int ans = 0;
	for (int i = 0; i < (int)flowEdges.size(); i++) {
		for (int j = 0; j < (int)flowEdges[i].size(); j++) {
			ans = max(ans, flowEdges[i][j]->getFlow() + flowEdges[i][j]->getRest());
		}
	}
	return ans;	
}

void FlowGraph::get() {
	int n, m;
	cin >> n >> m;
	EdgeCount = m;
	flowEdges.resize(n);
	flowVertexes.resize(n);
	for (int i = 0; i < n; i++) {
		flowVertexes[i] = new Vertex();
	}

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;


		flowEdges[a].push_back(new FlowEdge(a, b, i + 1, 0, c, NULL));
		flowEdges[b].push_back(new FlowEdge(b, a, 0, 0, 0, flowEdges[a][ flowEdges[a].size() - 1 ]));
		flowEdges[a][flowEdges[a].size() - 1]->setreversedEdge(flowEdges[b][ flowEdges[b].size() - 1 ]);
	}	
}

long long FlowGraph::pushFlow(int x, long long flow, int minG, int finish) {
	if (x == finish) {
		return flow;
	}
	long long oldflow = flow;

	for (int i = flowVertexes[x]->getHead(); i < (int)flowEdges[x].size(); i++) {
		int y = flowEdges[x][i]->getTo();
		if (flowVertexes[y]->getDist() == flowVertexes[x]->getDist() + 1 && flowEdges[x][i]->getRest() >= minG && flow > 0) {
			long long cur = pushFlow(y, min(flow, (long long)flowEdges[x][i]->getRest()), minG, finish);
			flow -= cur;
			if (flow != 0) {
				flowVertexes[x]->increaseHead();
			}
			flowEdges[x][i]->push(cur);
		}			
	}	

	return (oldflow - flow);
}

long long FlowGraph::Dinic(int start, int finish) {
	long long flow = 0;
	for (int minG = this->getMaxCap(); minG > 0; minG /= 2) {
		while (true) {
			Graph G(flowEdges, flowVertexes, minG);
			G.bfs(start);
			for (int i = 0; i < (int)flowVertexes.size(); i++) {
				flowVertexes[i]->initHead();
			}
			long long cur = pushFlow(start, INFLL, minG, finish);
			if (cur == 0) {
				break;
			}
			flow += cur;
		}
	}
	return flow;
}

void FlowGraph::push(FlowEdge* edge) {
 	int from = edge->getFrom();
 	int to = edge->getTo();
 	long long d = min(flowVertexes[from]->getExcess(), (long long)edge->getRest());
 	edge->push(d);
 	flowVertexes[from]->increaseExcess(-d);
 	flowVertexes[to]->increaseExcess(d);
}

void FlowGraph::relabel(int vertex) {
	int ans = INF;
	for (int i = 0; i < (int)flowEdges[vertex].size(); i++) {
		if (flowEdges[vertex][i]->getRest() > 0) {
			ans = min(ans, flowVertexes[flowEdges[vertex][i]->getTo()]->getLabel() + 1);
		}
	}
	flowVertexes[vertex]->setLabel(ans);
}

void FlowGraph::initPreflow(int start) {
	for (int i = 0; i < (int)flowVertexes.size(); i++) {
		flowVertexes[i]->setExcess(0);
		flowVertexes[i]->setLabel(0);
	}
	for (int j = 0; j < (int)flowEdges[start].size(); j++) {
		if (flowEdges[start][j]->getTo() == start) {
			continue;
		}
		flowVertexes[ flowEdges[start][j]->getTo() ]->increaseExcess( flowEdges[start][j]->getRest() );
		flowVertexes[start]->increaseExcess(-flowEdges[start][j]->getRest());
		flowEdges[start][j]->push(flowEdges[start][j]->getRest());
	}
	flowVertexes[start]->setLabel(flowVertexes.size());
}

void FlowGraph::discharge(int u, int start, int finish, queue<int>& q, vector<int>& used) {
	while (flowVertexes[u]->getExcess() > 0) {
		if (flowVertexes[u]->getHead() == (int)flowEdges[u].size()) { 
			relabel(u);
			flowVertexes[u]->initHead();
		}
		else {
			FlowEdge* e = flowEdges[u][ flowVertexes[u]->getHead() ];
			if (e->getRest() > 0 && flowVertexes[u]->getLabel() == flowVertexes[e->getTo()]->getLabel() + 1) {
				push(e);
				if (used[e->getTo()] == 0 && flowVertexes[e->getTo()]->getExcess() > 0 && e->getTo() != start && e->getTo() != finish) {
					q.push(e->getTo());
					used[e->getTo()] = 1;
				}
			}
			else
				flowVertexes[u]->increaseHead();
		}
	}
	used[u] = 0;
}

long long FlowGraph::RelabelToFront(int start, int finish) {
	initPreflow(start);
	vector<int> used(flowVertexes.size());
	queue<int> q;
	for (int i = 0; i < (int)flowVertexes.size(); i++) {
		flowVertexes[i]->initHead();
		if (i != start && i != finish && flowVertexes[i]->getExcess() > 0) {
			q.push(i);
			used[i] = 1;
		}
	}
	

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		discharge(cur, start, finish, q, used);
	}

	return flowVertexes[finish]->getExcess();
}

void FlowGraph::printFlow() {
	vector<int> ans;
	ans.resize(EdgeCount);
	for (int i = 0; i < (int)flowEdges.size(); i++) {
		for (int j = 0; j < (int)flowEdges[i].size(); j++) {
			if (flowEdges[i][j]->getId() != 0) {
				int id = flowEdges[i][j]->getId();
				ans[id - 1] = flowEdges[i][j]->getFlow();
			}
		}
	}	

	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i] << endl;
	}
}

void FlowGraph::Gap() {
	vector<int> used(flowVertexes.size() + 1);
	for (int i = 0; i < (int)used.size(); i++) {
		used[i] = 0;
	}
	for (int i = 0; i < (int)flowVertexes.size(); i++) {
		used[flowVertexes[i]->getLabel()] = 1;
	}

	int h = 0;
	for (int i = 0; i < (int)used.size(); i++) {
		if (used[i] == 0) {
			h = i;
		}
   	}

	for (int i = 0; i < (int)flowVertexes.size(); i++) {
		if (flowVertexes[i]->getLabel() > h) {
			flowVertexes[i]->setLabel(flowVertexes.size());
		}
	}	
}

#endif