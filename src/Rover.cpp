#include <iostream>
#include <fstream>
#include "Rover.hh"
#include <unistd.h>
#include <cmath>

using namespace std;

Rover::Rover(const char* sModelSolidFilename,
             const char* sObjectName,
             int ColorID,
             Vector3D _Scale, Vector3D _Position, double _OrientationAngle, double speed, double distance
             ) : GeomObject(sModelSolidFilename, sObjectName, ColorID, _Scale, _Position, _OrientationAngle)
{
  this->DistanceToDrive = distance;
  this->Speed = speed;
}

CollisionType Rover::CheckCollision(shared_ptr<Rover> &Akt) {
  if (this->CheckOutlineCollision(*Akt)) {
    cout << "Collision!" << endl;
    return CollisionType::Collision;
  }
  return CollisionType::NoCollision;
}

/*
 * Analyzes whether the rover can drive over a specific regolith sample or if it
 * results in a solid collision, based on the chassis clearance and the distance to the sample.
 */
CollisionType Rover::AnalyzeSampleCollision(const GeomObject &sample) {
  CollisionType typ = CollisionType::DriveOverSample;

  double tmp[3] = {this->get_DistanceToDrive(), 0, 0};
  Vector3D jedz(tmp);

  jedz = this->rotateZ(jedz, this->get_OrientationAngle());

  Vector3D r = this->get_Position() - sample.get_Position();

  double iloczyn_dlugosci_wektorow =
      (sqrt(jedz[0] * jedz[0] + jedz[1] * jedz[1] + jedz[2] * jedz[2])) *
      (sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]));

  double sin_a =
      (jedz[0] * r[1] - jedz[1] * r[0]) / iloczyn_dlugosci_wektorow;


  double dlugosc_r = sqrt(r[0] * r[0] + r[1] * r[1]);

  double distance = abs(sin_a * dlugosc_r);

  if (distance > (this->get_Scale()[1] / 5)) {
    typ = CollisionType::CollisionWithSample;
  }

  if (typ == CollisionType::DriveOverSample) {
    cout << "Collision with sample, but you can drive over it. Distance: " << distance << endl;
  }

  if (typ == CollisionType::CollisionWithSample) {
    cout << "Collision with sample! Distance: " << distance << endl;
  }

  return typ;
}
