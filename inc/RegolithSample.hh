#pragma once
#include "Rover.hh"

class Rover;
class RegolithSample : public GeomObject {
public:
    RegolithSample(const char* sModelSolidFilename, const char* sObjectName, int ColorID, Vector3D Scale, Vector3D Position, double degrees);
    virtual ~RegolithSample() {
        std::cout << "RegolithSample Destructor is running\n";
    }
    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr) override;
};
