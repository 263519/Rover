//
// Created by PRO on 10.05.2023.
//

#ifndef GRAPH_ALGORITHMS_VERTEX_H
#define GRAPH_ALGORITHMS_VERTEX_H

class Vertex {
  public:
    virtual int Element_v() const = 0;
    virtual void set_vertex_element(int ele) = 0;
    //virtual ~Vertex() {}
};
#endif // GRAPH_ALGORITHMS_VERTEX_H
