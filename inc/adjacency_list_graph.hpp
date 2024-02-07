#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>

#include "graph.hpp"
#include <unordered_map>


#include "Edge_adj.h"
//#include "ADJ.h"
#include "Vertex_adj.h"


class AdjacencyListGraph : public Graph
{

std::list<Vertex_adj> v_list;
//int  v_siz;
//int e_siz;

std::list<Edge_adj> e_list;


  public:

  //  AdjacencyListGraph(int v, int e) {
        //this->v_siz = v;
       // this->e_siz = e;


   // }
    virtual ~AdjacencyListGraph() {}
    Vertex * insertVertex(int ve);// dodaje wierzcjolek

    Edge * insertEdge(Vertex * v, Vertex * w,int o);//v,w - wierzcholki o krawedz
    void insertEdge_int(int v,int w,int o) ;
    void endVertices(int o);// podaje krawedz zwraca wierzcholki
    void endVertices(Edge  *e);
    Vertex * opposite(Vertex  *v,Edge  *e);
    void replace(Vertex  *v,int x);//zastap element w wierzcholku
    void replace(Edge  *v,int x);// zastap element w krawedzi
    void removeVertex(Vertex  *v);

    void areAdjacent(Vertex * v , Vertex * w);
    void removeEdge(Edge  *e);
    vector<Edge*> incidentEdges(Vertex  *v);
    void vertices();
    void edges();
    void print();
     //vector<Edge*> adjacentEdges(Vertex* u) const;
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



#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
