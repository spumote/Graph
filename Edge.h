#ifndef _EDGE_H_
#define _EDGE_H_

#include <iostream>

class Edge {
protected:
	int from, to;
	int id;
public:
	Edge() {} 
	Edge(int _from, int _to, int _id) : from(_from), to(_to), id(_id) {}
	int getTo();
	int getId();
	int getFrom();
};

#include "Edge.cpp"

#endif
