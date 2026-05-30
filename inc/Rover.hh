#pragma once

#include <string>
#include "GeomObject.hh"
#include "gnuplot_link.hh"
#include <unistd.h>

typedef SMatrix<double, 3> Matrix3D; 

class Rover : public GeomObject {
    double Speed;
    double DistanceToDrive;

public:
    double get_DistanceToDrive() { return DistanceToDrive; }
    double &set_DistanceToDrive() { return DistanceToDrive; }
    double get_Speed() { return Speed; }
    double &set_Speed() { return Speed; }

    Rover();
    Rover(const char* sModelSolidFilename, const char* sObjectName, int ColorID, Vector3D Scale, Vector3D Position, double degrees, double speed, double distance);

    virtual ~Rover() {
        std::cout << "Virtual Rover Destructor is running\n";
    }

    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr);
};