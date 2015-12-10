#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

int FlowEdge::getFlow() {
	return flow;
}   

void FlowEdge::setreversedEdge(FlowEdge* _reversedEdge) {
	reversedEdge = _reversedEdge;
}

void FlowEdge::push(int x) {
	this->flow += x;
	this->reversedEdge->flow -= x;
}

int FlowEdge::getRest() {
	return capacity - flow;
}

#endif