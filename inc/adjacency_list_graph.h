#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <memory>
#include <unordered_map>
#include <list>
#include <iostream>
#include "graph.hpp"
#include "Edge_adj.h"
#include "Vertex_adj.h"

template<typename T>
class AdjacencyListGraph : public Graph<T>
{
    int numVer = 0;
    std::list<Vertex_adj<T>> v_list;
    std::list<Edge_adj<T>> e_list;

public:
    virtual ~AdjacencyListGraph() {}
  
  Vertex<T>* insertVertex(T ve) {
    for (auto& vertex : v_list) {
        if (vertex.Element_v() == ve) {
            return &vertex;
        }
    }

    Vertex_adj<T> ver(ve);
    Vertex_adj<T>* v = &ver;

    v_list.push_back(*v);
    v_list.back().set_Position(--v_list.end());
    numVer++;

    return &v_list.back();
}

    Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e){
        Vertex_adj<T>* start = dynamic_cast<Vertex_adj<T>*>(v1);
        Vertex_adj<T>* end = dynamic_cast<Vertex_adj<T>*>(v2);

        Edge_adj<T> edge(e, start, end, --e_list.end());

        e_list.push_back(edge);
        auto it = e_list.end();
        --it;
        e_list.back().set_Position(it);

        start->ADDEdge_adj(&e_list.back());
        e_list.back().set_Position_start(start->Position_edge());

        e_list.back().set_Position_end(end->Position_edge());

        return &e_list.back();
    }

    void insertEdge_int(int v, int w, int o) {
        Vertex<T>* start = insertVertex(v);
        Vertex<T>* end = insertVertex(w);
        insertEdge(start, end, o);
    }

    void endVertices(int o) {
        for (auto& edge : e_list) {
            if (edge.Element_e() == o) {
                std::cout << edge.Start()->Element_v() << " -> " << edge.End()->Element_v() << std::endl;
            }
        }
    }

    void endVertices(Edge<T>* e) {
        std::cout << e->Start()->Element_v() << " -> " << e->End()->Element_v() << std::endl;
    }

    Vertex<T>* opposite(Vertex<T>* v, Edge<T>* e) {
        if (v == e->End()) {
            return e->Start();
        } else if (v == e->Start()) {
            return e->End();
        } else {
            std::cout << "Error: the given vertex is not incident to the given edge." << std::endl;
        }

        return v;
    }

    void replace(Vertex<T>* v, int x) {
        v->set_vertex_element(x);
    }

    void replace(Edge<T>* v, int x) {
        v->set_edge_element(x);
    }

    void removeVertex(Vertex<T>* v) {
             Vertex_adj<T> *v_adj = dynamic_cast<Vertex_adj<T> *>(v);

       // v_list.erase(v_adj->Position());
        auto edge_list = v_adj->list_Edge_adj();

        for (auto & ed : edge_list) {
            removeEdge(ed);
        }


       // cout<<v_adj->list_Edge_adj().front()->Element_e()<<endl;
        edge_list.clear();
       v_list.erase(v_adj->Position());
    }

    void removeEdge(Edge<T>* e) {
        Edge_adj<T>* edge = dynamic_cast<Edge_adj<T>*>(e);

        Vertex_adj<T>* start = dynamic_cast<Vertex_adj<T>*>(edge->Start());
        Vertex_adj<T>* end = dynamic_cast<Vertex_adj<T>*>(edge->End());

        auto s = start->list_Edge_adj();
        s.erase(edge->Position_start());

        auto en = end->list_Edge_adj();
        en.erase(edge->Position_end());

        e_list.erase(edge->Position());
    }

    void areAdjacent(Vertex<T>* v, Vertex<T>* w) {
        Vertex_adj<T>* v_adj = dynamic_cast<Vertex_adj<T>*>(v);
        Vertex_adj<T>* w_adj = dynamic_cast<Vertex_adj<T>*>(w);

        for (Edge_adj<T>* edge : v_adj->list_Edge_adj()) {
            if (edge->End() == w_adj) {
                std::cout << "Adjacent" << std::endl;
                return;
            } else if (edge->Start() == w_adj) {
                std::cout << "Adjacent" << std::endl;
                return;
            }
        }

        std::cout << "Not adjacent" << std::endl;
    }

    std::vector<Edge<T>*> incidentEdges(Vertex<T>* v) {
        Vertex_adj<T>* v_adj = dynamic_cast<Vertex_adj<T>*>(v);
        std::vector<Edge<T>*> vect;
        auto edge_list = v_adj->list_Edge_adj();

        for (auto t : edge_list) {
            vect.push_back(t);
        }

        return vect;
    }

    void vertices() {
        std::cout << "Vertices:" << std::endl;
        for (auto& vertex : v_list) {
            std::cout << vertex.Element_v() << " ";
        }
        std::cout << std::endl;
    }

    void edges() {
        std::cout << "Edges:" << std::endl;
        for (auto& edge : e_list) {
            std::cout << "Edge(" << edge.Element_e() << ") " << edge.Start()->Element_v() << " -> " << edge.End()->Element_v() << std::endl;
        }
    }

    void print() {
        std::cout << "Vertices ADJ:" << std::endl;
        for (auto tmp : v_list) {
            std::cout << "Vertex : " << tmp.Element_v() << " have Edge:";
            for (auto& t : tmp.list_Edge_adj()) {
                if (tmp.Position_edge() != tmp.list_Edge_adj().end()) {
                    std::cout << t->Element_e() << " |";
                }
            }
            std::cout << std::endl;
        }
    }

    static std::unique_ptr<Graph<T>> createGraph(std::istream& is) {
        int num_vertices, num_edges;
        is >> num_vertices >> num_edges;

        std::unique_ptr<AdjacencyListGraph<T>> graph = std::make_unique<AdjacencyListGraph<T>>();
        for (int i = 0; i < num_edges; ++i) {
            int u, v, l;

            is >> u >> v >> l;
            graph->insertEdge_int(u, v, l);
        }

        return graph;
    }

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
