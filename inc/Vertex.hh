#ifndef GRAPH_ALGORITHMS_VERTEX_HH
#define GRAPH_ALGORITHMS_VERTEX_HH

template<typename T>
class Vertex {
public:
    virtual ~Vertex() {}
    virtual T Element_v() const = 0;
    virtual void set_vertex_element(T ele) = 0;
};

#endif // GRAPH_ALGORITHMS_VERTEX_HH
