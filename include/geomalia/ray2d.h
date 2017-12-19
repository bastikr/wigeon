#pragma once

#include "geomalia/point2d.h"
#include "geomalia/vector2d.h"


namespace geomalia {

struct Ray2D {
  Ray2D(Point2D point, Vector2D direction): point(point), direction(direction) {}
  Ray2D(Point2D point0, Point2D point1) : point(point0), direction(point1-point0) {}

  Point2D getPoint() const {return point;}
  Vector2D getDirection() const {return direction;}

  Ray2D operator+(const Vector2D&) const;
  Ray2D operator-(const Vector2D&) const;

  Point2D point;
  Vector2D direction;
};

} // namespace geomalia
