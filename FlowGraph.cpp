#ifndef _FLOWGRAPH_CPP_
#define _FLOWGRAPH_CPP_

#include "FlowGraph.h"

int FlowGraph::getSize() {
	return E.size();
}

int FlowGraph::getMaxCap() {
	int ans = 0;
	for (int i = 0; i < (int)E.size(); i++) {
		for (int j = 0; j < (int)E[i].size(); j++) {
			ans = max(ans, E[i][j]->getFlow() + E[i][j]->getG());
		}
	}
	return ans;	
}

void FlowGraph::get() {
	int n, m;
	cin >> n >> m;
	EdgeCount = m;
	E.resize(n);
	V.resize(n);
	for (int i = 0; i < n; i++) {
		V[i] = new Vertex();
	}

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;


		E[a].push_back(new FlowEdge(a, b, i + 1, 0, c, NULL));
		E[b].push_back(new FlowEdge(b, a, 0, 0, 0, E[a][ E[a].size() - 1 ]));
		E[a][ E[a].size() - 1 ]->setRev(E[b][ E[b].size() - 1 ]);
	}	
}

long long FlowGraph::pushFlow(int x, long long flow, int minG, int T) {
	if (x == T) {
		return flow;
	}
	long long oldflow = flow;

	for (int i = V[x]->getHead(); i < (int)E[x].size(); i++) {
		int y = E[x][i]->getTo();
		if (V[y]->getDist() == V[x]->getDist() + 1 && E[x][i]->getG() >= minG && flow > 0) {
			long long cur = pushFlow(y, min(flow, (long long)E[x][i]->getG()), minG, T);
			flow -= cur;
			if (flow != 0) {
				V[x]->increaseHead();
			}
			E[x][i]->push(cur);
		}			
	}	

	return (oldflow - flow);
}

long long FlowGraph::Dinic(int S, int T) {
	long long flow = 0;
	for (int minG = this->getMaxCap(); minG > 0; minG /= 2) {
		while (true) {
			Graph G(E, V, minG);
			G.bfs(S);
			for (int i = 0; i < (int)V.size(); i++) {
				V[i]->initHead();
			}
			long long cur = pushFlow(S, INFLL, minG, T);
			if (cur == 0) {
				break;
			}
			flow += cur;
		}
	}
	return flow;
}

void FlowGraph::push(FlowEdge* e) {
 	int a = e->getFrom();
 	int b = e->getTo();
 	long long d = min(V[a]->getExcess(), (long long)e->getG());
 	e->push(d);
 	V[a]->increaseExcess(-d);
 	V[b]->increaseExcess(d);
}

void FlowGraph::relabel(int a) {
	int ans = INF;
	for (int i = 0; i < (int)E[a].size(); i++) {
		if (E[a][i]->getG() > 0) {
			ans = min(ans, V[ E[a][i]->getTo() ]->getLabel() + 1);
		}
	}
	V[a]->setLabel(ans);
}

void FlowGraph::initPreflow(int S) {
	for (int i = 0; i < (int)V.size(); i++) {
		V[i]->setExcess(0);
		V[i]->setLabel(0);
	}
	for (int j = 0; j < (int)E[S].size(); j++) {
		if (E[S][j]->getTo() == S) {
			continue;
		}
		V[ E[S][j]->getTo() ]->increaseExcess( E[S][j]->getG() );
		V[S]->increaseExcess(-E[S][j]->getG());
		E[S][j]->push(E[S][j]->getG());
	}
	V[S]->setLabel(V.size());
}

void FlowGraph::discharge(int u, int S, int T, queue<int>& q, vector<int>& used) {
	while (V[u]->getExcess() > 0) {
		if (V[u]->getHead() == (int)E[u].size()) { 
			relabel(u);
			V[u]->initHead();
		}
		else {
			FlowEdge* e = E[u][ V[u]->getHead() ];
			if (e->getG() > 0 && V[u]->getLabel() == V[e->getTo()]->getLabel() + 1) {
				push(e);
				if (used[e->getTo()] == 0 && V[e->getTo()]->getExcess() > 0 && e->getTo() != S && e->getTo() != T) {
					q.push(e->getTo());
					used[e->getTo()] = 1;
				}
			}
			else
				V[u]->increaseHead();
		}
	}
	used[u] = 0;
}

long long FlowGraph::RelabelToFront(int S, int T) {
	initPreflow(S);
	vector<int> used(V.size());
	queue<int> q;
	for (int i = 0; i < (int)V.size(); i++) {
		V[i]->initHead();
		if (i != S && i != T && V[i]->getExcess() > 0) {
			q.push(i);
			used[i] = 1;
		}
	}
	

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		discharge(cur, S, T, q, used);
	}

	return V[T]->getExcess();
}

void FlowGraph::printFlow() {
	vector<int> ans;
	ans.resize(EdgeCount);
	for (int i = 0; i < (int)E.size(); i++) {
		for (int j = 0; j < (int)E[i].size(); j++) {
			if (E[i][j]->getId() != 0) {
				int id = E[i][j]->getId();
				ans[id - 1] = E[i][j]->getFlow();
			}
		}
	}	

	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i] << endl;
	}
}

void FlowGraph::Gap() {
	vector<int> used(V.size() + 1);
	for (int i = 0; i < (int)used.size(); i++) {
		used[i] = 0;
	}
	for (int i = 0; i < (int)V.size(); i++) {
		used[V[i]->getLabel()] = 1;
	}

	int h = 0;
	for (int i = 0; i < (int)used.size(); i++) {
		if (used[i] == 0) {
			h = i;
		}
   	}

	for (int i = 0; i < (int)V.size(); i++) {
		if (V[i]->getLabel() > h) {
			V[i]->setLabel(V.size());
		}
	}	
}

#endif