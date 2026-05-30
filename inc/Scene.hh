#pragma once
#include <iostream>
#include "Rover.hh"
#include "gnuplot_link.hh"
#include <unistd.h>
#include <cmath>
#include <list>
#include <memory>
#include "Colors.hh"
#include "MarsSurface.hh"
#include "RegolithSample.hh"
#include <cstring>
#include "RoverSFR.hh"
#include <csignal>
#include <climits>
#include "AdjacencyListGraph.hh"
#include "AdjacencyMatrixGraph.hh"

constexpr int THREADS_COUNT = 1;

class Scene {
    PzG::GnuplotLink Link;
    std::shared_ptr<Rover> SelectedRover;
    std::list<std::shared_ptr<GeomObject>> GeomObjects;

public:
    std::shared_ptr<Rover> get_SelectedRover() { return SelectedRover; }
    std::shared_ptr<Rover> &set_SelectedRover() { return SelectedRover; }

    Scene();
    void AddToDrawingList(PzG::GnuplotLink &rLink, const GeomObject &rOb);
    void RemoveFromDrawingList(PzG::GnuplotLink &rLink, const GeomObject &rOb);
    void InitGnuplotLink(PzG::GnuplotLink &rLink);
    std::shared_ptr<Rover> SelectRover(unsigned int choice);
    void DriveDistance(double distance);
    void Rotate(double theta);
    void DisplaySampleList();
    void Menu();
    std::list<std::shared_ptr<GeomObject>>::iterator PickUpSample();
    void PlaceSamples();

    void AutonomousDrive();
    ~Scene() {
        std::cout << "Scene Destructor is running\n";
    }
};
