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

// Point - ...
double distance2(const Point2D& point0, const Point2D& point1);

double distance2(const Point2D& point0, const LineSegment2D& segment0);
double distance2(const LineSegment2D& segment0, const Point2D& point0);

double distance2(const Point2D& point, const Line2D& line);
double distance2(const Line2D& line, const Point2D& point);

double distance2(const Point2D& point, const Ray2D& ray);
double distance2(const Ray2D& ray, const Point2D& point);

double distance2(const Point2D& point, const Rectangle2D& circle);
double distance2(const Rectangle2D& circle, const Point2D& point);

double distance2(const Point2D& point, const Circle2D& circle);
double distance2(const Circle2D& circle, const Point2D& point);

double distance2(const Point2D& point0, const Polygon2D& polygon0);
double distance2(const Polygon2D& polygon0, const Point2D& point0);


// LineSegment - ...
double distance2(const LineSegment2D& segment0, const LineSegment2D& segment1);

double distance2(const LineSegment2D& segment, const Line2D& line);
double distance2(const Line2D& line, const LineSegment2D& segment);

double distance2(const LineSegment2D& segment, const Ray2D& ray);
double distance2(const Ray2D& ray, const LineSegment2D& segment);

double distance2(const LineSegment2D& segment, const Polygon2D& polygon);
double distance2(const Polygon2D& polygon, const LineSegment2D& segment);


// Polygon - ...
double distance2(const Polygon2D& polygon0, const Polygon2D& polygon1);

} // namespace wigeon
