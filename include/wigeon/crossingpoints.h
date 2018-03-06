#pragma once

#include <boost/variant.hpp>
#include <vector>

#include "wigeon/point2d.h"
#include "wigeon/line2d.h"
#include "wigeon/ray2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/polygon2d.h"
#include "wigeon/intersections.h"


namespace wigeon {

std::vector<Point2D> crossingpoints(const Line2D&, const Line2D&);

std::vector<Point2D> crossingpoints(const Ray2D&, const Ray2D&);
std::vector<Point2D> crossingpoints(const Ray2D&, const Line2D&);
std::vector<Point2D> crossingpoints(const Line2D&, const Ray2D&);

std::vector<Point2D> crossingpoints(const LineSegment2D&, const LineSegment2D&);
std::vector<Point2D> crossingpoints(const LineSegment2D&, const Line2D&);
std::vector<Point2D> crossingpoints(const Line2D&, const LineSegment2D&);
std::vector<Point2D> crossingpoints(const LineSegment2D&, const Ray2D&);
std::vector<Point2D> crossingpoints(const Ray2D&, const LineSegment2D&);

} // namespace wigeon
