// #include "Kolory.hh"
// #include "Lazik.hh"
// #include "ObrysXY.hh"
// #include "PowierzchniaMarsa.hh"
 #include "Scena.hh"
// #include "lacze_do_gnuplota.hh"
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include<thread>
//#include "adjacency_list_graph.hpp"
//#include "adjacency_matrix_graph.hpp"
//#include <pthread.h>

using namespace std;










int main() {
//     srand( time( NULL ) );
    //Scena s;

AdjacencyMatrixGraph<int>  e1;

AdjacencyListGraph<int> l, l2;
//e.new_matrix(10,10);
e1.new_matrix(10,10);
//e1.endVertices(2);
 l.insertVertex(2);
l.insertVertex(7);

 //e1.insertEdge(a1,a2, 7);
l.insertEdge(l.insertVertex(8),l.insertVertex(2), 5);
 e1.insertEdge(e1.insertVertex(8),e1.insertVertex(7), 9);
e1.print();
l.print();
cout<<"\n\n";
//   auto v1 = e.insertVertex(1);
//   auto v2 = e.insertVertex(2);
//    e.insertEdge(v1,v2,7);
    //e.insertEdge(v1,e.insertVertex(99),7);


 // e.print();

//     //std::thread t1(accumulator_function1, std::ref(s)); // Pass Scena object by reference
 
//     std::thread t2(accumulator_function2, std::ref(s)); // Pass Scena object by reference
//     //t1.join();
//     t2.join();
 


//  //pthread_t roboty[ilosc_watkow];

//   // for(long i=0; i< ilosc_watkow; i++){
//   //   pthread_create(&roboty[i], NULL, &Scena::AutonomousDriveThreads_helper, &s[i]);

//   // }



//   cout << "Nacisnij klawisz ENTER, aby zakonczyc." << endl;
//   cin.ignore(100, '\n');


// // for(int i=0; i< ilosc_watkow; i++){
// //     pthread_join(roboty[i], NULL);
// // }

}

