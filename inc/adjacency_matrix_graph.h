#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>
#include <list>
#include "graph.hpp"
#include "Vertex_matrix.h"
#include "Edge_matrix.h"

template<typename T>
class AdjacencyMatrixGraph : public Graph<T> {

    std::list<Vertex_matrix<T>> v_list;
    T pos = 0;
    int v_siz;
    int e_siz;
    std::vector<std::vector<Edge_matrix<T>*>> adjacency_matrix;
    std::list<Edge_matrix<T>> e_list;

public:

    void new_matrix(T v, int e) {
        v_siz = v;
        e_siz = e;
        adjacency_matrix.resize(v_siz, std::vector<Edge_matrix<T>*>(e_siz));
    }
    Vertex<T>* insertVertex(T ve); // dodaje wierzchołek
   Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) ; // v, w - wierzchołki o krawędź źle
    void insertEdge_int(T v, T w, int o); // dobre
    void endVertices(int o); // podaje krawędź zwraca wierzchołki
    void endVertices(Edge<T>* e); // to inaczej
    void areAdjacent(Vertex<T>* v, Vertex<T>* w); // to inaczej
    Vertex<T>* opposite(Vertex<T>* v, Edge<T>* e);
    void replace(Vertex<T>* v, T x); // zastąp element w wierzchołku
    void replace(Edge<T>* v, int x); // zastąp element w krawędzi
    void removeVertex(Vertex<T>* v);
    void removeEdge(Edge<T>* e); // to inaczej
    std::vector<Edge<T>*> incidentEdges(Vertex<T>* v);
    void vertices();
    void edges();
    void print();
    static std::unique_ptr<Graph<T>> createGraph(std::istream& is);
    std::list<Vertex<T>*> get_vertices() {
        std::list<Vertex<T>*> v;
        for (auto& vertex : v_list) {
            v.push_back(&vertex);
        }
        return v;
    }

    std::list<Edge<T>*> get_edges() {
        std::list<Edge<T>*> e;
        for (auto& edge : e_list) {
            e.push_back(&edge);
        }
        return e;
    }

};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
