#pragma once

#include "wigeon/point2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/area2d.h"


namespace wigeon {

Line2D offset(const Line2D& line, double d);
Ray2D offset(const Ray2D& ray, double d);
LineSegment2D offset(const LineSegment2D& segment, double d);
Circle2D offset(const Circle2D& circle, double d);
Rectangle2D offset(const Rectangle2D& rectangle, double d);
Polygon2D offset(const Polygon2D& polygon, double d);
ClosedCurve2D offset(const ClosedCurve2D&, double d);
Area2D offset(const Area2D&, double d);

} // namespace wigeon
