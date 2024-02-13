#pragma once
#include <iostream>
#include "Lazik.hh"
#include "lacze_do_gnuplota.hh"
#include <unistd.h>
#include <cmath>
#include <list>
#include <memory>
#include "Kolory.hh"
#include "Lazik.hh"
#include "PowierzchniaMarsa.hh"
#include "ProbkaRegolitu.hh"
#include <cstring>
#include "LazikSFR.hh"
#include <csignal>
#include <climits>
#include "adjacency_list_graph.h"
#include "adjacency_matrix_graph.h"



constexpr int ilosc_watkow = 1;


class Scena {
PzG::LaczeDoGNUPlota Lacze;
std::shared_ptr<Lazik> WybranyLazik;
std::list<std::shared_ptr<ObiektGeom>>ObiektLista;



public:
std::shared_ptr<Lazik> get_WybranyLazik() {return WybranyLazik;}
std::shared_ptr<Lazik> &set_WybranyLazik() {return WybranyLazik;}

//int thread_counter = 1;

Scena();
void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom  &rOb);
void UsunDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze,const ObiektGeom  &rOb);
void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze);
std::shared_ptr<Lazik> WybierzLazik(unsigned int wybor);
void Odleglosc(double Odleglosc);
void Obrot(double theta);
void WyswietlListeProbek();
void Menu();
std::list<std::shared_ptr<ObiektGeom>>::iterator  PodniesProbke();
void PlaceSample();

// void* AutonomousDriveThreads(){
// //   long id = (long)argument;
//    std::cout<<"Wszedl watek z nuemrem thread_counter"<<thread_counter<<"\n";
//   WybierzLazik(thread_counter);
//    thread_counter++;
//   AutonomousDrive();
//   pthread_exit(0);
// }

// static void *AutonomousDriveThreads_helper(void *context){
//     return ((Scena*) context)->AutonomousDriveThreads();
// }


void AutonomousDrive();
~Scena(){
    std::cout<<"Scena Destructor is running\n";
}




};

