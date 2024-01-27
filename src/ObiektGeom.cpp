#include "ObiektGeom.hh"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

ObiektGeom::~ObiektGeom() { cout << "Destrukto" << endl; }

ObiektGeom::ObiektGeom(const char *sNazwaPliku_BrylaWzorcowa,
                       const char *sNazwaObiektu, int KolorID, Vector3D _Skala,
                       Vector3D _Polozenie, double stopnie)
    : _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID),
      _Skala(_Skala), _Polozenie(_Polozenie), _KatOrientacji(stopnie) {

  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  this->_Skala = _Skala;
  this->_Polozenie = _Polozenie;

  this->_KatOrientacji = (stopnie * M_PI) / 180;
}

//============================================================================
//_____________________ wypelnijRotZ _________________________________

/*!
 * Inicjalizuje obiekt.
 *  \param[in] v - Vector3D do obrotu
 *  \param[in] theta    - kat do obrotu w radianach,
 *  \param[out] rotated  - obrocony wektor
 */
Vector3D ObiektGeom::wypelnijRotZ(Vector3D v, double theta) {
  Vector3D rotated;
  double tmp[3][3] = {
      {cos(theta), -sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};
  Matrix3D RotationMat = Matrix3D(tmp);

  rotated = RotationMat * v;
  return rotated;
}
// theta - kat obrotu wektora
bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki() {
  ifstream StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl
         << "Nie mozna otworzyc jednego z plikow:" << endl
         << "    " << _NazwaPliku_BrylaWzorcowa << endl
         << "    " << _NazwaPliku_BrylaRysowana << endl
         << endl;

    return false;
  }

  Vector3D Wsp = Vector3D();
  int Indeks_Wiersza = 0;

  StrmWe >> Wsp;

  if (StrmWe.fail())
    return false;

  do {
    Wsp = Wsp * _Skala;
    Wsp = wypelnijRotZ(Wsp, _KatOrientacji);
    Wsp = Wsp + _Polozenie;

    StrmWy << Wsp[0] << " " << Wsp[1] << " " << Wsp[2] << endl;

    ++Indeks_Wiersza;

    if (Indeks_Wiersza >= 4) {
      StrmWy << endl;
      Indeks_Wiersza = 0;
    }

    StrmWe >> Wsp;

  } while (!StrmWe.fail());

  Zapisz_Wierzcholki();
  if (!StrmWe.eof())
    return false;

  return Indeks_Wiersza == 0 && !StrmWy.fail();
}

//============================================================================
//_____________________Zapisz_Wierzcholki() _________________________________

/*!
Funkcja zapisuje wierzcholki do obrysu z pliku
 */
void ObiektGeom::Zapisz_Wierzcholki() {

  ifstream Wejscie(_NazwaPliku_BrylaRysowana);
  double tab[24];
  //  double *tab =(double*) malloc(20*sizeof(double));
  for (int i = 0; i < 20; ++i) {
    Wejscie >> tab[i];
  }
  int i = 0;
  double tmp;
  int krotnosc = 0; // Wielokrotnosc kata (2kpi)
  krotnosc = _KatOrientacji / (2 * M_PI);

  if (((_KatOrientacji - krotnosc * 2 * M_PI >= M_PI / 2 &&
        _KatOrientacji - krotnosc * 2 * M_PI <= M_PI) ||
       (_KatOrientacji - krotnosc * 2 * M_PI >= 3 * M_PI / 2 &&
        _KatOrientacji - krotnosc * 2 * M_PI <= 2 * M_PI) ||
       (_KatOrientacji - krotnosc * 2 * M_PI >= -M_PI / 2 &&
        _KatOrientacji - krotnosc * 2 * M_PI <= 0) ||
       (_KatOrientacji - krotnosc * 2 * M_PI >= -3 * M_PI / 2 &&
        _KatOrientacji - krotnosc * 2 * M_PI <= -M_PI)) &&
      _KatOrientacji != 0) {
    i = 1;

    this->_Obrys.set_Wierz_DolnyLewy()[1] = tab[6 + i];
    this->_Obrys.set_Wierz_GornyPrawy()[0] = tab[4 - i];
    this->_Obrys.set_Wierz_GornyPrawy()[1] = tab[15 + i];
    this->_Obrys.set_Wierz_DolnyLewy()[0] = tab[19 - i];

  }

  else {

    this->_Obrys.set_Wierz_DolnyLewy()[0] = tab[6 + i];
    this->_Obrys.set_Wierz_DolnyLewy()[1] = tab[4 - i];
    this->_Obrys.set_Wierz_GornyPrawy()[0] = tab[15 + i];
    this->_Obrys.set_Wierz_GornyPrawy()[1] = tab[19 - i];
  }

  if (this->_Obrys.set_Wierz_DolnyLewy()[0] >
      this->_Obrys.set_Wierz_GornyPrawy()[0]) {
    tmp = this->_Obrys.set_Wierz_DolnyLewy()[0];
    this->_Obrys.set_Wierz_DolnyLewy()[0] =
        this->_Obrys.set_Wierz_GornyPrawy()[0];
    this->_Obrys.set_Wierz_GornyPrawy()[0] = tmp;
  }
  if (this->_Obrys.set_Wierz_DolnyLewy()[1] >
      this->_Obrys.set_Wierz_GornyPrawy()[1]) {
    tmp = this->_Obrys.set_Wierz_DolnyLewy()[1];
    this->_Obrys.set_Wierz_DolnyLewy()[1] =
        this->_Obrys.set_Wierz_GornyPrawy()[1];
    this->_Obrys.set_Wierz_GornyPrawy()[1] = tmp;
  }

  // free(tab);
  // tab = NULL;
}
