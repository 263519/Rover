#include "RoverSFR.hh"
#include <iostream>

using namespace std;

RoverSFR::RoverSFR(const char *sModelSolidFilename,
                   const char *sObjectName, int ColorID, Vector3D Scale,
                   Vector3D Position, double degrees, double speed,
                   double distance)
    : Rover(sModelSolidFilename, sObjectName, ColorID, Scale,
            Position, degrees, speed, distance) {}

CollisionType RoverSFR::CheckCollision(shared_ptr<Rover> &Akt) {
  if (Akt->get_Outline().get_BottomLeftCorner()[0] <= this->get_Outline().get_BottomLeftCorner()[0] &&
      ((Akt->get_Outline().get_BottomLeftCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1] &&
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_TopRightCorner()[1]) ||
       (Akt->get_Outline().get_TopRightCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] &&
        Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1]) ||
       (Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_TopRightCorner()[1] &&
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_BottomLeftCorner()[1]))) {

    if (Akt->get_Outline().get_TopRightCorner()[0] >= this->get_Outline().get_BottomLeftCorner()[0]) {
      cout << "Collision!" << endl;
      return Collision;
    }

  } else if (Akt->get_Outline().get_BottomLeftCorner()[0] >= this->get_Outline().get_BottomLeftCorner()[0] &&
             ((Akt->get_Outline().get_BottomLeftCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1] &&
               Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_TopRightCorner()[1]) ||
              (Akt->get_Outline().get_TopRightCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] &&
               Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1]) ||
              (Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_BottomLeftCorner()[1] &&
               Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_TopRightCorner()[1]))) {

    if (Akt->get_Outline().get_BottomLeftCorner()[0] <= this->get_Outline().get_TopRightCorner()[0]) {
      cout << "Collision!" << endl;
      return Collision;
    }
  }
  return NoCollision;
}

void RoverSFR::AddSample(shared_ptr<GeomObject> &samplePtr) {
  CollectedSamples.push_back(samplePtr);
}

void RoverSFR::DisplayList() {
  for (shared_ptr<GeomObject> &Ob : CollectedSamples) {
    cout << Ob->get_ObjectName() << endl;
  }
}