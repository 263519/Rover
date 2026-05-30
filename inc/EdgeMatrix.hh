#ifndef GRAPH_ALGORITHMS_EDGE_MATRIX_HH
#define GRAPH_ALGORITHMS_EDGE_MATRIX_HH

#include "Edge.hh"
#include "VertexMatrix.hh"

template<typename T>
class EdgeMatrix : public Edge<T> {
protected:
    int element;
    VertexMatrix<T>* start;
    VertexMatrix<T>* end;
    typename std::list<EdgeMatrix<T>>::iterator position;

public:
    EdgeMatrix(int element, VertexMatrix<T>* start, VertexMatrix<T>* end, typename std::list<EdgeMatrix<T>>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;
    }

    virtual ~EdgeMatrix() {}

    int Element_e() const override { return element; }
    void set_edge_element(int ele) override { element = ele; }

    Vertex<T>* Start() const override { return dynamic_cast<Vertex<T>*>(start); }
    Vertex<T>* End() const override { return dynamic_cast<Vertex<T>*>(end); }

    typename std::list<EdgeMatrix<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<EdgeMatrix<T>>::iterator p) { position = p; }
};

#endif // GRAPH_ALGORITHMS_EDGE_MATRIX_HH
