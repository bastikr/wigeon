#pragma once

#include "geomalia/point2d.h"
#include "geomalia/polygon2d.h"


namespace geomalia {

int winding_number(const Point2D& point, const Polygon2D& polygon);

} // namespace geomalia