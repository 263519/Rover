#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>
#include "graph.hpp"
#include "Vertex_matrix.h"
#include "Edge_matrix.h"
using namespacestd;
template<typename T>
class AdjacencyMatrixGraph : public Graph{

   list<Vertex_matrix> v_list;
    T pos =0;
    int  v_siz;
    int e_siz;
    vector<vector<Edge_matrix*>> adjacency_matrix;

    list<Edge_matrix> e_list;
  public:

    void new_matrix (T v, int e) {
        v_siz = v;
       e_siz = e;
        adjacency_matrix.resize(v_siz, std::vector<Edge_matrix*>(e_siz));
    }
     Vertex * insertVertex(T ve);// dodaje wierzcjolek
     Edge * insertEdge(Vertex * v, Vertex * w,int o);//v,w - wierzcholki o krawedz zle
     void insertEdge_int(T v,T w,int o);//dobre
     void endVertices(int o);// podaje krawedz zwraca wierzcholki
     void endVertices(Edge  *e);//to inaczejn
     void areAdjacent(Vertex * v , Vertex * w);// to inaczej
     Vertex * opposite(Vertex  *v,Edge  *e);
     void replace(Vertex  *v,T x);//zastap element w wierzcholku
     void replace(Edge  *v,int x);// zastap element w krawedzi
     void removeVertex(Vertex  *v);
     void removeEdge(Edge  *e);//to inaczej
     vector<Edge*> incidentEdges(Vertex  *v);
     void vertices();
     void edges();
     void print();
     static std::unique_ptr<Graph> createGraph(std::istream& is);
     std::list<Vertex*> get_vertices()
     {
        std::list<Vertex*> v;
        for(auto& vertex : v_list)
        {
            v.push_back(&vertex);
        }
        return v;
     }

     std::list<Edge*> get_edges(){
        std::list<Edge*> e;
        for(auto& edge : e_list)
        {
            e.push_back(&edge);
        }
        return e;
     }

};

#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */
