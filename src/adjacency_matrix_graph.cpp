#include "adjacency_matrix_graph.h"
#include <memory>

template<typename T>
Vertex<T>* AdjacencyMatrixGraph<T>::insertVertex(T ve) {
    for (auto& vertex : v_list) {
        if (vertex.Element_v() == ve) {
            return &vertex;
        }
    }

    Vertex_matrix<T> ver(ve);
    v_list.push_back(ver);
    v_list.back().set_key(pos);
    v_list.back().set_Position(--v_list.end());
    ++pos;
    return &v_list.back();
}

template<typename T>
Edge<T>* AdjacencyMatrixGraph<T>::insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e) {
    Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(v1);
    Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(v2);
    Edge_matrix<T> edge(e, start, end, --e_list.end());
    e_list.push_back(edge);
    adjacency_matrix[start->Key()][end->Key()] = &e_list.back();
    return &e_list.back();
}

template<typename T>
void AdjacencyMatrixGraph<T>::insertEdge_int(T v, T w, int o) {
    Vertex<T>* start = insertVertex(v);
    Vertex<T>* end = insertVertex(w);
    insertEdge(start, end, o);
}

template<typename T>
void AdjacencyMatrixGraph<T>::endVertices(int o) {
    for (auto& edge : e_list) {
        if (edge.Element_e() == o) {
            std::cout << edge.Start()->Element_v() << " -> " << edge.End()->Element_v() << std::endl;
        }
    }
}

template<typename T>
void AdjacencyMatrixGraph<T>::endVertices(Edge<T>* e) {
    std::cout << e->Start()->Element_v() << " -> " << e->End()->Element_v() << std::endl;
}

template<typename T>
void AdjacencyMatrixGraph<T>::areAdjacent(Vertex<T>* v, Vertex<T>* w) {
    Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(v);
    Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(w);
    std::cout << "Are adjacent: " << (adjacency_matrix[start->Key()][end->Key()] != nullptr) << std::endl;
}

template<typename T>
Vertex<T>* AdjacencyMatrixGraph<T>::opposite(Vertex<T>* v, Edge<T>* e) {
    if (v == e->End()) {
        return e->Start();
    } else if (v == e->Start()) {
        return e->End();
    } else {
        std::cout << "Error: the given Vertex<T> is not incident to the given edge." << std::endl;
        return nullptr;
    }
}

template<typename T>
void AdjacencyMatrixGraph<T>::replace(Vertex<T>* v, T x) {
    v->set_vertex_element(x);
}

template<typename T>
void AdjacencyMatrixGraph<T>::replace(Edge<T>* v, int x) {
    v->set_edge_element(x);
}

template<typename T>
void AdjacencyMatrixGraph<T>::removeVertex(Vertex<T>* v) {
    Vertex_matrix<T>* vertex = dynamic_cast<Vertex_matrix<T>*>(v);
    for (auto edge : adjacency_matrix[vertex->Key()]) {
        if (edge) {
            removeEdge(edge);
        }
    }
    adjacency_matrix.erase(adjacency_matrix.begin() + vertex->Key());
    v_list.erase(vertex->Position());
}

template<typename T>
void AdjacencyMatrixGraph<T>::removeEdge(Edge<T>* e) {
    Edge_matrix<T>* edge = dynamic_cast<Edge_matrix<T>*>(e);
    e_list.erase(edge->Position());
    Vertex_matrix<T>* start = dynamic_cast<Vertex_matrix<T>*>(edge->Start());
    Vertex_matrix<T>* end = dynamic_cast<Vertex_matrix<T>*>(edge->End());
    adjacency_matrix[start->Key()][end->Key()] = nullptr;
    adjacency_matrix[end->Key()][start->Key()] = nullptr;
}

template<typename T>
std::vector<Edge<T>*> AdjacencyMatrixGraph<T>::incidentEdges(Vertex<T>* v) {
    std::vector<Edge<T>*> incidentE;
    Vertex_matrix<T>* startVertex = dynamic_cast<Vertex_matrix<T>*>(v);
    for (const auto& x : adjacency_matrix[startVertex->Key()]) {
        if (x) {
            incidentE.push_back(x);
        }
    }
    return incidentE;
}

template<typename T>
void AdjacencyMatrixGraph<T>::vertices() {
    std::cout << "Vertices : ";
    for (const auto& vertex : v_list) {
        std::cout << vertex.Element_v() << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void AdjacencyMatrixGraph<T>::edges() {
    for (const auto& edge : e_list) {
        std::cout << "Edge: (" << edge.Element_e() << ")-> ";
        std::cout << edge.Start()->Element_v();
        std::cout << "  " << edge.End()->Element_v() << std::endl;
    }
}

template<typename T>
void AdjacencyMatrixGraph<T>::print() {
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

template<typename T>
std::unique_ptr<Graph<T>> AdjacencyMatrixGraph<T>::createGraph(std::istream& is) {
    int num_vertices, num_edges;
    is >> num_vertices >> num_edges;
    std::unique_ptr<AdjacencyMatrixGraph<T>> graph = std::make_unique<AdjacencyMatrixGraph<T>>();
    graph->new_matrix(num_vertices, num_vertices);
    for (int i = 0; i < num_edges; ++i) {
        T u, v;
        int l;
        is >> u >> v >> l;
        graph->insertEdge_int(u, v, l);
    }
    return graph;
}
