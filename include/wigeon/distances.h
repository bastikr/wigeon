#pragma once

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

// Point
double distance2(const Point2D&, const Point2D&);


// LineSegment
double distance2(const LineSegment2D&, const Point2D&);
double distance2(const Point2D&, const LineSegment2D&);

double distance2(const LineSegment2D&, const LineSegment2D&);


// Line
double distance2(const Line2D&, const Point2D&);
double distance2(const Point2D&, const Line2D&);

double distance2(const LineSegment2D&, const Line2D&);
double distance2(const Line2D&, const LineSegment2D&);


// Ray
double distance2(const Ray2D&, const Point2D&);
double distance2(const Point2D&, const Ray2D&);

double distance2(const Ray2D&, const LineSegment2D&);
double distance2(const LineSegment2D&, const Ray2D&);


// Circle
double distance2(const Circle2D&, const Point2D&);
double distance2(const Point2D&, const Circle2D&);


// Rectangle
double distance2(const Rectangle2D&, const Point2D&);
double distance2(const Point2D&, const Rectangle2D&);


// Polygon
double distance2(const Polygon2D&, const Point2D&);
double distance2(const Point2D&, const Polygon2D&);

double distance2(const Polygon2D&, const LineSegment2D&);
double distance2(const LineSegment2D&, const Polygon2D&);

double distance2(const Polygon2D&, const Polygon2D&);

} // namespace wigeon
