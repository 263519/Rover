#include "ProbkaRegolitu.hh"
using namespace std;

TypKolizji ProbkaRegolitu::Czy_Zderzenie(shared_ptr<Lazik> &Akt) {

  // if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] >=
  // this->get_Obrys().get_Wierz_DolnyLewy()[0]){
  //     Vector2D tmp =this->get_Obrys().set_Wierz_DolnyLewy();
  // this->get_Obrys().set_Wierz_DolnyLewy()=Akt->get_Obrys().set_Wierz_DolnyLewy();
  // Akt->get_Obrys().set_Wierz_DolnyLewy()=tmp;

  //}

  TypKolizji typ = BrakKolizji;

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

      typ = KolizjaZProbka;
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

      typ = KolizjaZProbka;
    }
  }

  if (typ == KolizjaZProbka) {
    typ = PrzejazdNadProbka;

    double tmp[3] = {Akt->get_OdlegloscDoPrzejechania(), 0, 0};
    Vector3D jedz(tmp);

    jedz = Akt->wypelnijRotZ(jedz, Akt->get_KatOrientacji());

    Vector3D r = Akt->get_Polozenie() - this->get_Polozenie();

    double iloczyn_dlugosci_wektorow =
        (sqrt(jedz[0] * jedz[0] + jedz[1] * jedz[1] + jedz[2] * jedz[2])) *
        (sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]));

    double sin_a =
        (jedz[0] * r[1] - jedz[1] * r[0]) / iloczyn_dlugosci_wektorow;

    double dlugosc_r = sqrt(r[0] * r[0] + r[1] + r[1]);

    double distance = abs(sin_a * dlugosc_r);

    if (distance > (Akt->get_Skala()[1] / 5))
      typ = KolizjaZProbka;

    if (typ == PrzejazdNadProbka)

      cout << "Kolizja z probka, ale mozna nad nia przejechac.  " << distance
           << endl;

    if (typ == KolizjaZProbka)

      cout << "Kolizja z probka!" << distance << endl;
  }

  return typ;
}

ProbkaRegolitu::ProbkaRegolitu(const char *sNazwaPliku_BrylaWzorcowa,
                               const char *sNazwaObiektu, int KolorID,
                               Vector3D _Skala, Vector3D _Polozenie,
                               double _KatOrientacji)
    : ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, _Skala,
                 _Polozenie, _KatOrientacji) {}
