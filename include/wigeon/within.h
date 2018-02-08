#pragma once

#include "wigeon/point2d.h"
#include "wigeon/boundingbox2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/collections.h"
#include "wigeon/area2d.h"


namespace wigeon {

bool within(const Point2D&, const Triangle2D&);
bool within(const Point2D&, const Rectangle2D&);
bool within(const Point2D&, const Circle2D&);
bool within(const Point2D&, const Polygon2D&);
bool within(const Point2D&, const ClosedCurve2D&);
bool within(const Point2D&, const ClosedCurves2D&);
bool within(const Point2D&, const Area2D&);

bool within(const Point2D&, const BoundingBox2D&);
bool within(const BoundingBox2D&, const BoundingBox2D&);

} // namespace wigeon
