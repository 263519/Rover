#include <iostream>
#include <fstream>
#include "Lazik.hh"
#include <unistd.h>
#include <cmath>



using namespace std;




Lazik::Lazik(const char*  sNazwaPliku_BrylaWzorcowa,
		        const char*  sNazwaObiektu,
		        int          KolorID,
            Vector3D _Skala, Vector3D _Polozenie,double _KatOrientacji, double predkosc,double odleglosc
		       ):ObiektGeom
               (
  sNazwaPliku_BrylaWzorcowa,sNazwaObiektu, KolorID, _Skala, _Polozenie,_KatOrientacji               )
{
  

this->OdlegloscDoPrzejechania=odleglosc;
this->Szybkosc=predkosc;

}




 





//============================================================================
 //_____________________ Czy_Zderzenie _________________________________

 /*!
 Funkcja sprawdza czy nastąpiło zderzenie
  */
TypKolizji Lazik::Czy_Zderzenie( shared_ptr<Lazik> &Akt){

// if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] >= this->get_Obrys().get_Wierz_DolnyLewy()[0]){
//     Vector2D tmp =this->get_Obrys().set_Wierz_DolnyLewy();
// this->get_Obrys().set_Wierz_DolnyLewy()=Akt->get_Obrys().set_Wierz_DolnyLewy();
// Akt->get_Obrys().set_Wierz_DolnyLewy()=tmp;

//}
                              
                 if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] <= this->get_Obrys().get_Wierz_DolnyLewy()[0] &&
                 ((Akt->get_Obrys().get_Wierz_DolnyLewy()[1] >= this->get_Obrys().get_Wierz_DolnyLewy()[1] && 
                 Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <= this->get_Obrys().get_Wierz_GornyPrawy()[1] )|| 
                 (Akt->get_Obrys().get_Wierz_GornyPrawy()[1] <= this->get_Obrys().get_Wierz_GornyPrawy()[1] && 
                 Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >= this->get_Obrys().get_Wierz_DolnyLewy()[1]
                 )|| (    Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >= this->get_Obrys().get_Wierz_GornyPrawy()[1] &&
                 Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <= this->get_Obrys().get_Wierz_DolnyLewy()[1] )) ){
                        
                   if(Akt->get_Obrys().get_Wierz_GornyPrawy()[0] >= this->get_Obrys().get_Wierz_DolnyLewy()[0]){
                     cout<<"Kolizja!"<<endl;
                


                     return Kolizja;
                   }
                   
                 }
                else if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] >= this->get_Obrys().get_Wierz_DolnyLewy()[0]
                 &&
                 ((Akt->get_Obrys().get_Wierz_DolnyLewy()[1] >= this->get_Obrys().get_Wierz_DolnyLewy()[1] && 
                 Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <= this->get_Obrys().get_Wierz_GornyPrawy()[1] )||
                 (Akt->get_Obrys().get_Wierz_GornyPrawy()[1] <= this->get_Obrys().get_Wierz_GornyPrawy()[1] && 
                 Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >= this->get_Obrys().get_Wierz_DolnyLewy()[1]
                 ) ||(    Akt->get_Obrys().get_Wierz_DolnyLewy()[1] <= this->get_Obrys().get_Wierz_DolnyLewy()[1] &&
                 Akt->get_Obrys().get_Wierz_GornyPrawy()[1] >= this->get_Obrys().get_Wierz_GornyPrawy()[1] )) ){
                   
                   if(Akt->get_Obrys().get_Wierz_DolnyLewy()[0] <= this->get_Obrys().get_Wierz_GornyPrawy()[0]){
                     cout<<"Kolizja!"<<endl;
           
                     
                     return Kolizja;
                   }
                 }
                 return BrakKolizji;

}


//                  /*cout<<"Dolny lewy ARGUMENTU"<<Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy()<<endl;
//    cout<<"Gorny prawy ARGUMENTU"<<Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()<<endl;
//     cout<<"Dolny lewy THISA"<<this->get_Obrys().get_Wierz_DolnyLewy()<<endl;
//     cout<<"Gorny prawy THISA"<<this->get_Obrys().get_Wierz_GornyPrawy()<<endl;

//     double x_thisa = abs(this->get_Obrys().get_Wierz_GornyPrawy()[0]-this->get_Obrys().get_Wierz_DolnyLewy()[0]);
//     double y_thisa = abs(this->get_Obrys().get_Wierz_GornyPrawy()[1]-this->get_Obrys().get_Wierz_DolnyLewy()[1]);
//     double x_argumentu = abs(Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()[0]-Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy()[0]);
//     double y_argumentu = abs(Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()[1]-Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy()[1]);
  
// cout<<"xthisa"<<x_thisa<<endl;
// cout<<"ythisa"<<y_thisa<<endl;
// cout<<"xa"<<x_argumentu<<endl;
// cout<<"ya"<<y_argumentu<<endl;
// Vector2D srodek_thisa=(this->get_Obrys().get_Wierz_GornyPrawy()+this->get_Obrys().get_Wierz_DolnyLewy())*0.5;
// Vector2D srodek_argumentu=(Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()+Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy())*0.5;
// double pol_d_thisa=0.5*sqrt( x_thisa* y_thisa);
//  double pol_d_argumentu=0.5*sqrt(x_argumentu*  y_argumentu);
// /*cout<<(Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()-this->get_Obrys().get_Wierz_DolnyLewy())*((Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()-this->get_Obrys().get_Wierz_DolnyLewy())<<end;
//                cout<<"ODLEGLOSC"<<(Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()[0] -this->get_Obrys().get_Wierz_DolnyLewy()[1])<<endl;
//                 cout<<"Warunek jebniecia"<<x/2+this->get_Skala()[0]/2<<endl;
//                 if((Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()-this->get_Obrys().get_Wierz_DolnyLewy())*((Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()-this->get_Obrys().get_Wierz_DolnyLewy())<100){
                
//                       cout<<"wffffffffffffffffffffffffffffffffffffffffff"<<endl;
//                 }
//                 */
// //double x = abs(Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy()[0]-Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()[0]);
// //double y = abs(Wsk_lazik->get_Obrys().get_Wierz_DolnyLewy()[1]-Wsk_lazik->get_Obrys().get_Wierz_GornyPrawy()[1]);

// //Vector2D roznica =srodek_thisa-srodek_argumentu;

//              //  if(abs(roznica[0])+abs(roznica[1])<=pol_d_thisa+pol_d_argumentu)
        
 
  
      







     
