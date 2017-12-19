#pragma once

#include "geometry/point2d.h"
#include "geometry/rectangle2d.h"
#include "geometry/circle2d.h"
#include "geometry/polygon2d.h"


namespace geometry {

bool isinside(const Point2D& point, const Rectangle2D& rectangle);
bool isinside(const Point2D& point, const Circle2D& circle);
bool isinside(const Point2D& point, const Polygon2D& polygon);

} // namespace geometry