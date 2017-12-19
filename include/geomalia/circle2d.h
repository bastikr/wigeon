#pragma once

#include "geomalia/point2d.h"


namespace geomalia {

struct Circle2D {
  Circle2D(Point2D center, double radius) : center(center), radius(radius) {}

  Point2D center;
  double radius;
};

} // namespace geomalia
