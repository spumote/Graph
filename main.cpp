#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

const int INF = 1e9;
const long long INFLL = (long long)1e18;

#include "Vertex.h"
#include "Edge.h"
#include "FlowEdge.h"
#include "Graph.h"
#include "FlowGraph.h"

using namespace std;	        

int main() {
	FlowGraph G;
	G.get();
	std::cout << G.RelabelToFront(0, G.getSize() - 1) << std::endl;
	G.printFlow();
	return 0;
}