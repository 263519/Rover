//
// Created by PRO on 12.05.2023.
//

#ifndef GRAPH_ALGORITHMS_VERTEX_ADJ_H
#define GRAPH_ALGORITHMS_VERTEX_ADJ_H

//#include "ADJ.h"
#include "Edge_adj.h"
#include "Vertex.h"


// #include "ADJ.h"

class Vertex_adj : public Vertex {

    int element;

    std::list<Vertex_adj>::iterator position;

        std::list<Edge_adj *> edges;
        list<Edge_adj *>::iterator pos;

  public:
    explicit Vertex_adj(int ele) { element = ele;
this->pos = edges.end();

    }
    virtual ~Vertex_adj() = default;
    int Element_v() const { return element; }
    void set_vertex_element(int ele) { element = ele; }


    list<Edge_adj*> list_Edge_adj() {return edges;}
    void ADDEdge_adj(Edge_adj  *e) {
            edges.push_back(e);
            pos = --edges.end();

    }
    //void set_Position_edge(list<Edge_adj*>::iterator p) { this->pos = p;}
    typename std::list<Edge_adj*>::iterator Position_edge()  { return pos; }


    typename std::list<Vertex_adj>::iterator Position()  { return position; }




   void set_Position(list<Vertex_adj>::iterator p) { this->position = p;}

};
#endif // GRAPH_ALGORITHMS_VERTEX_ADJ_H
