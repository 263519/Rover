#ifndef GRAPH_ALGORITHMS_VERTEX_MATRIX_H
#define GRAPH_ALGORITHMS_VERTEX_MATRIX_H

#include "Vertex.h"
#include <list>

template<typename T>
class Vertex_matrix : public Vertex<T> {
private:
    T element;
    int key;
    typename std::list<Vertex_matrix<T>>::iterator position;

public:
    explicit Vertex_matrix(T ele) : element(ele) {
        // Initialize key to some default value if needed
        // this->key = -1;
    }

    T Element_v() const override { return element; }
    void set_vertex_element(T ele) { element = ele; }

    typename std::list<Vertex_matrix<T>>::iterator Position() { return position; }
    void set_Position(typename std::list<Vertex_matrix<T>>::iterator p) { this->position = p; }

    int Key() const { return key; }
    void set_key(int k) { key = k; }
};

#endif // GRAPH_ALGORITHMS_VERTEX_MATRIX_H
