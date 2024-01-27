#pragma once

#include <string>
#include "ObiektGeom.hh"
#include "lacze_do_gnuplota.hh"
#include<unistd.h>


typedef SMatrix<double, 3> Matrix3D; 


class Lazik : public ObiektGeom{
  
    double Szybkosc;
    double OdlegloscDoPrzejechania;

public:

double get_OdlegloscDoPrzejechania() {return OdlegloscDoPrzejechania;}
double &set_OdlegloscDoPrzejechania() {return OdlegloscDoPrzejechania;}
double get_Szybkosc() {return Szybkosc;}
double &set_Szybkosc() {return Szybkosc;}

Lazik();
Lazik(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID,Vector3D Skala, Vector3D Polozenie,double stopnie,double predkosc,double odleglosc);



virtual TypKolizji Czy_Zderzenie ( std::shared_ptr<Lazik> &Wsk_lazik) ;

};