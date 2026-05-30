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
  if (Akt->get_Outline().get_BottomLeftCorner()[0] <= this->get_Outline().get_BottomLeftCorner()[0] &&
      ((Akt->get_Outline().get_BottomLeftCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1] && 
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] ) || 
       (Akt->get_Outline().get_TopRightCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] && 
        Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1]) || 
       (Akt->get_Outline().get_TopRightCorner()[1] >= this->get_Outline().get_TopRightCorner()[1] &&
        Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_BottomLeftCorner()[1]))) {
                        
    if (Akt->get_Outline().get_TopRightCorner()[0] >= this->get_Outline().get_BottomLeftCorner()[0]) {
      cout << "Collision!" << endl;
      return Collision;
    }
  }
  else if (Akt->get_Outline().get_BottomLeftCorner()[0] >= this->get_Outline().get_BottomLeftCorner()[0] &&
           ((Akt->get_Outline().get_BottomLeftCorner()[1] >= this->get_Outline().get_BottomLeftCorner()[1] && 
             Akt->get_Outline().get_BottomLeftCorner()[1] <= this->get_Outline().get_TopRightCorner()[1] ) ||
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
