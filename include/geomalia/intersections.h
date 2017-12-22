#pragma once

#include <vector>

#include "geomalia/point2d.h"
#include "geomalia/line2d.h"
#include "geomalia/ray2d.h"
#include "geomalia/linesegment2d.h"
#include "geomalia/rectangle2d.h"
#include "geomalia/circle2d.h"
#include "geomalia/polygon2d.h"

/*
Point
LineSegment
Line
Ray
Rectangle
Circle
Polygon
*/


namespace geomalia {

using Points2D = std::vector<Point2D>;

Points2D intersections(const Line2D& line0, const Line2D& line1);

} // namespace geomalia
