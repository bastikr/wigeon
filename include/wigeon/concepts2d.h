#pragma once

#include <boost/variant.hpp>

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


namespace wigeon {

using Curve2D = boost::variant<Line2D, Ray2D, LineSegment2D, PolyLine2D, Triangle2D, Rectangle2D, Circle2D, Polygon2D>;
using FiniteCurve2D = boost::variant<LineSegment2D, PolyLine2D, Triangle2D, Rectangle2D, Circle2D, Polygon2D>;
using InfiniteCurve2D = boost::variant<Line2D, Ray2D>;
using OpenCurve2D = boost::variant<Line2D, Ray2D, LineSegment2D, PolyLine2D>;
using ClosedCurve2D = boost::variant<Triangle2D, Rectangle2D, Circle2D, Polygon2D>;
using PlotObject2D = boost::variant<LineSegment2D, Triangle2D, Rectangle2D, Circle2D, Polygon2D, PolyLine2D>;

Curve2D rotate(const Rotation2D&, const Curve2D&);
FiniteCurve2D rotate(const Rotation2D&, const FiniteCurve2D&);
InfiniteCurve2D rotate(const Rotation2D&, const InfiniteCurve2D&);
OpenCurve2D rotate(const Rotation2D&, const OpenCurve2D&);
ClosedCurve2D rotate(const Rotation2D&, const ClosedCurve2D&);
PlotObject2D rotate(const Rotation2D&, const PlotObject2D&);


Curve2D operator+(const Curve2D&, const Vector2D&);
Curve2D operator+(const Vector2D&, const Curve2D&);

FiniteCurve2D operator+(const FiniteCurve2D&, const Vector2D&);
FiniteCurve2D operator+(const Vector2D&, const FiniteCurve2D&);

InfiniteCurve2D operator+(const InfiniteCurve2D&, const Vector2D&);
InfiniteCurve2D operator+(const Vector2D&, const InfiniteCurve2D&);

OpenCurve2D operator+(const OpenCurve2D&, const Vector2D&);
OpenCurve2D operator+(const Vector2D&, const OpenCurve2D&);

ClosedCurve2D operator+(const ClosedCurve2D&, const Vector2D&);
ClosedCurve2D operator+(const Vector2D&, const ClosedCurve2D&);

PlotObject2D operator+(const PlotObject2D&, const Vector2D&);
PlotObject2D operator+(const Vector2D&, const PlotObject2D&);


Curve2D operator-(const Curve2D&, const Vector2D&);

FiniteCurve2D operator-(const FiniteCurve2D&, const Vector2D&);

InfiniteCurve2D operator-(const InfiniteCurve2D&, const Vector2D&);

OpenCurve2D operator-(const OpenCurve2D&, const Vector2D&);

ClosedCurve2D operator-(const ClosedCurve2D&, const Vector2D&);

PlotObject2D operator-(const PlotObject2D&, const Vector2D&);

} // namespace wigeon
