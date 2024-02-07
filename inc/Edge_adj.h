#ifndef GRAPH_ALGORITHMS_EDGE_ADJ_H
#define GRAPH_ALGORITHMS_EDGE_ADJ_H
//#include "Vertex_adj.h"
#include "Edge.h"
#include "Vertex.h"
//#include "adjacency_list_graph.hpp"

//#include "ADJ.h"
class Edge_adj : public Edge {
  protected:
    int element;
    Vertex* start;
    Vertex* end;
    std::list<Edge_adj>::iterator position;
    list<Edge_adj *>::iterator pos_start;
    list<Edge_adj *>::iterator pos_end;


  public:

    Edge_adj(int element, Vertex* start, Vertex* end, std::list<Edge_adj>::iterator position) {
        this->element = element;
        this->start = start;
        this->end = end;
        this->position = position;

    }
    virtual ~Edge_adj() {}
    int Element_e() const { return element; }
    void set_edge_element(int ele) { element = ele; }

    Vertex* Start() const { return start; }

    Vertex* End() const { return end; }

    typename std::list<Edge_adj>::iterator Position()  { return position; }
    void set_Position(list<Edge_adj>::iterator p) { this->position = p;}

    typename std::list<Edge_adj*>::iterator Position_start()  { return pos_start; }
    void set_Position_start(list<Edge_adj*>::iterator pe) { this->pos_start = pe;}
    typename std::list<Edge_adj*>::iterator Position_end()  { return pos_end; }
    void set_Position_end(list<Edge_adj*>::iterator pen) { this->pos_end = pen;}


};

#endif // GRAPH_ALGORITHMS_EDGE_ADJ_H
