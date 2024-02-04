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
#include <pthread.h>

using namespace std;










int main() {
  // PzG::LaczeDoGNUPlota  Lacze;
  Scena s[3];
  

  //s.Menu();
 s[0].thread_counter=1;
 s[1].thread_counter=2;
 s[2].thread_counter=3;


  pthread_t roboty[ilosc_watkow];

  for(long i=0; i< ilosc_watkow; i++){
    pthread_create(&roboty[i], NULL, &Scena::AutonomousDriveThreads_helper, &s[i]);
  }



  cout << "Nacisnij klawisz ENTER, aby zakonczyc." << endl;
  cin.ignore(100, '\n');


for(int i=0; i< ilosc_watkow; i++){
    pthread_join(roboty[i], NULL);
}

}

