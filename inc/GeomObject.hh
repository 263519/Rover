#ifndef GEOMOBJECT_HH
#define GEOMOBJECT_HH

#include <string>
#include <memory>
#include "SVector.hh"
#include "SMatrix.hh"
#include "OutlineXY.hh"
#include "CollisionType.hh"

#define DRAWN_SOLIDS_DIRECTORY    "../drawn_solids"

class Rover;
class GeomObject {
    std::string   _modelSolidFilename;
    std::string   _drawnSolidFilename;
    std::string   _objectName;
    int           _colorID;
    Vector3D      _scale;
    Vector3D      _position;
    double        _orientationAngle;   // RADIANS
    OutlineXY     _outline;
    
  public:
    OutlineXY &set_Outline() { return _outline; }
    OutlineXY get_Outline() { return _outline; }
    double get_OrientationAngle() { return _orientationAngle; }
    double &set_OrientationAngle() { return _orientationAngle; }
    Vector3D &set_Position() { return _position; }
    Vector3D get_Position() { return _position; }
    
    Vector3D &set_Scale() { return _scale; }
    Vector3D get_Scale() { return _scale; }
    
    std::string  get_ObjectName() { return _objectName; }
    std::string  get_DrawnSolidFilename() { return _drawnSolidFilename; }
    std::string  get_ModelSolidFilename() { return _modelSolidFilename; }
    std::string  &set_ObjectName() { return _objectName; }
    std::string  &set_DrawnSolidFilename() { return _drawnSolidFilename; }
    std::string  &set_ModelSolidFilename() { return _modelSolidFilename; }
  
    void SaveVertices();
    bool Input();

    GeomObject(const char* sModelSolidFilename, const char* sObjectName, int ColorID, Vector3D Scale, Vector3D Position, double degrees);
    virtual ~GeomObject() {
        std::cout << "GeomObject Destructor is running\n";
    }

    int GetColorID() const { return _colorID; }
  
    const std::string & GetObjectName() const { return _objectName; }
  
    const std::string & GetDrawnSolidFilename() const { return _drawnSolidFilename; }

    bool RecalculateAndSaveVertices();

    Vector3D rotateZ(Vector3D v, double theta);

    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr) = 0;
};

#endif
