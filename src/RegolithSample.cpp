#include "RegolithSample.hh"
using namespace std;

CollisionType RegolithSample::CheckCollision(shared_ptr<Rover> &Akt) {
  CollisionType typ = NoCollision;

  if (Akt->get_Outline().get_BottomLeftCorner()[0] <= this->get_Outline().get_BottomLeftCorner()[0] &&
      ((Akt->get_Outline().get_BottomLeftCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1] &&
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_TopRightCorner()[1]) ||
       (Akt->get_Outline().get_TopRightCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] &&
        Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1]) ||
       (Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_TopRightCorner()[1] &&
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_BottomLeftCorner()[1]))) {

    if (Akt->get_Outline().get_TopRightCorner()[0] >= this->get_Outline().get_BottomLeftCorner()[0]) {
      cout << "Collision!" << endl;
      typ = CollisionWithSample;
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
      typ = CollisionWithSample;
    }
  }

  if (typ == CollisionWithSample) {
    typ = DriveOverSample;

    double tmp[3] = {Akt->get_DistanceToDrive(), 0, 0};
    Vector3D jedz(tmp);

    jedz = Akt->rotateZ(jedz, Akt->get_OrientationAngle());

    Vector3D r = Akt->get_Position() - this->get_Position();

    double iloczyn_dlugosci_wektorow =
        (sqrt(jedz[0] * jedz[0] + jedz[1] * jedz[1] + jedz[2] * jedz[2])) *
        (sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]));

    double sin_a =
        (jedz[0] * r[1] - jedz[1] * r[0]) / iloczyn_dlugosci_wektorow;

    double dlugosc_r = sqrt(r[0] * r[0] + r[1] + r[1]);

    double distance = abs(sin_a * dlugosc_r);

    if (distance > (Akt->get_Scale()[1] / 5))
      typ = CollisionWithSample;

    if (typ == DriveOverSample)
      cout << "Collision with sample, but you can drive over it. Distance: " << distance << endl;

    if (typ == CollisionWithSample)
      cout << "Collision with sample! Distance: " << distance << endl;
  }

  return typ;
}

RegolithSample::RegolithSample(const char *sModelSolidFilename,
                               const char *sObjectName, int ColorID,
                               Vector3D Scale, Vector3D Position,
                               double degrees)
    : GeomObject(sModelSolidFilename, sObjectName, ColorID, Scale,
                 Position, degrees) {}
