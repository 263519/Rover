#pragma once
#include "Lazik.hh"

class Lazik;
class ProbkaRegolitu : public ObiektGeom {

public:
ProbkaRegolitu(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID,Vector3D Skala, Vector3D Polozenie, double stopnie);
virtual ~ProbkaRegolitu() {
    std::cout<<"ProbkaRegolitu Destructor is running\n";
}
virtual TypKolizji Czy_Zderzenie ( std::shared_ptr<Lazik> &Wsk_lazik) ;
};
