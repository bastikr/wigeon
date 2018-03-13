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

Line2D offset(const Line2D&, double);
Ray2D offset(const Ray2D&, double);
LineSegment2D offset(const LineSegment2D&, double);
Circle2D offset(const Circle2D&, double);
Rectangle2D offset(const Rectangle2D&, double);
Polygon2D offset(const Polygon2D&, double);
ClosedCurve2D offset(const ClosedCurve2D&, double);
Area2D offset(const Area2D&, double);

} // namespace wigeon
