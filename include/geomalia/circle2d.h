#pragma once

#include "geomalia/vector2d.h"
#include "geomalia/point2d.h"


namespace geomalia {

struct Circle2D {
  Circle2D(Point2D center, double radius) : center_(center), radius_(radius) {}

  Point2D center() const {return center_;}
  double radius() const {return radius_;}

  Circle2D operator+(const Vector2D& vector) const;
  Circle2D operator-(const Vector2D& vector) const;


  Point2D center_;
  double radius_;
};

} // namespace geomalia
