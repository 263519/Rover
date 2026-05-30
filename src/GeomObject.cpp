#include "GeomObject.hh"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

GeomObject::GeomObject(const char *sModelSolidFilename,
                       const char *sObjectName, int ColorID, Vector3D Scale,
                       Vector3D Position, double degrees)
    : _modelSolidFilename(sModelSolidFilename), _colorID(ColorID),
      _scale(Scale), _position(Position), _orientationAngle(degrees) {

  _objectName = sObjectName;
  _drawnSolidFilename = DRAWN_SOLIDS_DIRECTORY;
  _drawnSolidFilename += "/";
  _drawnSolidFilename += sObjectName;
  _drawnSolidFilename += ".dat";
  this->_scale = Scale;
  this->_position = Position;

  this->_orientationAngle = (degrees * M_PI) / 180;
}

Vector3D GeomObject::rotateZ(Vector3D v, double theta) {
  Vector3D rotated;
  double tmp[3][3] = {
      {cos(theta), -sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};
  Matrix3D RotationMat = Matrix3D(tmp);

  rotated = RotationMat * v;
  return rotated;
}

bool GeomObject::RecalculateAndSaveVertices() {
  ifstream StrmWe(_modelSolidFilename);
  ofstream StrmWy(_drawnSolidFilename);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl
         << "Could not open one of the files:" << endl
         << "    " << _modelSolidFilename << endl
         << "    " << _drawnSolidFilename << endl
         << endl;

    return false;
  }

  Vector3D Wsp = Vector3D();
  int RowIndex = 0;

  StrmWe >> Wsp;

  if (StrmWe.fail())
    return false;

  do {
    Wsp = Wsp * _scale;
    Wsp = rotateZ(Wsp, _orientationAngle);
    Wsp = Wsp + _position;

    StrmWy << Wsp[0] << " " << Wsp[1] << " " << Wsp[2] << endl;

    ++RowIndex;

    if (RowIndex >= 4) {
      StrmWy << endl;
      RowIndex = 0;
    }

    StrmWe >> Wsp;

  } while (!StrmWe.fail());

  SaveVertices();
  if (!StrmWe.eof())
    return false;

  return RowIndex == 0 && !StrmWy.fail();
}

void GeomObject::SaveVertices() {
  ifstream InputFile(_drawnSolidFilename);
  double tab[24];
  for (int i = 0; i < 20; ++i) {
    InputFile >> tab[i];
  }
  int i = 0;
  double tmp;
  int multiplicity = 0; // Multiplicity of angle (2kpi)
  multiplicity = _orientationAngle / (2 * M_PI);

  if (((_orientationAngle - multiplicity * 2 * M_PI >= M_PI / 2 &&
        _orientationAngle - multiplicity * 2 * M_PI <= M_PI) ||
       (_orientationAngle - multiplicity * 2 * M_PI >= 3 * M_PI / 2 &&
        _orientationAngle - multiplicity * 2 * M_PI <= 2 * M_PI) ||
       (_orientationAngle - multiplicity * 2 * M_PI >= -M_PI / 2 &&
        _orientationAngle - multiplicity * 2 * M_PI <= 0) ||
       (_orientationAngle - multiplicity * 2 * M_PI >= -3 * M_PI / 2 &&
        _orientationAngle - multiplicity * 2 * M_PI <= -M_PI)) &&
      _orientationAngle != 0) {
    i = 1;

    this->_outline.set_BottomLeftCorner()[1] = tab[6 + i];
    this->_outline.set_TopRightCorner()[0] = tab[4 - i];
    this->_outline.set_TopRightCorner()[1] = tab[15 + i];
    this->_outline.set_BottomLeftCorner()[0] = tab[19 - i];

  } else {
    this->_outline.set_BottomLeftCorner()[0] = tab[6 + i];
    this->_outline.set_BottomLeftCorner()[1] = tab[4 - i];
    this->_outline.set_TopRightCorner()[0] = tab[15 + i];
    this->_outline.set_TopRightCorner()[1] = tab[19 - i];
  }

  if (this->_outline.set_BottomLeftCorner()[0] > this->_outline.set_TopRightCorner()[0]) {
    tmp = this->_outline.set_BottomLeftCorner()[0];
    this->_outline.set_BottomLeftCorner()[0] = this->_outline.set_TopRightCorner()[0];
    this->_outline.set_TopRightCorner()[0] = tmp;
  }
  if (this->_outline.set_BottomLeftCorner()[1] > this->_outline.set_TopRightCorner()[1]) {
    tmp = this->_outline.set_BottomLeftCorner()[1];
    this->_outline.set_BottomLeftCorner()[1] = this->_outline.set_TopRightCorner()[1];
    this->_outline.set_TopRightCorner()[1] = tmp;
  }
}
