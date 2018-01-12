#include "wigeon/collisions.h"

#include <cmath>

#include "wigeon/distances.h"
#include "wigeon/intersections.h"


namespace wigeon {

boost::optional<Collision<PointCollision, SegmentCollision>>
collision(const UnitVector2D& u, const Point2D& point, const LineSegment2D& segment) {
  Ray2D ray(point, u);
  Points2D points = intersections(ray, segment);
  if (points.size()==0)
    return boost::optional<Collision<PointCollision, SegmentCollision>>();
  Vector2D v = segment.point1() - segment.point0();
  double r = v*(points[0] - segment.point0())/v.length2();
  return Collision<PointCollision, SegmentCollision>(sqrt(distance2(point, points[0])), points[0],
                   PointCollision(),
                   SegmentCollision(r));
}

boost::optional<Collision<SegmentCollision, SegmentCollision>>
collision(const UnitVector2D& u, const LineSegment2D& s0, const LineSegment2D& s1) {
  using T = Collision<SegmentCollision, SegmentCollision>;
  boost::optional<Collision<PointCollision, SegmentCollision>> c_sub;
  boost::optional<T> c;
  c_sub = collision(u, s0.point0(), s1);
  if (c_sub)
    c = T(c_sub->distance, c_sub->point, SegmentCollision(0), c_sub->object1);
  c_sub = collision(u, s0.point1(), s1);
  if (c_sub && (!c || c->distance > c_sub->distance))
      c = T(c_sub->distance, c_sub->point, SegmentCollision(1), c_sub->object1);
  c_sub = collision(u, s1.point0(), s0);
  if (c_sub && (!c || c->distance > c_sub->distance))
      c = T(c_sub->distance, c_sub->point, c_sub->object1, SegmentCollision(0));
  c_sub = collision(u, s1.point1(), s0);
  if (c_sub && (!c || c->distance > c_sub->distance))
      c = T(c_sub->distance, c_sub->point, c_sub->object1, SegmentCollision(1));
  return c;
}

} // namespace wigeon
