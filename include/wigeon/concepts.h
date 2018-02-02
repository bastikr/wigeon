#pragma once


#include <boost/variant.hpp>

#include "wigeon/point1d.h"
#include "wigeon/vector1d.h"

#include "wigeon/point2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/polyline2d.h"

#include "wigeon/point3d.h"
#include "wigeon/vector3d.h"


namespace wigeon {

using Curve2D = boost::variant<Line2D, Ray2D, LineSegment2D, PolyLine2D>;
using ClosedCurve2D = boost::variant<Triangle2D, Rectangle2D, Circle2D, Polygon2D>;
using PlotObject2D = boost::variant<LineSegment2D, Triangle2D, Rectangle2D, Circle2D, Polygon2D, PolyLine2D>;

Curve2D rotate(const Rotation2D&, const Curve2D&);
ClosedCurve2D rotate(const Rotation2D&, const ClosedCurve2D&);
// PlotObject2D rotate(const Rotation2D&, const PlotObject2D&);


Curve2D operator+(const Curve2D&, const Vector2D&);
Curve2D operator+(const Vector2D&, const Curve2D&);

ClosedCurve2D operator+(const ClosedCurve2D&, const Vector2D&);
ClosedCurve2D operator+(const Vector2D&, const ClosedCurve2D&);

PlotObject2D operator+(const PlotObject2D&, const Vector2D&);
PlotObject2D operator+(const Vector2D&, const PlotObject2D&);


Curve2D operator-(const Curve2D&, const Vector2D&);
Curve2D operator-(const Vector2D&, const Curve2D&);

ClosedCurve2D operator-(const ClosedCurve2D&, const Vector2D&);
ClosedCurve2D operator-(const Vector2D&, const ClosedCurve2D&);

PlotObject2D operator-(const PlotObject2D&, const Vector2D&);
PlotObject2D operator-(const Vector2D&, const PlotObject2D&);

} // namespace wigeon
