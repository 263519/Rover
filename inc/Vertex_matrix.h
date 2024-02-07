#ifndef GRAPH_ALGORITHMS_VERTEX_MATRIX_H
#define GRAPH_ALGORITHMS_VERTEX_MATRIX_H

#include "Vertex.h"
//#include <list>
//#include "Edge_matrix.h"
template<typename T>
class Vertex_matrix : public Vertex {

    T element;
    int key;
    std::list<Vertex_matrix>::iterator position;


  public:
    explicit Vertex_matrix(T ele) { element = ele;

        //this->key = -1;
    }

    T Element_v() const { return element; }
    void set_vertex_element(T ele) { element = ele; }



    typename std::list<Vertex_matrix>::iterator Position()  { return position; }

    void set_Position(list<Vertex_matrix>::iterator p) { this->position = p;}
    int Key()  { return key; }
    void set_key(int k) { key = k; }

    //virtual ~Vertex_adj() {}
};




#endif // GRAPH_ALGORITHMS_VERTEX_MATRIX_H
