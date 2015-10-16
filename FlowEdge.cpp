#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

int FlowEdge::getFlow() {
	return flow;
}   

void FlowEdge::setRev(FlowEdge* _rev) {
	rev = _rev;
}

void FlowEdge::push(int x) {
	this->flow += x;
	this->rev->flow -= x;
}

int FlowEdge::getG() {
	return capacity - flow;
}

#endif