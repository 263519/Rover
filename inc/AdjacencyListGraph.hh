#ifndef ADJACENCY_LIST_GRAPH_HH
#define ADJACENCY_LIST_GRAPH_HH

#include <memory>
#include <unordered_map>
#include <list>
#include <iostream>
#include "Graph.hh"
#include "EdgeAdj.hh"
#include "VertexAdj.hh"

template<typename T>
class AdjacencyListGraph : public Graph<T> {
    int numVer = 0;
    std::list<VertexAdj<T>> v_list;
    std::list<EdgeAdj<T>> e_list;

public:
    virtual ~AdjacencyListGraph() {}
  
    Vertex<T>* insertVertex(T ve) override {
        for (auto& vertex : v_list) {
            if (vertex.Element_v() == ve) {
                return &vertex;
            }
        }

        VertexAdj<T> ver(ve);
        VertexAdj<T>* v = &ver;

        v_list.push_back(*v);
        v_list.back().set_Position(--v_list.end());
        numVer++;

        return &v_list.back();
    }

    Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) override {
        VertexAdj<T>* start = dynamic_cast<VertexAdj<T>*>(v1);
        VertexAdj<T>* end = dynamic_cast<VertexAdj<T>*>(v2);

        EdgeAdj<T> edge(e, start, end, --e_list.end());

        e_list.push_back(edge);
        auto it = e_list.end();
        --it;
        e_list.back().set_Position(it);

        start->ADDEdge_adj(&e_list.back());
        e_list.back().set_Position_start(start->Position_edge());

        e_list.back().set_Position_end(end->Position_edge());

        return &e_list.back();
    }

    void print() override {
        std::cout << "Vertices ADJ:" << std::endl;
        for (auto tmp : v_list) {
            std::cout << "Vertex : (" << tmp.Element_v().first << ", " << tmp.Element_v().second << ") have Edge:";
            for (auto& t : tmp.list_Edge_adj()) {
                if (tmp.Position_edge() != tmp.list_Edge_adj().end()) {
                    std::cout << t->Element_e() << " |";
                }
            }
            std::cout << std::endl;
        }
    }
};

#endif /* ADJACENCY_LIST_GRAPH_HH */
