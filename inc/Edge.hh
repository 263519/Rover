#ifndef GRAPH_ALGORITHMS_EDGE_HH
#define GRAPH_ALGORITHMS_EDGE_HH

#include "Vertex.hh"

template<typename T>
class Edge {
public:
    virtual ~Edge() {}
    virtual int Element_e() const = 0;
    virtual void set_edge_element(int ele) = 0;
    virtual Vertex<T>* Start() const = 0;
    virtual Vertex<T>* End() const = 0;
};

#endif // GRAPH_ALGORITHMS_EDGE_HH
