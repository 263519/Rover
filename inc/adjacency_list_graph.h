#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>
#include <unordered_map>
#include <list>

#include "graph.hpp"
#include "Edge_adj.h"
#include "Vertex_adj.h"

template<typename T>
class AdjacencyListGraph : public Graph<T>
{

std::list<Vertex_adj<T>> v_list;
std::list<Edge_adj<T>> e_list;


public:

    virtual ~AdjacencyListGraph() {}
  
     Vertex<T> * insertVertex(int ve);
    Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e);
    void insertEdge_int(int v, int w, int o);
    void endVertices(int o);
    void endVertices(Edge<T> *e);
    Vertex<T> * opposite(Vertex<T> *v, Edge<T> *e);
    void replace(Vertex<T> *v, int x);
    void replace(Edge<T> *v, int x);
    void removeVertex(Vertex<T> *v);
    void areAdjacent(Vertex<T> *v, Vertex<T> *w);
    void removeEdge(Edge<T> *e);
    std::vector<Edge<T>*> incidentEdges(Vertex<T> *v);
    void vertices();
    void edges();
    void print();
    static std::unique_ptr<Graph<T>> createGraph(std::istream &is);
    std::list<Vertex<T>*> get_vertices()
    {
        std::list<Vertex<T>*> v;
        for(auto& vertex : v_list)
        {
            v.push_back(&vertex);
        }
        return v;
    }
    std::list<Edge<T>*> get_edges(){
        std::list<Edge<T>*> e;
        for(auto& edge : e_list)
        {
            e.push_back(&edge);
        }
        return e;
    }

};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
