#include "Scena.hh"
#include <iostream>
using namespace std;

/*!
 *  \brief Inicjalizuje połączenie z programem gnuplot oraz rozmiar świata.
 *
 *  Inicjalizuje podstawowe parametry "swiata", tzn. jego wymiary,
 *  które będą widoczne jako obszar objęty układem współrzędnych.
 *  Następnie w tle uruchamiany jest program gnuplot.
 *  \param[in] rLacze - nieaktywne łącze do gnuplota.
 */
void Scena::Inicjalizuj_Lacze(PzG::LaczeDoGNUPlota &rLacze) {
  rLacze.ZmienTrybRys(PzG::TR_3D);
  rLacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X / 2, ROMIAR_POWIERZCHNI_X / 2);
  rLacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y / 2, ROMIAR_POWIERZCHNI_Y / 2);
  rLacze.UstawZakresZ(-0, 90);
  rLacze.UstawRotacjeXZ(40, 60); // Tutaj ustawiany jest widok

  rLacze.Inicjalizuj(); // Tutaj startuje gnuplot.
}

void Scena::DodajDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze,
                                  const ObiektGeom &rOb) {
  PzG::InfoPlikuDoRysowania *wInfoPliku;

  wInfoPliku = &rLacze.DodajNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
  wInfoPliku->ZmienKolor(rOb.WezKolorID());
}

void Scena::UsunDoListyRysowania(PzG::LaczeDoGNUPlota &rLacze,
                                 const ObiektGeom &rOb) {
  // PzG::InfoPlikuDoRysowania *wInfoPliku;

  rLacze.UsunNazwePliku(rOb.WezNazwePliku_BrylaRysowana());
}

Scena::Scena() {

  double skala[3] = {20, 20, 10};
  Vector3D Skala(skala);

  double polozenie1[3] = {0, 0, 0};
 // double polozenie2[3] = {-40, -10, 0};
  double polozenie3[3] = {-80, 0, 0};
   double polozenie4[3] = {40, 0, 0};
  double polozenie5[3] = {40, 0, 0};
    double polozenie6[3] = {0, 40, 0};

  Vector3D Polozenie1(polozenie1);
  //Vector3D Polozenie2(polozenie2);
  Vector3D Polozenie3(polozenie3);
  Vector3D Polozenie4(polozenie4);
  Vector3D Polozenie5(polozenie5);
  Vector3D Polozenie6(polozenie6);

  // 135 315
  ObiektLista.push_back(make_shared<LazikSFR>("../bryly_wzorcowe/szescian3.dat",
                                              "FSR", Kolor_JasnoNiebieski,
                                              Skala, Polozenie1, 0, 10, 33));
  // ObiektLista.push_back(make_shared<Lazik>("../bryly_wzorcowe/szescian3.dat",
  //                                          "Perseverance", Kolor_Czerwony,
  //                                          Skala, Polozenie2, 0, 10, 15));

  ObiektLista.push_back(make_shared<ProbkaRegolitu>(
      "../bryly_wzorcowe/szescian2.dat", "Coulettes", Kolor_Czerwony,
      Skala * 0.2, Polozenie3, 0));
  ObiektLista.push_back(
      make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Salette",
                                  Kolor_Czerwony, Skala * 0.2, Polozenie4, 0));

    ObiektLista.push_back(
      make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Louda",
                                  Kolor_Czerwony, Skala * 0.2, Polozenie6, 0));
                                  ObiektLista.push_back(
      make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Salette2",
                                  Kolor_Czerwony, Skala * 0.2, Polozenie4*1.3, 0));
  // ObiektLista.push_back(
  //     make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Dourbes2",
  //                                 Kolor_Czerwony, Skala * 0.2, Polozenie5*1.3, 0));
    ObiektLista.push_back(
      make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Louda2",
                                  Kolor_Czerwony, Skala * 0.2, Polozenie6*1.3, 0));
  //                                   ObiektLista.push_back(
  //     make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Salette3",
  //                                 Kolor_Czerwony, Skala * 0.2, Polozenie4*(-1.5), 0));
  // ObiektLista.push_back(
  //     make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Dourbes3",
  //                                 Kolor_Czerwony, Skala * 0.2, Polozenie5*(-0.9), 0));
  //   ObiektLista.push_back(
  //     make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", "Louda3",
  //                                 Kolor_Czerwony, Skala * 0.2, Polozenie6*(-0.9), 0));

  for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
    DodajDoListyRysowania(Lacze, *Ob);
    Ob->Przelicz_i_Zapisz_Wierzcholki();
  }

  Inicjalizuj_Lacze(Lacze);

  if (!Inicjalizuj_PowierzchnieMarsa(Lacze))
    throw invalid_argument("Bledne dane");
  Lacze.Rysuj();
}

shared_ptr<Lazik> Scena::WybierzLazik(unsigned int wybor) {
  unsigned int i = 0;

  for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {

    ++i;

    DodajDoListyRysowania(Lacze, *Ob);
    Ob->Przelicz_i_Zapisz_Wierzcholki();

    this->WybranyLazik = dynamic_pointer_cast<Lazik>(Ob);

    if (i == wybor) {

      if (Ob->get_NazwaObiektu() == "FSR") {

        this->WybranyLazik = dynamic_pointer_cast<LazikSFR>(Ob);
        return dynamic_pointer_cast<LazikSFR>(Ob);
      }
      return dynamic_pointer_cast<Lazik>(Ob);
    }
  }
  cout << "Podano numer spoza zakresu. Wybrano lazik SFR" << endl;
  return nullptr;
}

void Scena::Odleglosc(double Odleglosc) {

  list<shared_ptr<ObiektGeom>> lista_tmp = ObiektLista;

  double tmp[3] = {Odleglosc, 0, 0};
  Vector3D jedz(tmp);
  Odleglosc = abs(Odleglosc);

  jedz = WybranyLazik->wypelnijRotZ(jedz, WybranyLazik->get_KatOrientacji());
  WybranyLazik->set_OdlegloscDoPrzejechania() = Odleglosc;
  cout << jedz << endl;

  int t = abs(Odleglosc);

  do {
   
    WybranyLazik->set_Polozenie() =
        WybranyLazik->get_Polozenie() + jedz / Odleglosc;
    WybranyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Lacze.Rysuj();

    for (shared_ptr<ObiektGeom> &Ob : lista_tmp) {
      list<shared_ptr<ObiektGeom>>::iterator it = ObiektLista.begin();
      ++it;

      if (WybranyLazik->WezNazweObiektu() != Ob->WezNazweObiektu()) {

        if (Ob->Czy_Zderzenie(WybranyLazik)) {

          // if (Ob->Czy_Zderzenie(WybranyLazik) == PrzejazdNadProbka) {

          //   shared_ptr<LazikSFR> lazikSFR;
          //   lazikSFR = dynamic_pointer_cast<LazikSFR>(WybranyLazik);
          // }

          cout << "Zderzenie podczas jazdy" << endl;
          cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie."
               << endl;
          //cin.ignore(100, '\n');

          t = 1;
        }
      }
    }
    usleep(600000 / WybranyLazik->get_Szybkosc());

  } while (--t);
}

// theta
void Scena::Obrot(double stopnie) {
if(stopnie==0) return;
  int t = abs(stopnie);
  double theta = (stopnie * M_PI) / 180;
  double czesc_obrotu = theta / t;

  

  do {

    WybranyLazik->set_KatOrientacji() += czesc_obrotu;

    WybranyLazik->Przelicz_i_Zapisz_Wierzcholki();
    Lacze.Rysuj();
    for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
      if (WybranyLazik->WezNazweObiektu() != Ob->WezNazweObiektu()) {

        if (Ob->Czy_Zderzenie(WybranyLazik)) {

          if (Ob->Czy_Zderzenie(WybranyLazik) == 1)

            cout << "Zderzenie podczas jazdy" << endl;
          cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie."
               << endl;
         // cin.ignore(100, '\n');
          t = 0;
        }
      }
    }
    usleep(100000 / WybranyLazik->get_Szybkosc());

  } while (--t);

}

void Scena::WyswietlListeProbek() {

  cout << "Lista probek na scenie: " << endl;
  int i = 0;

  for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
    // cout<<"Bryla Wzorcowa "<<Ob->get_NazwaPliku_BrylaWzorcowa() <<endl;

    if (Ob->get_NazwaPliku_BrylaWzorcowa() ==
        "../bryly_wzorcowe/szescian2.dat" ) {
      ++i;
      cout << i << ". " << Ob->get_NazwaObiektu() << endl;
    }
  }
  cout << endl;
}

void Scena::PodniesProbke() {

  //list<shared_ptr<ObiektGeom>> lista_tmp = ObiektLista;
  double wysoko[3] = {999, 999, 999};
  Vector3D Wysoko(wysoko);



  if (WybranyLazik->get_NazwaObiektu() != "FSR")
    cout << "Opcja dostępna tylko dla Lazika SFR! " << endl;

  else {
    auto it = ObiektLista.begin();
    for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
    
    
    

      if (WybranyLazik->WezNazweObiektu() != Ob->WezNazweObiektu()) {
  cout<<"Typ kolizji"<<Ob->Czy_Zderzenie(WybranyLazik)<<"\n";
        if (Ob->Czy_Zderzenie(WybranyLazik)) {

          if (Ob->Czy_Zderzenie(WybranyLazik) == PrzejazdNadProbka || Ob->Czy_Zderzenie(WybranyLazik) == KolizjaZProbka) {

            shared_ptr<LazikSFR> lazikSFR;
            lazikSFR = dynamic_pointer_cast<LazikSFR>(WybranyLazik);
            lazikSFR->Dodaj_Probke(Ob);
            Ob->set_Polozenie() = Wysoko;
            Ob->Przelicz_i_Zapisz_Wierzcholki();
            //Ob->set_NazwaObiektu() = "pobrana";
            
            Lacze.Rysuj();
      
            ObiektLista.erase(it);
        
           
            UsunDoListyRysowania(Lacze, *Ob);
            return;
            //lista_tmp = ObiektLista;
          }

          // cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie."
          //      << endl;
          // cin.ignore(100, '\n');
        //}
      }
  
    
    }
        ++it;
    }
}
}



void Scena::AutonomousDrive() {

  float delta_x, delta_y;
cout << "xd\n";
  for (list < shared_ptr < ObiektGeom >> ::iterator it = ObiektLista.begin(); it != ObiektLista.end(); it++) {
    cout << "xd\n";
    if (( * it) -> get_NazwaPliku_BrylaWzorcowa() == "../bryly_wzorcowe/szescian2.dat") {
      cout << "xd\n";
      cout << "Start lolo\n";
//   cout<<"Kolejne X: "<<(( * it) -> get_Polozenie().return_x())<< ", Y "<<(( * it) -> get_Polozenie().return_y())<<"\n";
//  cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie."
//                << endl;
        //  cin.ignore(100, '\n');


      delta_x = -WybranyLazik -> get_Polozenie().return_x() + ( * it) -> get_Polozenie().return_x();
      delta_y = -WybranyLazik -> get_Polozenie().return_y() + ( * it) -> get_Polozenie().return_y();
   
      float tan = (atan2(delta_y, delta_x)) * (180 / 3.14);
      // if(tan<0){
      //   tan+=(3.14/2);
      // }

//        cout<<"Kat obrotu: "<<tan-(WybranyLazik->get_KatOrientacji()* (180 / 3.14))<<"\n";
//  cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie."
  //             << endl;
        //  cin.ignore(100, '\n');
          
      Obrot(tan-(WybranyLazik->get_KatOrientacji()* (180 / 3.14)));
      Odleglosc(900);
      PodniesProbke();
      cout << "tangens" << tan << "\n";
      cout<<"Kat"<<-WybranyLazik->get_KatOrientacji()<<"\n";
     
      it = ObiektLista.begin();
  
  
    }
    //return;
    WyswietlListeProbek();
    cout<<"NE\n";
  }
   WyswietlListeProbek();
      return;
  cout << "Koniec\n";
}



void Scena::Menu() {
  int t = 1, wybor;
  char znak;
  double odleglosc, kat;

  WybierzLazik(1);
  AutonomousDrive();

  while (t) {
    cout << "--------------------------------------" << endl;
    cout << "j- jazda na wprost \no- zmien orientacje \np - podejmij probke "
            "(tylko dla SFR)\nw - wybor "
            "lazika \nl - lista probek na scenie \nm - wyswietl menu\n\nk - "
            "koniec "
            "dzialania programu \n--------------------------------------\nTwoj "
            "wybor, ";

    cin >> znak;
    switch (znak) {
    case 'j':
      cout << "Podaj odleglosc na ktora ma pojechac Lazik: " << endl;
      cin >> odleglosc;
      Odleglosc(odleglosc);

      break;
    case 'o':
      cout << "Podaj kat na ktory ma sie obrocic Lazik: " << endl;
      cin >> kat;
      Obrot(kat);

      break;
    case 'p':


      PodniesProbke();

  
  cout << endl;
      break;
    case 'w':
      cout << "Podaj nuemr Lazika, ktory chcesz wybrac: " << endl;
      cin >> wybor;
      WybierzLazik(wybor);

      break;
    case 'l':
      WyswietlListeProbek();
      break;
    case 'm':
      t = 0;
      break;
    case 'k':
      t = 0;
      break;
    default:
      cout << "Wybierz poprawna opcje.  " << endl;
      break;
    }
  }
}
