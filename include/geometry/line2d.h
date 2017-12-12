#pragma once

#include <array>

#include "geometry/point2d.h"
#include "geometry/vector2d.h"


namespace geometry {

struct Line2D {
  Line2D(Point2D point, Vector2D direction) : point(point), direction(direction) {}
  Line2D(Point2D point0, Point2D point1) : point(point0), direction(point1-point0) {}

  Point2D getPoint() const {return point;}
  Vector2D getDirection() const {return direction;}

  Line2D operator+(const Vector2D&) const;
  Line2D operator-(const Vector2D&) const;

  Point2D point;
  Vector2D direction;
};

} // namespace geometry