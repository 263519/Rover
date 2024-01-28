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




class Scena {
PzG::LaczeDoGNUPlota Lacze;
std::shared_ptr<Lazik> WybranyLazik;
std::list<std::shared_ptr<ObiektGeom>>ObiektLista;



public:
std::shared_ptr<Lazik> get_WybranyLazik() {return WybranyLazik;}
std::shared_ptr<Lazik> &set_WybranyLazik() {return WybranyLazik;}



Scena();
void DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze, const ObiektGeom  &rOb);
void UsunDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze,const ObiektGeom  &rOb);
void Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota  &rLacze);
std::shared_ptr<Lazik> WybierzLazik(unsigned int wybor);
void Odleglosc(double Odleglosc);
void Obrot(double theta);
void WyswietlListeProbek();
void Menu();
void PodniesProbke();

~Scena(){
    std::cout<<"Scena Destructor is running\n";
}




};