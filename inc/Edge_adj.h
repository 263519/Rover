#ifndef GRAPH_ALGORITHMS_EDGE_ADJ_H
#define GRAPH_ALGORITHMS_EDGE_ADJ_H

#include <list>
#include "Edge.h"
#include "Vertex.h"

template<typename T>
class Edge_adj : public Edge<T> {
protected:
    int element; // Changed to int
    Vertex<T>* start;
    Vertex<T>* end;
    typename std::list<Edge_adj<T>>::iterator position;
    typename std::list<Edge_adj<T>*>::iterator pos_start;
    typename std::list<Edge_adj<T>*>::iterator pos_end;

public:
    Edge_adj(int element, Vertex<T>* start, Vertex<T>* end, typename std::list<Edge_adj<T>>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;
    }

    virtual ~Edge_adj() {}

    int Element_e() const { return element; } // Changed return type to int
    void set_edge_element(int ele) { element = ele; } // Changed argument type to int

    Vertex<T>* Start() const { return start; }

    Vertex<T>* End() const { return end; }

    typename std::list<Edge_adj<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<Edge_adj<T>>::iterator p) { this->position = p; }

    typename std::list<Edge_adj<T>*>::iterator Position_start() { return pos_start; }
    void set_Position_start(typename std::list<Edge_adj<T>*>::iterator pe) { this->pos_start = pe; }

    typename std::list<Edge_adj<T>*>::iterator Position_end() { return pos_end; }
    void set_Position_end(typename std::list<Edge_adj<T>*>::iterator pen) { this->pos_end = pen; }
};

#endif // GRAPH_ALGORITHMS_EDGE_ADJ_H
