#pragma once
#include "Lazik.hh"
#include "ProbkaRegolitu.hh"


class LazikSFR : public Lazik{
    std::list<std::shared_ptr<ObiektGeom>> ListaObiektowNaLaziku;

    public:
    LazikSFR(const char*  sNazwaPliku_BrylaWzorcowa,
		        const char*  sNazwaObiektu,
		        int          KolorID,
            Vector3D _Skala, Vector3D _Polozenie,double _KatOrientacji, double predkosc,double odleglosc);


    virtual TypKolizji Czy_Zderzenie( std::shared_ptr<Lazik> &Wsk_lazik)  override;
    void Dodaj_Probke(std::shared_ptr<ObiektGeom> &wsk_probka);
    void Wyswietl_Liste();

    ~LazikSFR(){
        std::cout<<"LazikSFR destructor is running\n\n\n";

        std::cout<<"Lista obiektow na laziuku:\n";
        for(auto &x:ListaObiektowNaLaziku){
            std::cout<<x->get_NazwaObiektu()<<"\n";
        }

        std::cout<<"\n";
    }


};