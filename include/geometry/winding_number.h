#pragma once

#include "geometry/point2d.h"
#include "geometry/polygon2d.h"


namespace geometry {

int winding_number(const Point2D& point, const Polygon2D& polygon);

} // namespace geometry