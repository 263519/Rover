#ifndef ADJACENCY_MATRIX_GRAPH_HPP_
#define ADJACENCY_MATRIX_GRAPH_HPP_

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "graph.hpp"
#include "Vertex_matrix.h"
#include "Edge_matrix.h"

template<typename T>
class AdjacencyMatrixGraph : public Graph<T> {
    std::list<Vertex_matrix<T>> v_list;
    int pos = 0;
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
    
    Vertex<T>* insertVertex(T ve) {
        for (auto& vertex : v_list) {
            if (vertex.Element_v() == ve) {   return &vertex;
            }
        }

        Vertex_matrix<T> ver(ve);
        v_list.push_back(ver);
        v_list.back().set_key(pos);
        v_list.back().set_Position(--v_list.end());
        ++pos;
        return &v_list.back();
    }
    
    Edge<T>* insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) {
        Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(v1);
        Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(v2);
        Edge_matrix<T> edge(e, start, end, --e_list.end());
        e_list.push_back(edge);
        adjacency_matrix[start->Key()][end->Key()] = &e_list.back();
        return &e_list.back();
    }
    
    void insertEdge_int(T v, T w, int o) {
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
    
    void areAdjacent(Vertex<T>* v, Vertex<T>* w) {
        Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(v);
        Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(w);
        std::cout << "Are adjacent: " << (adjacency_matrix[start->Key()][end->Key()] != nullptr) << std::endl;
    }
    
    Vertex<T>* opposite(Vertex<T>* v, Edge<T>* e) {
        if (v == e->End()) {
            return e->Start();
        } else if (v == e->Start()) {
            return e->End();
        } else {
            std::cout << "Error: the given Vertex<T> is not incident to the given edge." << std::endl;
            return nullptr;
        }
    }
    
    void replace(Vertex<T>* v, T x) {
        v->set_vertex_element(x);
    }
    
    void replace(Edge<T>* v, int x) {
        v->set_edge_element(x);
    }
    
    void removeVertex(Vertex<T>* v) {
        Vertex_matrix<T>* vertex = dynamic_cast<Vertex_matrix<T>*>(v);
        for (auto edge : adjacency_matrix[vertex->Key()]) {
            if (edge) {
                removeEdge(edge);
            }
        }
        adjacency_matrix.erase(adjacency_matrix.begin() + vertex->Key());
        v_list.erase(vertex->Position());
    }
    
    void removeEdge(Edge<T>* e) {
        Edge_matrix<T>* edge = dynamic_cast<Edge_matrix<T>*>(e);
        e_list.erase(edge->Position());
        Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(edge->Start());
        Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(edge->End());
        adjacency_matrix[start->Key()][end->Key()] = nullptr;
        adjacency_matrix[end->Key()][start->Key()] = nullptr;
    }
    
    std::vector<Edge<T>*> incidentEdges(Vertex<T>* v) {
        std::vector<Edge<T>*> incidentE;
        Vertex_matrix<T>* startVertex = dynamic_cast<Vertex_matrix<T>*>(v);
        for (const auto& x : adjacency_matrix[startVertex->Key()]) {
            if (x) {
                incidentE.push_back(x);
            }
        }
        return incidentE;
    }
    
    void vertices() {
        std::cout << "Vertices : ";
        for (const auto& vertex : v_list) {
            std::cout << vertex.Element_v() << " ";
        }
        std::cout << std::endl;
    }
    
    void edges() {
        for (const auto& edge : e_list) {
            std::cout << "Edge: (" << edge.Element_e() << ")-> ";
            std::cout << edge.Start()->Element_v();
            std::cout << "  " << edge.End()->Element_v() << std::endl;
        }
    }
    
    void print() {
        for (const auto& row : adjacency_matrix) {
            for (const auto& element : row) {
                if (element) {
                    std::cout << element->Element_e() << "  ";
                } else {
                    std::cout << "*  ";
                }
            }
            std::cout << std::endl;
        }
    }

    static std::unique_ptr<Graph<T>> createGraph(std::istream& is) {
        int num_vertices, num_edges;
        is >> num_vertices >> num_edges;
        std::unique_ptr<AdjacencyMatrixGraph<T>> graph = std::make_unique<AdjacencyMatrixGraph<T>>();
        graph->new_matrix(num_vertices, num_vertices);
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
#endif /* ADJACENCY_MATRIX_GRAPH_HPP_ */