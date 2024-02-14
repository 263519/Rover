// #include "adjacency_list_graph.h"
// #include <algorithm>

// template<typename T>
// Vertex<T>* AdjacencyListGraph<T>::insertVertex(int ve) {
//     for (auto& vertex : v_list) {
//         if (vertex.Element_v() == ve) {
//             return &vertex;
//         }
//     }

//     Vertex_adj<T> ver(ve);
//     Vertex_adj<T>* v = &ver;

//     v_list.push_back(*v);
//     v_list.back().set_Position(--v_list.end());
//     //numVer++;

//     return &v_list.back();
// }

// template<typename T>
// Edge<T>* AdjacencyListGraph<T>::insertEdge(Vertex<T>* v1, Vertex<T>* v2, int e){
//     Vertex_adj<T>* start = dynamic_cast<Vertex_adj<T>*>(v1);
//     Vertex_adj<T>* end = dynamic_cast<Vertex_adj<T>*>(v2);

//     Edge_adj<T> edge(e, start, end, --e_list.end());

//     e_list.push_back(edge);
//     auto it = e_list.end();
//     --it;
//     e_list.back().set_Position(it);

//     start->ADDEdge_adj(&e_list.back());
//     e_list.back().set_Position_start(start->Position_edge());

//     e_list.back().set_Position_end(end->Position_edge());

//     return &e_list.back();
// }

// template<typename T>
// void AdjacencyListGraph<T>::insertEdge_int(int v, int w, int o) {
//     Vertex<T>* start = insertVertex(v);
//     Vertex<T>* end = insertVertex(w);
//     insertEdge(start, end, o);
// }

// template<typename T>
// void AdjacencyListGraph<T>::endVertices(int o) {
//     for (auto& edge : e_list) {
//         if (edge.Element_e() == o) {
//             std::cout << edge.Start()->Element_v() << " -> " << edge.End()->Element_v() << std::endl;
//         }
//     }
// }

// template<typename T>
// void AdjacencyListGraph<T>::endVertices(Edge<T>* e) {
//     std::cout << e->Start()->Element_v() << " -> " << e->End()->Element_v() << std::endl;
// }

// template<typename T>
// Vertex<T>* AdjacencyListGraph<T>::opposite(Vertex<T>* v, Edge<T>* e) {
//     if (v == e->End()) {
//         return e->Start();
//     } else if (v == e->Start()) {
//         return e->End();
//     } else {
//         std::cout << "Error: the given vertex is not incident to the given edge." << std::endl;
//     }

//     return v;
// }

// template<typename T>
// void AdjacencyListGraph<T>::replace(Vertex<T>* v, int x) {
//     v->set_vertex_element(x);
// }

// template<typename T>
// void AdjacencyListGraph<T>::replace(Edge<T>* v, int x) {
//     v->set_edge_element(x);
// }

// template<typename T>
// void AdjacencyListGraph<T>::removeVertex(Vertex<T>* v) {
//     Vertex_adj<T>* v_adj = dynamic_cast<Vertex_adj<T>*>(v);

//     auto edge_list = v_adj->list_Edge_adj();

//     for (auto& ed : edge_list) {
//         removeEdge(ed);
//     }

//     edge_list.clear();
//     v_list.erase(v_adj->Position());
// }

// template<typename T>
// void AdjacencyListGraph<T>::removeEdge(Edge<T>* e) {
//     Edge_adj<T>* edge = dynamic_cast<Edge_adj<T>*>(e);

//     Vertex_adj<T>* start = dynamic_cast<Vertex_adj<T>*>(edge->Start());
//     Vertex_adj<T>* end = dynamic_cast<Vertex_adj<T>*>(edge->End());

//     auto s = start->list_Edge_adj();
//     s.erase(edge->Position_start());

//     auto en = end->list_Edge_adj();
//     en.erase(edge->Position_end());

//     e_list.erase(edge->Position());
// }

// template<typename T>
// void AdjacencyListGraph<T>::areAdjacent(Vertex<T>* v, Vertex<T>* w) {
//     Vertex_adj<T>* v_adj = dynamic_cast<Vertex_adj<T>*>(v);
//     Vertex_adj<T>* w_adj = dynamic_cast<Vertex_adj<T>*>(w);

//     for (Edge_adj<T>* edge : v_adj->list_Edge_adj()) {
//         if (edge->End() == w_adj) {
//             std::cout << "Adjacent" << std::endl;
//             return;
//         } else if (edge->Start() == w_adj) {
//             std::cout << "Adjacent" << std::endl;
//             return;
//         }
//     }

//     std::cout << "Not adjacent" << std::endl;
// }

// template<typename T>
// std::vector<Edge<T>*> AdjacencyListGraph<T>::incidentEdges(Vertex<T>* v) {
//     Vertex_adj<T>* v_adj = dynamic_cast<Vertex_adj<T>*>(v);
//     std::vector<Edge<T>*> vect;
//     auto edge_list = v_adj->list_Edge_adj();

//     for (auto t : edge_list) {
//         vect.push_back(t);
//     }

//     return vect;
// }

// template<typename T>
// void AdjacencyListGraph<T>::vertices() {
//     std::cout << "Vertices:" << std::endl;
//     for (auto& vertex : v_list) {
//         std::cout << vertex.Element_v() << " ";
//     }
//     std::cout << std::endl;
// }

// template<typename T>
// void AdjacencyListGraph<T>::edges() {
//     std::cout << "Edges:" << std::endl;
//     for (auto& edge : e_list) {
//         std::cout << "Edge(" << edge.Element_e() << ") " << edge.Start()->Element_v() << " -> " << edge.End()->Element_v() << std::endl;
//     }
// }

// template<typename T>
// void AdjacencyListGraph<T>::print() {
//     std::cout << "Vertices ADJ:" << std::endl;
//     for (auto tmp : v_list) {
//         std::cout << "Vertex : " << tmp.Element_v() << " have Edge:";
//         for (auto& t : tmp.list_Edge_adj()) {
//             if (tmp.Position_edge() != tmp.list_Edge_adj().end()) {
//                 std::cout << t->Element_e() << " |";
//             }
//         }
//         std::cout << std::endl;
//     }
// }

// template<typename T>
// std::unique_ptr<Graph<T>> AdjacencyListGraph<T>::createGraph(std::istream& is) {
//     int num_vertices, num_edges;
//     is >> num_vertices >> num_edges;

//     std::unique_ptr<AdjacencyListGraph<T>> graph = std::make_unique<AdjacencyListGraph<T>>();
//     for (int i = 0; i < num_edges; ++i) {
//         int u, v, l;

//         is >> u >> v >> l;
//         graph->insertEdge_int(u, v, l);
//     }

//     return graph;
// }

