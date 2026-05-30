#ifndef ADJACENCY_MATRIX_GRAPH_HH
#define ADJACENCY_MATRIX_GRAPH_HH

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "Graph.hh"
#include "VertexMatrix.hh"
#include "EdgeMatrix.hh"

template<typename T>
class AdjacencyMatrixGraph : public Graph<T> {
    std::list<VertexMatrix<T>> v_list;
    int pos = 0;
    int v_siz;
    int e_siz;
    std::vector<std::vector<EdgeMatrix<T>*>> adjacency_matrix;
    std::list<EdgeMatrix<T>> e_list;

public:
    void new_matrix(T v, int e) {
        v_siz = v;
        e_siz = e;
        adjacency_matrix.resize(v_siz, std::vector<EdgeMatrix<T>*>(e_siz));
    }
    
    Vertex<T>* insertVertex(T ve) override {
        for (auto& vertex : v_list) {
            if (vertex.Element_v() == ve) {
                return &vertex;
            }
        }

        VertexMatrix<T> ver(ve);
        v_list.push_back(ver);
        v_list.back().set_key(pos);
        v_list.back().set_Position(--v_list.end());
        ++pos;
        return &v_list.back();
    }
    
    Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) override {
        VertexMatrix<T>* start = dynamic_cast<VertexMatrix<T>*>(v1);
        VertexMatrix<T>* end = dynamic_cast<VertexMatrix<T>*>(v2);
        EdgeMatrix<T> edge(e, start, end, --e_list.end());
        e_list.push_back(edge);
        adjacency_matrix[start->Key()][end->Key()] = &e_list.back();
        return &e_list.back();
    }
    
    void print() override {
        std::cout << "cannot print adjacency matrix for std::pair<int,int>\n";
    }
};

#endif /* ADJACENCY_MATRIX_GRAPH_HH */
