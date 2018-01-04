#pragma once

#include <vector>

#include "wigeon/point2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"

/*
Point
LineSegment
Line
Ray
Rectangle
Circle
Polygon
*/


namespace wigeon {

using Points2D = std::vector<Point2D>;

Points2D intersections(const Line2D& line0, const Line2D& line1);
Points2D intersections(const Line2D&, const Ray2D&);
Points2D intersections(const Ray2D&, const Line2D&);
Points2D intersections(const LineSegment2D&, const LineSegment2D&);
Points2D intersections(const LineSegment2D&, const Polygon2D&);
Points2D intersections(const Polygon2D&, const LineSegment2D&);
Points2D intersections(const Polygon2D&, const Polygon2D&);

} // namespace wigeon
