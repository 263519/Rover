#pragma once
#include <iostream>
#define DIFF 1e-15





template <typename Type, int Size>
class SVector {
  private:
    Type  size[Size];
    static int ilosc;
  public:

  typedef SVector<double, 3> Vector3D; 

    SVector() { for (Type &Wsp: size) Wsp = 0; }
    SVector(Type [Size]);
    
  
    Type  operator [] (unsigned int Ind) const { return size[Ind]; }
    Type &operator [] (unsigned int Ind)       { return size[Ind]; }

    SVector<Type,Size> operator - (const SVector<Type,Size> &Odjemnik) const;
    SVector<Type,Size> operator * (double Mnoznik) const;
    SVector<Type,Size> operator + (const SVector<Type,Size> &v);
    SVector<Type,Size> operator / (const double &tmp);
    bool operator == (const  SVector<Type,Size> tmp)const ;
    SVector<Type,Size> operator * (SVector<Type,Size> Vector2) const; // iloczyn wektorowy 
    Type return_x(){return size[0];}
    Type return_y(){return size[1];}
  //   SVector(){

  //     ++ilosc;

  //   } 
  // ~SVector(){}
  // static int IloscWek() { return ilosc; }
 
};

typedef SVector<double, 3> Vector3D; 
typedef SVector<double, 2> Vector2D; 

// template<typename Type, int Size>
// int SVector<Type,  Size>::ilosc = 0;


/******************************************************************************
 |  Realizuje odejmowanie dwoch wektorow.                                     |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik odejmowania,                                 |
 |      Odjemnik - drugi skladnik odejmowania.                                       |
 |  Zwraca:                                                                   |
 |      Roznice dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator - (const SVector<Type,Size> &Odjemnik) const
{
  SVector<Type,Size>  Wynik;

  for (unsigned int Ind = 0; Ind < Size; ++Ind) Wynik[Ind] = (*this)[Ind] - Odjemnik[Ind];
  return Wynik;
}


/******************************************************************************
 |  Realizuje mnozenie wektora przez skalar.                                     |
 |  Argumenty:                                                                |
|     this - pierwszy skladnik mnozenia (wektor),                           |
 |      v - drugi skladnik mnozenia (liczba typu double).                     |
 |  Zwraca:                                                                   |
 |      Iloczyn dwoch skladnikow przekazanych jako wskaznik                   |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator * (double Mnoznik) const
{
  SVector<Type,Size>  Wynik;

  for (unsigned int Ind = 0; Ind < Size; ++Ind) Wynik[Ind] = (*this)[Ind]*Mnoznik;
  return Wynik;  
}


/******************************************************************************
 |  Konstruktor klasy SVector.                                                 |
 |  Argumenty:                                                                |
 |      tmp - Jednowymiarowa tablica typu double.                             |
 |  Zwraca:                                                                   |
 |      Tablice wypelniona wartosciami podanymi w argumencie.                 |
 */
template <typename Type, int Size>
SVector<Type, Size>::SVector(Type tmp[Size]) {
    for (int i = 0; i < Size; ++i) {
   
      size[i] = tmp[i];
   
  }
}



/******************************************************************************
 |  Przeciazenie operatora <<                                                 |
 |  Argumenty:                                                                |
 |      out - strumien wejsciowy,                                             |
 |      tmp - wektor.                                                         |
 */
template <typename Type, int Size>
std::ostream &operator<<(std::ostream &out,const SVector<Type,Size> &tmp) {
  for (int i = 0; i < Size; ++i) {
    out << "[ " << tmp[i] << " ]\n";
  }
  return out;
}


/******************************************************************************
 |  Przeciazenie operatora >>                                                 |
 |  Argumenty:                                                                |
 |      in - strumien wyjsciowy,                                              |
 |      tmp - wektor.                                                         |
 */
template <typename Type, int Size>
std::istream &operator>>(std::istream &in,SVector<Type,Size> &tmp) {
  for (int i = 0; i <Size; ++i) {
    in >> tmp[i];
  }
  std::cout << std::endl;
  return in;
}




/******************************************************************************
     przeciazenuie porowaniaa                                 |
 */
 
template <typename Type, int Size>
bool SVector<Type,Size>::operator == (const  SVector<Type,Size> tmp)const {
  for(int i=0;i<Size;++i){
  if(abs(size[i]-tmp[i]) >= DIFF)
    return 0;
  }
  
  return 1;
}


/******************************************************************************
 |  Realizuje dodawanie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - pierwszy skladnik dodawania,                                   |
 |      v - drugi skladnik dodawania.                                         |
 |  Zwraca:                                                                   |
 |      Sume dwoch skladnikow przekazanych jako wskaznik                      |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator + (const SVector<Type,Size> &v) {
  SVector<Type,Size> result;
  for (int i = 0; i < Size; ++i) {
    result[i] = size[i] + v[i];
  }
  return result;
}



/******************************************************************************
 |  Realizuje dzielenie dwoch wektorow.                                       |
 |  Argumenty:                                                                |
 |      this - licznik dzielenia,                                             |
 |      v - mianownik dzielenia.                                              |
 |  Zwraca:                                                                   |
 |      Iloraz dwoch skladnikow przekazanych jako wskaznik                    |
 |      na parametr.                                                          |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator/(const double &tmp) {
 SVector<Type,Size> result;

  for (int i = 0; i < Size; ++i) {
    result[i] = size[i] / tmp;
  }

  return result;
}


/******************************************************************************
 |  Realizuje obliczasnie ILOCZYNU WEKTOROWEGO.                                     |
 |  Argumenty:                                                                |
|     this - pierwszy skladnik mnozenia (wektor),                           |
 |     Vector2 - drugi skladnik mnozenia (wektor).                     |
 |  Zwraca:                                                                   |
 |      Iloczyn skalarny                                                      |
 */
template <typename Type, int Size>
SVector<Type,Size> SVector<Type,Size>::operator * (SVector<Type,Size> Vector2) const
{
  SVector<Type,Size>  Wynik;

  for (unsigned int Ind = 0; Ind < Size; ++Ind) Wynik[Ind] = (*this)[Ind]*Vector2[Ind];
  return Wynik;  
}






