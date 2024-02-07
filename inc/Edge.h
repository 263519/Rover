

#ifndef GRAPH_ALGORITHMS_EDGE_H
#define GRAPH_ALGORITHMS_EDGE_H

class Edge {
  public:
    //virtual ~Edge() {}
    virtual int Element_e() const = 0;
    virtual void set_edge_element(int ele) = 0;
    virtual Vertex* Start() const = 0;
    virtual Vertex* End() const = 0;

};
#endif // GRAPH_ALGORITHMS_EDGE_H
