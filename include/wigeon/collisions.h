#pragma once

#include <boost/optional.hpp>

#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"


namespace wigeon {

struct PointCollision {};

struct SegmentCollision {
  SegmentCollision(double r) : r(r) {}
  double r;
};

template <class T0, class T1>
struct Collision {
  Collision(double distance, const Point2D& point, const T0& object0, const T1& object1)
      : distance(distance), point(point), object0(object0), object1(object1) {}
  double distance;
  Point2D point;
  T0 object0;
  T1 object1;
};


boost::optional<Collision<PointCollision, SegmentCollision>>
collision(const UnitVector2D& u, const Point2D&, const LineSegment2D&);

} // namespace wigeon
