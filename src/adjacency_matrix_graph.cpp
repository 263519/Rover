#include "adjacency_matrix_graph.hpp"
#include <memory>


template<typename T>
Vertex * AdjacencyMatrixGraph::insertVertex(T ve){
    for (auto& vertex : v_list) {
        if (vertex.Element_v() == ve) {
            return &vertex;
        }
    }

    Vertex_matrix ver(ve);

    v_list.push_back(ver);
    //auto last_iter = std::prev(v_list.end());
    v_list.back().set_key(pos);
    //cout<<v_list.back().Key()<<endl;
    v_list.back().set_Position(--v_list.end());
    ++pos;
    //cout<<&(*ver.Position())<<endl;
   // G_V.push_back(&v_list.back());
    return &v_list.back();

}
Edge * AdjacencyMatrixGraph::insertEdge(Vertex * v1, Vertex * v2,int e){
    Vertex_matrix* start = dynamic_cast<Vertex_matrix*>(v1);
    Vertex_matrix* end = dynamic_cast<Vertex_matrix*>(v2);



    Edge_matrix edge(e, start, end, --e_list.end());

  // cout<<start->Key()<<endl;
  // cout<<end->Key()<<endl;
    e_list.push_back(edge);
    //e_list.back().set_Position(--e_list.end());
        adjacency_matrix[start->Key()][end->Key()] = &e_list.back();
        //adjacency_matrix[end->Key()][start->Key()] = &e_list.back();

     //   G_E.push_back(&e_list.back());
    return &e_list.back();



}
 // v,w - wierzcholki o krawedz zle
void AdjacencyMatrixGraph::insertEdge_int(T v,T w,int o){
    Vertex *  start = insertVertex(v);
    Vertex *  end = insertVertex(w);
    insertEdge(start,end,o);

}// dobre
void AdjacencyMatrixGraph::endVertices(T o){
    for (auto& edge : e_list) {
        if(edge.Element_e() == o){
            cout<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
        }
    }


}// podaje krawedz zwraca wierzcholki


void AdjacencyMatrixGraph::endVertices(Edge* e)
{
    cout << e->Start()->Element_v() << " -> " << e->End()->Element_v() << endl;
}
void AdjacencyMatrixGraph::areAdjacent(Vertex* v, Vertex* w)
{
    Vertex_matrix* start = dynamic_cast<Vertex_matrix*>(v);
    Vertex_matrix* end = dynamic_cast<Vertex_matrix*>(w);

    std::cout << "takie same " << (adjacency_matrix[start->Key()][end->Key()] != nullptr) << " takie same" << endl;
}
Vertex* AdjacencyMatrixGraph::opposite(Vertex* v, Edge* e)
{

    if(v == e->End())
    {
      //  cout << "Opposite vertex: " << e->Start()->Element_v() << endl;
        return e->Start();
    }
    else if(v == e->Start())
    {
       // cout << "Opposite vertex: " << e->End()->Element_v() << endl;
        return e->End();
    }
    else
    {
        cout << "Error: the given vertex is not incident to the given edge." << std::endl;
        return nullptr;
    }
}
void AdjacencyMatrixGraph::replace(Vertex* v, T x)
{
    v->set_vertex_element(x);
} // zastap element w wierz
void AdjacencyMatrixGraph::replace(Edge* v, int x)
{
    v->set_edge_element(x);
} // zastap element w wierz



void AdjacencyMatrixGraph::removeVertex(Vertex  *v){
    Vertex_matrix* vertex = dynamic_cast<Vertex_matrix*>(v);


    for(auto edge : adjacency_matrix[vertex->Key()]){
        if(edge){removeEdge(edge);}
    }
    adjacency_matrix.erase(adjacency_matrix.begin() + vertex->Key() );
    v_list.erase(vertex->Position());
}
void AdjacencyMatrixGraph::removeEdge(Edge  *e)
{
    Edge_matrix* edge = dynamic_cast<Edge_matrix*>(e);
    e_list.erase(edge->Position());
    Vertex_matrix* start = dynamic_cast<Vertex_matrix*>(edge->Start());
    Vertex_matrix* end = dynamic_cast<Vertex_matrix*>(edge->End());

    adjacency_matrix[start->Key()][end->Key()] = nullptr;
    adjacency_matrix[end->Key()][start->Key()] = nullptr;

}
vector<Edge*> AdjacencyMatrixGraph::incidentEdges(Vertex  *v){


    std::vector<Edge*> incidentE;
   // cout << "Incident edges: " << endl;
    Vertex_matrix* startVertex = dynamic_cast<Vertex_matrix*>(v);
    for(const auto& x : adjacency_matrix[startVertex->Key()])
    {
        if(x)
        {
           // cout << x->Element_e() << endl;
            incidentE.push_back(x);
        }
    }
    return incidentE;
}
void AdjacencyMatrixGraph::vertices(){

    cout<<"Vertices : ";
    for (const auto& vertex : v_list) {
        std::cout << vertex.Element_v() << " ";
    }
    std::cout<<endl;
}
void AdjacencyMatrixGraph::edges(){

        for ( auto& edge : e_list){
                std::cout << "Edge: (" << edge.Element_e() <<")-> ";
                cout << edge.Start()->Element_v() ;
                std::cout << "  " << edge.End()->Element_v() << std::endl;
        }

}
void AdjacencyMatrixGraph::print(){
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

       // cout<<v_siz<<endl;
}




 std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is) {
        int num_vertices, num_edges;
        is >> num_vertices >> num_edges;
        //Graph::v_siz =num_vertices;
        std::unique_ptr<AdjacencyMatrixGraph> graph = std::make_unique<AdjacencyMatrixGraph>();
graph->new_matrix(num_vertices,num_vertices );
        for (int i = 0; i < num_edges; ++i) {
                T u, v;
                int l;
                is >> u >> v >> l;
                graph->insertEdge_int(u, v, l);  // Wywołanie insertEdge na obiekcie graph
        }


//cout<<r<<endl;
        return graph;
}

