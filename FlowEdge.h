#ifndef _FLOWEDGE_H_
#define _FLOWEDGE_H_

#include "Edge.h"

class FlowEdge : public Edge {
private:
	int flow, capacity;
	FlowEdge* rev;
public:
	FlowEdge() : rev(NULL) {}
	FlowEdge(int _from, int _to, int _id, int _flow, int _capacity, FlowEdge* _rev) : Edge(_from, _to, _id) {
		flow = _flow;
	 	capacity = _capacity;
		rev = _rev;
	}	

	void setRev(FlowEdge* _rev);
	void push(int x);
	int getG();
	int getFlow();
};

#include "FlowEdge.cpp"

#endif