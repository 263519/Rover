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


constexpr int ilosc_watkow = 1;




void* AutonomousDriveThreads(void * argument){
  Scena *id = (*Scena)argument;
  cout<<id<<"\n";
  // WybierzLazik(id);
  // AutonomousDrive();

  pthread_exit(0);
}


int main() {
  // PzG::LaczeDoGNUPlota  Lacze;
  Scena *s = new Scena();

  s->Menu();
 


  pthread_t roboty[ilosc_watkow];

  for(long i=0; i< ilosc_watkow; i++){
    pthread_create(&roboty[i], NULL, AutonomousDriveThreads, (void *)s);
  }



  cout << "Nacisnij klawisz ENTER, aby zakonczyc." << endl;
  cin.ignore(100, '\n');


for(int i=0; i< ilosc_watkow; i++){
    pthread_join(roboty[i], NULL);
}

}

