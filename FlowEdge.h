#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include "Edge.h"

class FlowEdge : public Edge {
private:
	int flow, capacity;
	FlowEdge* reversedEdge;
public:
	FlowEdge() : reversedEdge(NULL) {}
	FlowEdge(int _from, int _to, int _id, int _flow, int _capacity, FlowEdge* _reversedEdge) : Edge(_from, _to, _id) {
		flow = _flow;
	 	capacity = _capacity;
		reversedEdge = _reversedEdge;
	}	

	void setreversedEdge(FlowEdge* _reversedEdge);
	void push(int x);
	int getRest();
	int getFlow();
};

#include "FlowEdge.cpp"

#endif