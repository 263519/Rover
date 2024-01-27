#pragma once
#include <iostream>

#include "SVector.hh"

class ObrysXY {
Vector2D Wierz_DolnyLewy;
Vector2D Wierz_GornyPrawy;
public:
 Vector2D &set_Wierz_DolnyLewy() {return Wierz_DolnyLewy;}
   Vector2D get_Wierz_DolnyLewy() {return Wierz_DolnyLewy;}
    Vector2D &set_Wierz_GornyPrawy() {return Wierz_GornyPrawy;}
   Vector2D get_Wierz_GornyPrawy() {return Wierz_GornyPrawy;}






};

