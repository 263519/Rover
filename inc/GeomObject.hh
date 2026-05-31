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
    const OutlineXY &get_Outline() const { return _outline; }
    void set_Outline(const OutlineXY &outline) { _outline = outline; }

    double get_OrientationAngle() const { return _orientationAngle; }
    void set_OrientationAngle(double angle) { _orientationAngle = angle; }

    const Vector3D &get_Position() const { return _position; }
    void set_Position(const Vector3D &pos) { _position = pos; }

    const Vector3D &get_Scale() const { return _scale; }
    void set_Scale(const Vector3D &scale) { _scale = scale; }

    const std::string &get_ObjectName() const { return _objectName; }
    const std::string &get_DrawnSolidFilename() const { return _drawnSolidFilename; }
    const std::string &get_ModelSolidFilename() const { return _modelSolidFilename; }

    void set_ObjectName(const std::string &name) { _objectName = name; }
    void set_DrawnSolidFilename(const std::string &filename) { _drawnSolidFilename = filename; }
    void set_ModelSolidFilename(const std::string &filename) { _modelSolidFilename = filename; }
  
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

    bool CheckOutlineCollision(const GeomObject &other) const;

    virtual CollisionType CheckCollision(std::shared_ptr<Rover> &roverPtr) = 0;
};

#endif
