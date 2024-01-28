
#include "LazikSFR.hh"
#include <iostream>

using namespace std;

LazikSFR::LazikSFR(const char *sNazwaPliku_BrylaWzorcowa,
                   const char *sNazwaObiektu, int KolorID, Vector3D _Skala,
                   Vector3D _Polozenie, double _KatOrientacji, double predkosc,
                   double odleglosc)
    : Lazik(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, _Skala,
            _Polozenie, _KatOrientacji, predkosc, odleglosc) {

  //    wypalenie zawodowe mam ;()
}

//============================================================================
//_____________________ Czy_Zderzenie _________________________________

/*!
Funkcja sprawdza czy nastąpiło zderzenie
 */
TypKolizji LazikSFR::Czy_Zderzenie(shared_ptr<Lazik> &Akt) {

  // if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] >=
  // this->get_Obrys().get_Wierz_DolnyLewy()[0]){
  //     Vector2D tmp =this->get_Obrys().set_Wierz_DolnyLewy();
  // this->get_Obrys().set_Wierz_DolnyLewy()=Akt->get_Obrys().set_Wierz_DolnyLewy();
  // Akt->get_Obrys().set_Wierz_DolnyLewy()=tmp;

  //}

  if (Akt->get_Obrys().get_Wierz_DolnyLewy()[0] <=
          this->get_Obrys().get_Wierz_DolnyLewy()[0] &&
      ((Akt->get_Obrys().get_Wierz_DolnyLewy()[1] >=
            this->get_Obrys().get_Wierz_DolnyLewy()[1] &&
        Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <=
            this->get_Obrys().get_Wierz_GornyPrawy()[1]) ||
       (Akt->get_Obrys().get_Wierz_GornyPrawy()[1] <=
            this->get_Obrys().get_Wierz_GornyPrawy()[1] &&
        Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >=
            this->get_Obrys().get_Wierz_DolnyLewy()[1]) ||
       (Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >=
            this->get_Obrys().get_Wierz_GornyPrawy()[1] &&
        Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <=
            this->get_Obrys().get_Wierz_DolnyLewy()[1]))) {

    if (Akt->get_Obrys().get_Wierz_GornyPrawy()[0] >=
        this->get_Obrys().get_Wierz_DolnyLewy()[0]) {
      cout << "Kolizja!" << endl;

      return Kolizja;
    }

  } else if (Akt->get_Obrys().get_Wierz_DolnyLewy()[0] >=
                 this->get_Obrys().get_Wierz_DolnyLewy()[0] &&
             ((Akt->get_Obrys().get_Wierz_DolnyLewy()[1] >=
                   this->get_Obrys().get_Wierz_DolnyLewy()[1] &&
               Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <=
                   this->get_Obrys().get_Wierz_GornyPrawy()[1]) ||
              (Akt->get_Obrys().get_Wierz_GornyPrawy()[1] <=
                   this->get_Obrys().get_Wierz_GornyPrawy()[1] &&
               Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >=
                   this->get_Obrys().get_Wierz_DolnyLewy()[1]) ||
              (Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <=
                   this->get_Obrys().get_Wierz_DolnyLewy()[1] &&
               Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >=
                   this->get_Obrys().get_Wierz_GornyPrawy()[1]))) {

    if (Akt->get_Obrys().get_Wierz_DolnyLewy()[0] <=
        this->get_Obrys().get_Wierz_GornyPrawy()[0]) {
      cout << "Kolizja!" << endl;

      return Kolizja;
    }
  }
  return BrakKolizji;


}


// copying beacuse i have to chage name of probka for pobrana ezez
void LazikSFR::Dodaj_Probke(shared_ptr<ObiektGeom> &wsk_probka) {

  ListaObiektowNaLaziku.push_back(wsk_probka);
 
}

void LazikSFR::Wyswietl_Liste() {

  for (shared_ptr<ObiektGeom> &Ob : ListaObiektowNaLaziku) {

    cout << Ob->get_NazwaObiektu() << endl;
  }
}