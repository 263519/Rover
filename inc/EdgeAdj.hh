#ifndef GRAPH_ALGORITHMS_EDGE_ADJ_HH
#define GRAPH_ALGORITHMS_EDGE_ADJ_HH

#include <list>
#include "Edge.hh"
#include "Vertex.hh"

template<typename T>
class EdgeAdj : public Edge<T> {
protected:
    int element;
    Vertex<T>* start;
    Vertex<T>* end;
    typename std::list<EdgeAdj<T>>::iterator position;
    typename std::list<EdgeAdj<T>*>::iterator pos_start;
    typename std::list<EdgeAdj<T>*>::iterator pos_end;

public:
    EdgeAdj(int element, Vertex<T>* start, Vertex<T>* end, typename std::list<EdgeAdj<T>>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;
    }

    virtual ~EdgeAdj() {}

    int Element_e() const override { return element; }
    void set_edge_element(int ele) override { element = ele; }

    Vertex<T>* Start() const override { return start; }
    Vertex<T>* End() const override { return end; }

    typename std::list<EdgeAdj<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<EdgeAdj<T>>::iterator p) { this->position = p; }

    typename std::list<EdgeAdj<T>*>::iterator Position_start() { return pos_start; }
    void set_Position_start(typename std::list<EdgeAdj<T>*>::iterator pe) { this->pos_start = pe; }

    typename std::list<EdgeAdj<T>*>::iterator Position_end() { return pos_end; }
    void set_Position_end(typename std::list<EdgeAdj<T>*>::iterator pen) { this->pos_end = pen; }
};

#endif // GRAPH_ALGORITHMS_EDGE_ADJ_HH
