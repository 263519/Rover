#include "RegolithSample.hh"
using namespace std;

CollisionType RegolithSample::CheckCollision(shared_ptr<Rover> &Akt) {
  // Delegate basic bounding box check to base GeomObject (DRY)
  if (!this->CheckOutlineCollision(*Akt)) {
    return CollisionType::NoCollision;
  }

  // Delegate the details of chassis clearance and distance calculation to Rover (SRP)
  return Akt->AnalyzeSampleCollision(*this);
}

RegolithSample::RegolithSample(const char *sModelSolidFilename,
                               const char *sObjectName, int ColorID,
                               Vector3D Scale, Vector3D Position,
                               double degrees)
    : GeomObject(sModelSolidFilename, sObjectName, ColorID, Scale,
                 Position, degrees) {}
