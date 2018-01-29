#pragma once

#include <vector>
#include "wigeon/collections.h"

#include "wigeon/point2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/doublelinesegment2d.h"
#include "wigeon/rectangle2d.h"
#include "wigeon/circle2d.h"
#include "wigeon/polygon2d.h"

/*
Line
Ray
LineSegment
DoubleLineSegment
Rectangle
Circle
Polygon
*/


namespace wigeon {

using Points2D = std::vector<Point2D>;

bool curves_intersect(const Vector2D& v, const Vector2D& w0, const Vector2D& w1);

// Line2D
Points2D intersections(const Line2D& line0, const Line2D& line1);

// Ray2D
Points2D intersections(const Ray2D&, const Line2D&);
Points2D intersections(const Line2D&, const Ray2D&);

// LineSegment2D
Points2D intersections(const LineSegment2D&, const Ray2D&);
Points2D intersections(const Ray2D&, const LineSegment2D&);
Points2D intersections(const LineSegment2D&, const Line2D&);
Points2D intersections(const Line2D&, const LineSegment2D&);
Points2D intersections(const LineSegment2D&, const LineSegment2D&);

// DoubleLineSegment2D
Points2D intersections(const DoubleLineSegment2D&, const Line2D&);
Points2D intersections(const Line2D&, const DoubleLineSegment2D&);
Points2D intersections(const DoubleLineSegment2D&, const Ray2D&);
Points2D intersections(const Ray2D&, const DoubleLineSegment2D&);

// Polygon2D
Points2D intersections(const Polygon2D&, const Line2D&);
Points2D intersections(const Line2D&, const Polygon2D&);
Points2D intersections(const Polygon2D&, const Ray2D&);
Points2D intersections(const Ray2D&, const Polygon2D&);
Points2D intersections(const Polygon2D&, const LineSegment2D&);
Points2D intersections(const LineSegment2D&, const Polygon2D&);
Points2D intersections(const Polygon2D&, const Polygon2D&);

// Curves2D
class intersections_visitor : public boost::static_visitor<Points2D> {
  public:
    template <typename CurveType0, typename CurveType1>
    Points2D operator()(const CurveType0& curve0, const CurveType1& curve1) const {
      return intersections(curve0, curve1);
    }
};

Points2D intersections(const Curve2D&, const Curve2D&);

Points2D intersections(const Curves2D&, const Curve2D&);
Points2D intersections(const Curve2D&, const Curves2D&);
Points2D intersections(const Curves2D&, const Curves2D&);

} // namespace wigeon
