#ifndef GRAPH_ALGORITHMS_EDGE_MATRIX_H
#define GRAPH_ALGORITHMS_EDGE_MATRIX_H

#include "Edge.h"
#include "Vertex_matrix.h"

template<typename T>
class Edge_matrix : public Edge<T> {
protected:
    int element; // Changed the type to int
    Vertex_matrix<T>* start;
    Vertex_matrix<T>* end;
    typename std::list<Edge_matrix<T>>::iterator position;

public:
    Edge_matrix(int element, Vertex_matrix<T>* start, Vertex_matrix<T>* end, typename std::list<Edge_matrix<T>>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;
    }

     virtual ~Edge_matrix() {}

    int Element_e() const { return element; } // Changed the return type to int
    void set_edge_element(int ele) { element = ele; } // Changed the argument type to int

    Vertex<T>* Start() const { return dynamic_cast<Vertex<T>*>(start); }

    Vertex<T>* End() const { return dynamic_cast<Vertex<T>*>(end); }

    typename std::list<Edge_matrix<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<Edge_matrix<T>>::iterator p) { position = p; }
};

#endif // GRAPH_ALGORITHMS_EDGE_MATRIX_H
