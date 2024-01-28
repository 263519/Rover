#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include <memory>
#include "SVector.hh"
#include "SMatrix.hh"
#include "ObrysXY.hh"
#include "TypKolizji.hh"











#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "../pliki_do_rysowania"
class Lazik;
class ObiektGeom {
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;
    Vector3D      _Skala;
    Vector3D      _Polozenie;
    double        _KatOrientacji;   // RADIANY BOCIANY
    ObrysXY       _Obrys;
    
  public:
  ObrysXY &set_Obrys(){return _Obrys;}
    ObrysXY get_Obrys(){return _Obrys;}
  double get_KatOrientacji() {return _KatOrientacji;}
  double &set_KatOrientacji() {return _KatOrientacji;}
    Vector3D &set_Polozenie() {return _Polozenie;}
    Vector3D get_Polozenie() {return _Polozenie;}
    
    Vector3D &set_Skala() {return _Skala;}
    Vector3D get_Skala() {return _Skala;}
    
    std::string  get_NazwaObiektu() {return  _NazwaObiektu;}
    std::string  get_NazwaPliku_BrylaRysowana() {return _NazwaPliku_BrylaRysowana;}
    std::string  get_NazwaPliku_BrylaWzorcowa(){return _NazwaPliku_BrylaWzorcowa;}
      std::string  &set_NazwaObiektu() {return  _NazwaObiektu;}
    std::string  &set_NazwaPliku_BrylaRysowana() {return _NazwaPliku_BrylaRysowana;}
    std::string  &set_NazwaPliku_BrylaWzorcowa(){return _NazwaPliku_BrylaWzorcowa;}
  
    void Zapisz_Wierzcholki();
    bool Wpisz();

    

    //deklaracja konstruktora
    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID,Vector3D Skala, Vector3D Polozenie, double stopnie);
    virtual ~ObiektGeom(){
    
    std::cout<<"ObiektGeom Destructor is running\n";
    
    }



    int WezKolorID() const { return _KolorID; }
  
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
  
    const std::string & WezNazwePliku_BrylaRysowana() const
                 { return _NazwaPliku_BrylaRysowana; }

    bool Przelicz_i_Zapisz_Wierzcholki();

    Vector3D wypelnijRotZ(Vector3D v , double theta);

    virtual TypKolizji Czy_Zderzenie ( std::shared_ptr<Lazik> &Wsk_lazik)=0;
				     
};





#endif
