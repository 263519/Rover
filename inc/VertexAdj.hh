#ifndef GRAPH_ALGORITHMS_VERTEX_ADJ_HH
#define GRAPH_ALGORITHMS_VERTEX_ADJ_HH

#include <list>
#include "Vertex.hh"

// Forward declaration of EdgeAdj
template<typename T>
class EdgeAdj;

template<typename T>
class VertexAdj : public Vertex<T> {
private:
    T element;
    typename std::list<VertexAdj<T>>::iterator position;
    typename std::list<EdgeAdj<T>*> edges;
    typename std::list<EdgeAdj<T>*>::iterator pos;

public:
    explicit VertexAdj(T ele) : element(ele) {
        this->pos = edges.end();
    }

    virtual ~VertexAdj() = default;

    T Element_v() const override { return element; }
    void set_vertex_element(T ele) { element = ele; }

    std::list<EdgeAdj<T>*> list_Edge_adj() { return edges; }
    void ADDEdge_adj(EdgeAdj<T>* e) {
        edges.push_back(e);
        pos = --edges.end();
    }

    typename std::list<EdgeAdj<T>*>::iterator Position_edge() { return pos; }

    typename std::list<VertexAdj<T>>::iterator Position() { return position; }

    void set_Position(typename std::list<VertexAdj<T>>::iterator p) { this->position = p; }
};

#endif // GRAPH_ALGORITHMS_VERTEX_ADJ_HH
