#pragma once

#include "geometry/point2d.h"


namespace geometry {

struct Circle2D {
  Circle2D(Point2D center, double radius) : center(center), radius(radius) {}

  Point2D center;
  double radius;
};

} // namespace geometry
