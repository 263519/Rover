#include "Scena.hh"
#include <iostream>
using namespace std;
string usuniete_rzeczy;
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

  double polozenie1[3] = {-100, 0, 0};
   double polozenie2[3] = {0, 100, 0};
  // double polozenie3[3] = {-35, -40, 0};


  Vector3D Polozenie1(polozenie1);
  Vector3D Polozenie2(polozenie2);
  // Vector3D Polozenie3(polozenie3);
  

  // 135 315
  ObiektLista.push_back(make_shared<LazikSFR>("../bryly_wzorcowe/szescian3.dat",
                                              "FSRxpp", Kolor_JasnoNiebieski,
                                              Skala, Polozenie1, 0, 20, 33));
  ObiektLista.push_back(make_shared<LazikSFR>("../bryly_wzorcowe/szescian3.dat",
                                           "FSR", Kolor_JasnoNiebieski,
                                           Skala, Polozenie2, 0, 10, 15));

  //    ObiektLista.push_back(make_shared<LazikSFR>("../bryly_wzorcowe/szescian3.dat",
  //                                          "FSRorza", Kolor_JasnoNiebieski,
  //                                          Skala, Polozenie1*(-1)+Polozenie2*(-1), 0, 10, 15));
 

  PlaceSample();

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

      if (Ob->get_NazwaObiektu().find("FSR", 0)>=3){
    

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
//if(Odleglosc==0) return;
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
          t = 1;
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

list<shared_ptr<ObiektGeom>>::iterator Scena::PodniesProbke() {

  //list<shared_ptr<ObiektGeom>> lista_tmp = ObiektLista;
  double wysoko[3] = {999, 999, 999};
  Vector3D Wysoko(wysoko);



  if (WybranyLazik->get_NazwaObiektu().find("FSR", 0)>=3)
    cout << "Opcja dostępna tylko dla Lazika SFR! " << endl;

  else {
    auto it = ObiektLista.begin();
 
    for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
    
    
    

      if ((*it)->WezNazweObiektu() != "../bryly_wzorcowe/szescian3.dat") {
  
  cout<<"Typ kolizji"<<(*it)->Czy_Zderzenie(WybranyLazik)<<"\n";
        if ((*it)->Czy_Zderzenie(WybranyLazik)) {

          if ((*it)->Czy_Zderzenie(WybranyLazik) == PrzejazdNadProbka || (*it)->Czy_Zderzenie(WybranyLazik) == KolizjaZProbka) {

            shared_ptr<LazikSFR> lazikSFR;
            lazikSFR = dynamic_pointer_cast<LazikSFR>(WybranyLazik);
            lazikSFR->Dodaj_Probke((*it));
            (*it)->set_Polozenie() = Wysoko;
           (*it)->Przelicz_i_Zapisz_Wierzcholki();
            //Ob->set_NazwaObiektu() = "pobrana";
             usuniete_rzeczy+=' '+(*it)->WezNazweObiektu();
            Lacze.Rysuj();
      
        if ((*it)->WezNazweObiektu() != "../bryly_wzorcowe/szescian3.dat") {
            it=ObiektLista.erase(it);
        }
           
            UsunDoListyRysowania(Lacze, *Ob);
            return it;
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
    auto it = ObiektLista.begin();
    it++;
return it;
}

void Scena::PlaceSample(){
const char* names[] = {"Alice", "Bob", "Charlie", "David", "Emma", "Frank", "Grace", "Henry", "Ivy", "Jack", "Katie", "Liam", "Mia", "Noah", "Olivia", "Patrick", "Quinn", "Ryan", "Samantha", "Tyler","Alice1", "Bob1", "Charlie1", "David1", "Emma1", "Frank1", "Grace1", "Henry1", "Ivy1", "Jack1", "Katie1", "Liam1", "Mia1", "Noah1", "Olivia1", "Patrick1", "Quinn1", "Ryan1", "Samantha1", "Tyler1"};
AdjacencyListGraph<std::pair<int,int>>  l;

for(int i = 0 ; i<15 ; i++){
  double skala[3] = {20, 20, 10};
  Vector3D Skala(skala);

  double x = rand() % 200;
  double y = rand() % 200;
  double polozenie[3] = {x-100, y-100, 0};
  Vector3D Polozenie(polozenie);
  l.insertEdge(l.insertVertex({x,y}),l.insertVertex({0,0}),10);
      
   ObiektLista.push_back(
      make_shared<ProbkaRegolitu>("../bryly_wzorcowe/szescian2.dat", names[i],
     
                                  Kolor_Czerwony, Skala * 0.2, Polozenie, 0));


//  for (shared_ptr<ObiektGeom> &Ob : ObiektLista) {
//     DodajDoListyRysowania(Lacze, *Ob);
//     Ob->Przelicz_i_Zapisz_Wierzcholki();
//   }

  }

  l.print();
}



void Scena::AutonomousDrive() {

  float delta_x, delta_y;
  cout << "xd\n";

  //list < shared_ptr < ObiektGeom >> ::iterator it = ObiektLista.begin();
 while(1) {
list < shared_ptr < ObiektGeom >> ::iterator it = ObiektLista.begin();

int najkrotsza = INT_MAX;
   int probka_count = 0;
     for (list < shared_ptr < ObiektGeom >> ::iterator kt= ObiektLista.begin(); kt != ObiektLista.end(); ++kt) {
        if (( * kt) -> get_NazwaPliku_BrylaWzorcowa() != "../bryly_wzorcowe/szescian3.dat") {

                probka_count++;

           delta_x = -WybranyLazik -> get_Polozenie().return_x() + ( * kt) -> get_Polozenie().return_x();
      delta_y = -WybranyLazik -> get_Polozenie().return_y() + ( * kt) -> get_Polozenie().return_y();
      
        if(najkrotsza> sqrt(delta_x*delta_x + delta_y*delta_y)){
          najkrotsza = sqrt(delta_x*delta_x + delta_y*delta_y);
          it=kt;
        }
        list < shared_ptr < ObiektGeom >> ::iterator end = kt;
        end++;
        if(end == ObiektLista.end() && (najkrotsza == INT_MAX)){
          return;
        }


        }
     }

     if(!probka_count) return;
    cout << "xd\n";

    // if (( * it) -> get_NazwaPliku_BrylaWzorcowa() != "../bryly_wzorcowe/szescian3.dat") {
      cout << "xd\n";
      cout << WybranyLazik -> get_Polozenie().return_x() << " polozenie x\n";
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

      // cout << "Kat obrotu: " << tan - (WybranyLazik -> get_KatOrientacji() * (180 / 3.14)) << "\n";
      // cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie." <<
      //   endl;
      // cin.ignore(100, '\n');

      Obrot(tan - (WybranyLazik -> get_KatOrientacji() * (180 / 3.14)));
      Odleglosc(sqrt(delta_x*delta_x + delta_y*delta_y));
     it=PodniesProbke();
      cout << "tangens" << tan << "\n";
      cout << "Kat" << -WybranyLazik -> get_KatOrientacji() << "\n";
     // --it;
      //it = ObiektLista.begin()++;

      
    //}
 }
  //  else{
  //   ++it;
  //  }
//  for (list < shared_ptr < ObiektGeom >> ::iterator it= ObiektLista.begin(); it != ObiektLista.end(); ++it) {
 

//     if (( * it) -> get_NazwaPliku_BrylaWzorcowa() != "../bryly_wzorcowe/szescian3.dat") {
//         AutonomousDrive();
//     }
//  }

  cout << "Koniec\n";
}





void Scena::Menu() {
  int t = 1, wybor;
  char znak;
  double odleglosc, kat;



//WybierzLazik(1);


  while (t) {
    cout << "--------------------------------------" << endl;
    cout << "a - jazda autonomiczna \nj - jazda na wprost \no - zmien orientacje \np - podejmij probke "
            "(tylko dla SFR)\nw - wybor "
            "lazika \nl - lista probek na scenie \nm - wyswietl menu\n\nk - "
            "koniec "
            "dzialania programu \n--------------------------------------\nTwoj "
            "wybor, ";

    cin >> znak;
    switch (znak) {
     case 'a':
      cout << "Autonomous driving" << endl;
      AutonomousDrive();

      break;
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



  cout<<usuniete_rzeczy<<" Usuniete xpp\n";
}