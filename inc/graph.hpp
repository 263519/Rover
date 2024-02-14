#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <list>
#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Edge.h"

template<typename T>
class Graph {

int numVer = 0;

public:
    virtual ~Graph() {}
    virtual Vertex<T>* insertVertex(T ve) = 0;
    virtual  Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) = 0;
    virtual void endVertices(int o) = 0;
    virtual void endVertices(Edge<T>* e) = 0;
    virtual void areAdjacent(Vertex<T>* v, Vertex<T>* w) = 0;
    virtual Vertex<T>* opposite(Vertex<T>* v, Edge<T>* e) = 0;
    virtual void replace(Vertex<T>* v, T x) = 0;
    virtual void replace(Edge<T>* e, int x) = 0;
    virtual void removeVertex(Vertex<T>* v) = 0;
    virtual void removeEdge(Edge<T>* e) = 0;
    virtual std::vector<Edge<T>*> incidentEdges(Vertex<T>* v) = 0;
    virtual void vertices() = 0;
    virtual void edges() = 0;
    virtual void print() = 0;
    virtual std::list<Vertex<T>*> get_vertices() = 0;
    virtual std::list<Edge<T>*> get_edges() = 0;

    int numVertices() const {
        return numVer;
    }
};

#endif /* GRAPH_HPP_ */
