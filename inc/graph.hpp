#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <list>
#include <iostream>
#include <vector>
using namespace std;
#include "Vertex.h"
#include "Edge.h"




//template<typename T>
class Graph
{
  protected:
    int numVer = 0;
    //vector<Vertex *> G_V;
   // vector<Edge *> G_E;
    // int  v_siz;
    //int e_siz;

  public:
    //Graph();
    //Graph(int V,int E);
   // virtual ~Graph() {}
   virtual Vertex * insertVertex(int ve) = 0 ;// dodaje wierzcjolek
   virtual Edge * insertEdge(Vertex * v, Vertex * w,int o)= 0;//v,w - wierzcholki o krawedz zle
   virtual void insertEdge_int(int v,int w,int o)= 0;//dobre
   virtual void endVertices(int o)= 0;// podaje krawedz zwraca wierzcholki
   virtual void endVertices(Edge  *e)= 0;
   virtual void areAdjacent(Vertex * v , Vertex * w)=0;
   virtual Vertex * opposite(Vertex  *v,Edge  *e)= 0;
   virtual void replace(Vertex  *v,int x)= 0;//zastap element w wierzcholku
   virtual void replace(Edge  *v,int x)= 0;// zastap element w krawedzi
   virtual void removeVertex(Vertex  *v)= 0;
   virtual void removeEdge(Edge  *e)= 0;
   virtual vector<Edge*> incidentEdges(Vertex  *v)= 0;
   virtual void vertices()= 0;
   virtual void edges()= 0;
   virtual void print()= 0;
   int numVertices() const
   {
       return numVer;
   }
   //vector<Vertex *>Get_Vec(){return G_V;}
   virtual std::list<Vertex*> get_vertices()=0;
   virtual std::list<Edge*> get_edges()=0;

  // virtual vector<Edge*> adjacentEdges(Vertex* u) const = 0;

};




//Graph::Graph(int V, int E){
   // cout<<"Create Graph with siz v,siz e"<<endl;

//}
/*Vertex<int>* Graph::insertVertex(int ve){


    int tmp = -1;
    for(auto & vertex : v_list){
        if(vertex.Element_v() == ve){
            tmp = ve;
            break;
        }
    }
    if(tmp != ve)
    {
        v_list.emplace_back(ve, --v_list.end()); // emplace_back. Dodaje element skonstruowany na końcu wektora.
    }
    v_list.emplace_back(ve, --v_list.end());
        return &v_list.back();
}
Edge<int>* Graph::insertEdge(Vertex<int> *v, Vertex<int> *w,int o){


        e_list.emplace_back(o,v,w,--e_list.end());
        return &e_list.back();
}
void Graph::insertEdge_int(int v, int w,int o){
        Vertex<int> *tmp;
        Vertex<int> *tmp1;
        bool czy_pol = false;
        bool czy_pol_1 = false;
        for(auto & vertex : v_list){
        if(vertex.Element_v() == v){
            tmp = &vertex;
            czy_pol =true ;
        }
        if(vertex.Element_v() == w){
            tmp1 = &vertex;
            czy_pol_1 = true;
        }
        }
        if(czy_pol == true && czy_pol_1 == true){
        e_list.emplace_back(o,tmp,tmp1,--e_list.end());
        }


        //e_list.emplace_back(o,v,w,e_list.end());

}
void Graph::endVertices(int o)
{
        for (auto& edge : e_list) {
        if(edge.Element_e() == o){
        cout<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
        }
        }

}
void Graph::endVertices(Edge<int> *e){
        cout<<e->Start()->Element_v()<<" -> "<< e->End()->Element_v() <<endl;
}

void Graph::opposite(Vertex<int> *v,Edge<int> *e){
        //Edge<int> *edge;
        Vertex<int> *vert;
        for(auto & edge : e_list)
        {
         if(edge.Position() == e->Position() && v == edge.End()){
         cout<<"Oposite to "<<v->Element_v()<<" Vertex is : "<<edge.Start()->Element_v()<<endl;
          }
         else if(edge.Position() == e->Position() && v == edge.Start()){
         cout<<"Oposite to "<<v->Element_v()<<" Vertex is : "<<edge.End()->Element_v()<<endl;
        }

        }
}

void Graph::replace(Vertex<int> *v,int x){
        //cout<<v->Element_v()<<endl;
        v->set_vertex_element(x);
        //cout<<v->Element_v()<<endl;
}
void Graph::replace(Edge<int> *v,int x){
        //for (auto& edge : e_list) {
        //if(edge.Position() == v->Position()){
        //cout<<v->Element_e()<<endl;
         v->set_edge_element(x);

}
void Graph::removeEdge(Edge<int>* e){//uzupelnij usuń krawędź e


         for (auto edge = e_list.begin(); edge != e_list.end();++edge ) {
        if (edge->Position() == e->Position()) {
         edge = e_list.erase(edge);
         //break;
                }
         }
}
void Graph::removeVertex(Vertex<int> *v)
{ // uzupelnij usuń wierzchołek v oraz przylegające krawędzie
         list<Edge<int>> tmp;
         for(auto& edge : e_list)
         {
                if(edge.Start() == v || edge.End() == v)
                {
                tmp.push_back(edge);
                }
         }
         for(auto& edge1 : tmp)
         {
                removeEdge(&edge1);
         }

                for(auto vertex = v_list.begin(); vertex != v_list.end(); ++vertex)
                {
         if(vertex->Position() == v->Position())
         {
             vertex = v_list.erase(vertex);

         }
                }

}
void Graph::incidentEdges(Vertex<int> *v){

         cout<<"Vertex : "<<v->Element_v()<<endl;
         cout<<"Have Edges : " ;
         for (auto& edge : e_list) {
        if(edge.Start() == v || edge.End() == v){
         cout<<edge.Element_e()<<" ";
        }

         }
         cout<<endl;
}
void Graph::vertices()
{
         cout<<"Vertex:"<<endl;
         for (auto& vertex : v_list) {
        cout << vertex.Element_v()<<endl;
         }
}
void Graph::edges()
{
         cout << "Edges:" << std::endl;
         for (auto& edge : e_list) {
        cout<<"Edge("<<edge.Element_e()<<") "<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
         }
}
void Graph::print() {
        cout<<"Vertex:"<<endl;
        for (auto& vertex : v_list) {
        cout << vertex.Element_v()<<endl;
        }
        cout << "Edges:" << std::endl;
        for (auto& edge : e_list) {
        cout<<"Edge("<<edge.Element_e()<<") "<<edge.Start()->Element_v() <<" -> "<< edge.End()->Element_v() <<endl;
        }
}*/



#endif /* GRAPH_HPP_ */
