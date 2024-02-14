#ifndef GRAPH_ALGORITHMS_VERTEX_ADJ_H
#define GRAPH_ALGORITHMS_VERTEX_ADJ_H

#include <list>
#include "Edge_adj.h"
#include "Vertex.h"

template<typename T>
class Vertex_adj : public Vertex<T> {
private:
T element;

    typename std::list<Vertex_adj<T>>::iterator position;

       typename std::list<Edge_adj<T> *> edges;
      typename  std::list<Edge_adj<T> *>::iterator pos;

public:
    explicit Vertex_adj(T ele) : element(ele) {
        this->pos = edges.end();
    }

    virtual ~Vertex_adj() = default;

    T Element_v() const override { return element; }
    void set_vertex_element(T ele) { element = ele; }

    std::list<Edge_adj<T>*> list_Edge_adj() { return edges; }
    void ADDEdge_adj(Edge_adj<T>* e) {
        edges.push_back(e);
        pos = --edges.end();
    }

   // typename std::list<Edge_adj<T>*>::iterator Position_edge() { return pos; }

    typename std::list<Edge_adj<T>*>::iterator Position_edge()  { return pos; }


    typename std::list<Vertex_adj<T>>::iterator Position()  { return position; }




   void set_Position(typename std::list<Vertex_adj<T>>::iterator p) { this->position = p;}

};

#endif // GRAPH_ALGORITHMS_VERTEX_ADJ_H
