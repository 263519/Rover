#ifndef GRAPH_ALGORITHMS_VERTEX_MATRIX_HH
#define GRAPH_ALGORITHMS_VERTEX_MATRIX_HH

#include "Vertex.hh"
#include <list>

template<typename T>
class VertexMatrix : public Vertex<T> {
private:
    T element;
    int key;
    typename std::list<VertexMatrix<T>>::iterator position;

public:
    explicit VertexMatrix(T ele) : element(ele) {
        // Initialize key to some default value if needed
        // this->key = -1;
    }

    T Element_v() const override { return element; }
    void set_vertex_element(T ele) override { element = ele; }

    typename std::list<VertexMatrix<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<VertexMatrix<T>>::iterator p) { this->position = p; }

    int Key() const { return key; }
    void set_key(int k) { key = k; }
};

#endif // GRAPH_ALGORITHMS_VERTEX_MATRIX_HH
