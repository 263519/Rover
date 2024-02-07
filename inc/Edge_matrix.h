//
// Created by PRO on 12.05.2023.
//

#ifndef GRAPH_ALGORITHMS_EDGE_MATRIX_H
#define GRAPH_ALGORITHMS_EDGE_MATRIX_H


#include "Edge.h"
#include "Vertex_matrix.h"

class Edge_matrix : public Edge {
  protected:
    int element;
    Vertex_matrix* start;
    Vertex_matrix* end;
    std::list<Edge_matrix>::iterator position;




  public:

    Edge_matrix(int element, Vertex_matrix* start, Vertex_matrix* end, std::list<Edge_matrix>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;
    }
    // virtual ~Edge_adj() {}
    int Element_e() const { return element; }
    void set_edge_element(int ele) { element = ele; }

    Vertex* Start() const { return dynamic_cast<Vertex*>(start); }

    Vertex* End() const { return dynamic_cast<Vertex*>(end); }

    typename std::list<Edge_matrix>::iterator Position()  { return position; }
    void set_Position(list<Edge_matrix>::iterator p) { position = p;}
    //typename std::list<Vertex_adj>::iterator Position_s()  { return adj; }
    //typename std::list<Vertex_adj>::iterator Position_e()  { return e; }

};
#endif // GRAPH_ALGORITHMS_EDGE_MATRIX_H
