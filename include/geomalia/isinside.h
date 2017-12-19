#pragma once

#include "geomalia/point2d.h"
#include "geomalia/rectangle2d.h"
#include "geomalia/circle2d.h"
#include "geomalia/polygon2d.h"


namespace geomalia {

bool isinside(const Point2D& point, const Rectangle2D& rectangle);
bool isinside(const Point2D& point, const Circle2D& circle);
bool isinside(const Point2D& point, const Polygon2D& polygon);

} // namespace geomalia