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
  CollisionType collisionType = CollisionType::DriveOverSample;

  Vector3D driveVector{this->get_DistanceToDrive(), 0, 0};

  driveVector = this->rotateZ(driveVector, this->get_OrientationAngle());

  Vector3D r = this->get_Position() - sample.get_Position();

  double vectorLengthsProduct =
      (sqrt(driveVector[0] * driveVector[0] + driveVector[1] * driveVector[1] + driveVector[2] * driveVector[2])) *
      (sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]));

  double sin_a =
      (driveVector[0] * r[1] - driveVector[1] * r[0]) / vectorLengthsProduct;


  double lengthR = sqrt(r[0] * r[0] + r[1] * r[1]);

  double distance = abs(sin_a * lengthR);

  if (distance > (this->get_Scale()[1] / 5)) {
    collisionType = CollisionType::CollisionWithSample;
  }

  if (collisionType == CollisionType::DriveOverSample) {
    cout << "Collision with sample, but you can drive over it. Distance: " << distance << endl;
  }

  if (collisionType == CollisionType::CollisionWithSample) {
    cout << "Collision with sample! Distance: " << distance << endl;
  }

  return collisionType;
}
