#pragma once

#include "wigeon/point2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/collections.h"
#include "wigeon/area2d.h"


namespace wigeon {

bool within(const Point2D& point, const Triangle2D& triangle);
bool within(const Point2D& point, const Rectangle2D& rectangle);
bool within(const Point2D& point, const Circle2D& circle);
bool within(const Point2D& point, const Polygon2D& polygon);
bool within(const Point2D&, const ClosedCurve2D&);
bool within(const Point2D&, const ClosedCurves2D&);
bool within(const Point2D&, const Area2D&);

} // namespace wigeon
