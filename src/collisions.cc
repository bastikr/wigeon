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

} // namespace wigeon
