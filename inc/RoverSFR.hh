#pragma once
#include "Rover.hh"
#include "RegolithSample.hh"
#include <list>

class RoverSFR : public Rover {
    std::list<std::shared_ptr<GeomObject>> CollectedSamples;

public:
    RoverSFR(const char* sModelSolidFilename, const char* sObjectName, int ColorID, Vector3D Scale, Vector3D Position, double degrees, double speed, double distance);

    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr) override;
    virtual void AddSample(std::shared_ptr<GeomObject> &samplePtr) override;
    void DisplayList();

    virtual bool CanPickSamples() const override { return true; }

    ~RoverSFR() {
        std::cout << "RoverSFR destructor is running\n\n\n";
        std::cout << "Collected samples on rover:\n";
        for (auto &x : CollectedSamples) {
            std::cout << x->get_ObjectName() << "\n";
        }
        std::cout << "\n";
    }
};