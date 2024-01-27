#include "Kolory.hh"
#include "Lazik.hh"
#include "ObrysXY.hh"
#include "PowierzchniaMarsa.hh"
#include "Scena.hh"
#include "lacze_do_gnuplota.hh"
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

using namespace std;

int main() {
  // PzG::LaczeDoGNUPlota  Lacze;
  Scena Scena;

  Scena.Menu();
 

  // wybrany.Dodaj_Probke();

  cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie." << endl;
  cin.ignore(100, '\n');





  // cout<<"ILOSC WEKTOROW"<<Vector3D::IloscWek()<<endl;

  // wybrany->Przelicz_i_Zapisz_Wierzcholki();

  /*
   if (!Inicjalizuj_PowierzchnieMarsa(Lacze)) return 1;

 double skala[3]={20,20,10};
 Vector3D Skala(skala);





 double polozenie1[3]={0,0,0};
 double polozenie2[3]={60,30,0};
 double polozenie3[3]={-20,70,0};
 double polozenie4[3]={20, 0, 0};
 double polozenie5[3]={40, 0,0};


 Vector3D Polozenie1(polozenie1);
 Vector3D Polozenie2(polozenie2);
 Vector3D Polozenie3(polozenie3);
 Vector3D Polozenie4(polozenie4);
 Vector3D Polozenie5(polozenie5);


   shared_ptr<Lazik> l1 =
 make_shared<Lazik>("../bryly_wzorcowe/szescian3.dat","FSR",Kolor_JasnoNiebieski,
 Skala, Polozenie1,30,7,33); shared_ptr<Lazik> l2 =
 make_shared<Lazik>("../bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony,
 Skala,Polozenie2,270,7,33); shared_ptr<Lazik> l3 =
 make_shared<Lazik>("../bryly_wzorcowe/szescian3.dat","Curiosity",Kolor_Czerwony,
 Skala,Polozenie3,45,7,33);

 list<shared_ptr<Lazik>> LISTA;
 LISTA.push_back(l1);
 LISTA.push_back(l2);
 LISTA.push_back(l3);

  //Scena Scena();
  Scena.Inicjalizuj_Lacze(Lacze);



   Scena.DodajDoListyRysowania(Lacze,*l3);


   */

  /*
   l3->Przelicz_i_Zapisz_Wierzcholki();


   cout << endl << "Start programu gnuplot" << endl << endl;
   Lacze.Rysuj();


   cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie." << endl;
   cin.ignore(100,'\n');
 l3->Odleglosc(22, Lacze);

   l3->Przelicz_i_Zapisz_Wierzcholki();
   Lacze.Rysuj();

   cout << "Nacisnij klawisz ENTER, aby FSR wykonal przesuniecie." << endl;
   cin.ignore(100,'\n');
 l3->Odleglosc(14, Lacze);


  l3->Przelicz_i_Zapisz_Wierzcholki();
   Lacze.Rysuj();
   */

  cout << "Nacisnij klawisz ENTER, aby zakonczyc." << endl;
  cin.ignore(100, '\n');
}
