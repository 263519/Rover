#pragma once
#include <iostream>

#include "SVector.hh"

class OutlineXY {
    Vector2D BottomLeftCorner;
    Vector2D TopRightCorner;
public:
    Vector2D &set_BottomLeftCorner() { return BottomLeftCorner; }
    Vector2D get_BottomLeftCorner() { return BottomLeftCorner; }
    Vector2D &set_TopRightCorner() { return TopRightCorner; }
    Vector2D get_TopRightCorner() { return TopRightCorner; }
};
