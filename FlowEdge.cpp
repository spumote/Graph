#ifndef _FLOWEDGE_CPP_
#define _FLOWEDGE_CPP_

#include "FlowEdge.h"

int FlowEdge::getFlow() {
	return flow;
}   

void FlowEdge::setreversedEdge(FlowEdge* _reversedEdge) {
	reversedEdge = _reversedEdge;
}

void FlowEdge::push(int ad) {
	this->flow += ad;
	this->reversedEdge->flow -= ad;
}

int FlowEdge::getRest() {
	return capacity - flow;
}

#endif