#ifndef GRAPH_HH_
#define GRAPH_HH_

#include <list>
#include <iostream>
#include <vector>

#include "Vertex.hh"
#include "Edge.hh"

template<typename T>
class Graph {

int numVer = 0;

public:
    virtual ~Graph() {}
    virtual Vertex<T>* insertVertex(T ve) = 0;
    virtual Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) = 0;
    virtual void print() = 0;
};

#endif /* GRAPH_HH_ */
