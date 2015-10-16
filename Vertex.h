#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <iostream>
#include <cstdio>

class Vertex {
private:
	int dist;
	int edges_head;
	long long excess;
	int label;
public:
	Vertex() : dist(1e9), edges_head(0) {}

	int getDist();
	int getHead();
	void setDist(int x);
	void increaseHead();
	void initHead();

	long long getExcess();
	int getLabel();
	void setExcess(long long x);
	void setLabel(int x);
	void increaseExcess(long long x);
};

#include "Vertex.cpp"

#endif