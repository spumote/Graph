#ifndef _VERTEX_CPP_
#define _VERTEX_CPP_

#include <iostream>
#include <cstdio>

#include "Vertex.h"

int Vertex::getDist() {
	return dist;
}

int Vertex::getHead() {
	return edges_head;
}

void Vertex::setDist(int x) {
	dist = x;
}

void Vertex::increaseHead() {
	edges_head++;
}

void Vertex::initHead() {
	edges_head = 0;
}

long long Vertex::getExcess() {
	return excess;
}

int Vertex::getLabel() {
	return label;
}

void Vertex::setExcess(long long x) {
	excess = x;
}

void Vertex::setLabel(int x) {
	label = x;
}

void Vertex::increaseExcess(long long x) {
	excess += x;
}

#endif