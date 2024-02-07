#include "adjacency_list_graph.hpp"
#include <algorithm>





Vertex* AdjacencyListGraph::insertVertex(int ve) {
    for (auto& vertex : v_list) {
        if (vertex.Element_v() == ve) {
            return &vertex;
        }
    }

    Vertex_adj ver(ve);
    Vertex_adj* v = &ver;

    //v_list.push_back(ver);
    v_list.push_back(*v);
    //auto last_iter = std::prev(v_list.end());
    v_list.back().set_Position(--v_list.end());
     numVer++;
     //G_V.push_back(&v_list.back());
  //  cout<<&(*v_list.back().Position())<<endl;
    return &v_list.back();
}





Edge* AdjacencyListGraph::insertEdge(Vertex* v1, Vertex* v2, int e) {

    Vertex_adj* start = dynamic_cast<Vertex_adj*>(v1);
    Vertex_adj* end = dynamic_cast<Vertex_adj*>(v2);
  //  cout<<&(*start->Position())<<endl;


    Edge_adj edge(e, start, end, --e_list.end());
   // for (auto& ed : e_list) {
     //   if (ed.Element_e() == e) {
            //return &ed;
       // }
   // }

    e_list.push_back(edge);


    auto it = e_list.end();
   --it;
   e_list.back().set_Position(it) ;
   // start->AddAdjacentVertex(*end);
   // end->AddAdjacentVertex(*start);


    start->ADDEdge_adj(&e_list.back());
    e_list.back().set_Position_start(start->Position_edge());


   // end->ADDEdge_adj(&e_list.back());
    e_list.back().set_Position_end(end->Position_edge());







   // cout<<"tu"<<&*e_list.back().Position()<<endl;
    //G_E.push_back(&e_list.back());
    return &e_list.back();
}


void AdjacencyListGraph::insertEdge_int(int v,int w,int o)
{
    Vertex *  start = insertVertex(v);
    Vertex *  end = insertVertex(w);

   // Edge* edge = insertEdge(start,end,o);
    insertEdge(start,end,o);
}


void AdjacencyListGraph::endVertices(int o){

        for (auto& edge : e_list) {
            if(edge.Element_e() == o){
                cout<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
            }
        }

    }// podaje krawedz zwraca wierzcholki
void AdjacencyListGraph::endVertices(Edge  *e){
        cout<<e->Start()->Element_v()<<" -> "<< e->End()->Element_v() <<endl;
}


Vertex* AdjacencyListGraph::opposite(Vertex  *v,Edge  *e){


        if (v == e->End()) {
         //  cout << "Opposite vertex: " << e->Start() << endl;
           return e->Start();
        }
        else if (v == e->Start()) {
         //   cout << "Opposite vertex: " << e->End() << endl;
            return e->End();
        }
        else {
            cout << "Error: the given vertex is not incident to the given edge." << std::endl;
        }

        return v;

}
void AdjacencyListGraph::replace(Vertex  *v,int x){

        v->set_vertex_element(x);
}

void AdjacencyListGraph::replace(Edge  *v,int x){
        v->set_edge_element(x);
}



void AdjacencyListGraph::removeVertex(Vertex *v) {
        Vertex_adj *v_adj = dynamic_cast<Vertex_adj *>(v);

       // v_list.erase(v_adj->Position());
        auto edge_list = v_adj->list_Edge_adj();

        for (auto & ed : edge_list) {
            removeEdge(ed);
        }


       // cout<<v_adj->list_Edge_adj().front()->Element_e()<<endl;
        edge_list.clear();
       v_list.erase(v_adj->Position());




}

void AdjacencyListGraph::removeEdge(Edge *e)
{
        Edge_adj* edge = dynamic_cast<Edge_adj*>(e);

       Vertex_adj *start = dynamic_cast<Vertex_adj *>(edge->Start());
       Vertex_adj *end = dynamic_cast<Vertex_adj *>(edge->End());
       auto s = start->list_Edge_adj();
       s.erase(edge->Position_start());

       auto en = end->list_Edge_adj();
       en.erase(edge->Position_end());
       e_list.erase(edge->Position());



}

 void AdjacencyListGraph::areAdjacent(Vertex * v , Vertex * w){

       Vertex_adj* v_adj = dynamic_cast<Vertex_adj*>(v);
       Vertex_adj* w_adj = dynamic_cast<Vertex_adj*>(w);


       // Sprawdzamy, czy wierzchołek v_adj ma krawędź łączącą go z wierzchołkiem w_adj
       for (Edge_adj* edge : v_adj->list_Edge_adj()) {
            if (edge->End() == w_adj) {
                cout<<"som"<<endl;
                return ;
            }
            else if (edge->Start() == w_adj) {
                cout<<"som"<<endl;
                return ;
            }
       }

       // Wierzchołki v_adj i w_adj nie są sąsiednie
       cout<<"nie nie sa"<<endl;




}

vector<Edge*> AdjacencyListGraph::incidentEdges(Vertex  *v){
       Vertex_adj* v_adj = dynamic_cast<Vertex_adj*>(v);
      vector<Edge*>  vect;
       auto edge_list = v_adj->list_Edge_adj();
//cout<<"Vertex ("<<v_adj->Element_v()<<") have edge : ";
       for(auto t : edge_list){
            //cout<<t->Element_e()<<" ";
            vect.push_back(t);
}
cout<<endl;

return vect;
}

void AdjacencyListGraph::vertices(){
    cout<<"Vertexs:"<<endl;
    for ( auto& vertex : v_list) {
        std::cout << vertex.Element_v() << " ";
    }
    std::cout << std::endl;

}


void AdjacencyListGraph::edges(){

    cout << "Edges:" << std::endl;
    for (auto& edge : e_list) {
        cout<<"Edge("<<edge.Element_e()<<") "<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
    }
}


void AdjacencyListGraph::print(){

    cout<<"Vertexs ADJ:"<<endl;

for (auto tmp :v_list ){
        cout<<"Vertex : "<<tmp.Element_v()<<" have Edge:";

        for(auto& t : tmp.list_Edge_adj()){
           if(tmp.Position_edge() != tmp.list_Edge_adj().end()) {
               cout<<t->Element_e()<<" |";
           }
          //  cout<<&*t->Position_adj()<<"  /";
        }
        cout<<endl;
}
//cout<<v_siz<<endl;
  }



  // vector<Edge*> adjacentEdges(Vertex* u) const
  //{
//Vertex_adj* start = dynamic_cast<Vertex_adj*>(u);
   // std::vector<Edge*> adjacentEdges;

// Przechodzenie przez listę sąsiedztwa wierzchołka u
   // for (auto& edge : start->getEdges())
  //  {
    //    adjacentEdges.push_back(edge);
  //  }

  //  return adjacentEdges;
  ///}

  std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    int num_vertices, num_edges;
    is >> num_vertices >> num_edges;

    std::unique_ptr<AdjacencyListGraph> graph = std::make_unique<AdjacencyListGraph>();
   // graph->new_matrix(num_vertices,num_edges);
    for (int i = 0; i < num_edges; ++i) {
        int u, v, l;

        is >> u >> v >> l;
        graph->insertEdge_int(u, v, l);  // Wywołanie insertEdge na obiekcie graph
    }

    return graph;
}

