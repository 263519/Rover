#include <fstream>
#include <iostream>
#include "MarsSurface.hh"

using namespace std;

#define PLANET_SURFACE_FILENAME "../drawn_solids/planet_surface.dat"

bool CreateSurface_SaveToFile(ofstream &rStrmWy) {
  for (double WspY = -SURFACE_SIZE_Y / 2;
       WspY <= SURFACE_SIZE_Y / 2;
       WspY += GRID_MESH_SIZE) {

    for (double WspX = -SURFACE_SIZE_X / 2;
         WspX <= SURFACE_SIZE_X / 2;
         WspX += GRID_MESH_SIZE) {
      rStrmWy << WspX << "  " << WspY << " 0" << endl;
    }
    rStrmWy << endl;
  }
  return !rStrmWy.fail();
}

bool CreateSurface_SaveToFile(const char *sFilename) {
  ofstream StrmWy(sFilename);
  if (!StrmWy.is_open()) {
    cerr << endl
         << ":( Failed to open file for writing: \""
         << sFilename << "\"" << endl
         << endl;
    return false;
  }
  return CreateSurface_SaveToFile(StrmWy);
}

bool InitMarsSurface(PzG::GnuplotLink &rLink) {
  if (!CreateSurface_SaveToFile(PLANET_SURFACE_FILENAME))
    return false;

  PzG::InfoPlikuDoRysowania *wInfoPliku;

  wInfoPliku = &rLink.DodajNazwePliku(PLANET_SURFACE_FILENAME);
  wInfoPliku->ZmienKolor(4);
  return true;
}
