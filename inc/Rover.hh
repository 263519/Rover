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
    double get_DistanceToDrive() const { return DistanceToDrive; }
    void set_DistanceToDrive(double distance) { DistanceToDrive = distance; }
    double get_Speed() const { return Speed; }
    void set_Speed(double speed) { Speed = speed; }

    virtual bool CanPickSamples() const { return false; }
    virtual void AddSample(std::shared_ptr<GeomObject>&) {}

    Rover();
    Rover(const char* sModelSolidFilename, const char* sObjectName, int ColorID, Vector3D Scale, Vector3D Position, double degrees, double speed, double distance);

    virtual ~Rover() {
        std::cout << "Virtual Rover Destructor is running\n";
    }

    CollisionType AnalyzeSampleCollision(const GeomObject &sample);

    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr) override;
};