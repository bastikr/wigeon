#include "geometry/geometry.h"

#include <cmath>
#include <algorithm>

using namespace std;

namespace geometry {

double distance2(const Point2D& point0, const Point2D& point1) {
  double dx = point1.x() - point0.x();
  double dy = point1.y() - point0.y();
  return dx*dx + dy*dy;
}

double distance2(const Point2D& point0, const LineSegment2D& segment0) {
  Vector2D v = segment0.getPoint1() - segment0.getPoint0();
  Vector2D w = point0 - segment0.getPoint0();
  double alpha = v*v;
  double r = (v*w)/alpha;
  if (r <= 0)
    return distance2(point0, segment0.getPoint0());
  if (r >= 1)
    return distance2(point0, segment0.getPoint1());
  return pow(v.y()*w.x() - v.x()*w.y(), 2)/alpha;
}

double distance2(const LineSegment2D& segment0, const Point2D& point0) {
  return distance2(point0, segment0);
}

// double distance2(const LineSegment2D& segment0, const LineSegment2D& segment1) {
//   double d = distance2(segment0.getPoint0(), segment1);
//   d = min(distance2(segment0.getPoint1(), segment1));
//   d = min(distance2(segment1.getPoint0(), segment0));
//   d = min(distance2(segment1.getPoint1(), segment0));
//   if segmentsintersect(segment0, segment1)
//     return -d;
//   return d;
// }

// bool isintersecting(const LineSegment2D& segment0, const LineSegment2D& segment1) {
//   Vector2D v = segment0.getPoint1() - segment0.getPoint0();
//   Vector2D w1 = segment1.getPoint0() - segment0.getPoint0();
//   Vector2D w2 = segment1.getPoint1() - segment0.getPoint0();
//   double alpha = v*v;
//
//   double c1 = cross(v, w1);
//   double c2 = cross(v, w2);
//   if (c1==0 && c2==0) // segment is on line
//     double r1 = (v*w1)/alpha;
//     double r2 = (v*w2)/alpha;
//     return !((r1<0 && r2<0) || (r1>1 && r2>1));
//   if (c1==0) // first segment point is on line
//     r = (v*w1)/alpha;
//     return 0 <= r && r <= 1;
//   if (c2==0) // second segment point is on line
//     r = (v*w2)/alpha;
//     return 0 <= r && r <= 1;
//   return c1*c2 < 0;
// }


// double distance2(const Point2D& point0, const Polygon2D& polygon0) {
//   double d = distance2(point0, *polygon0.getLineSegment(0));
//   for (int i=1; i<polygon0.size(); ++i) {
//     d = std::min(d, distance2(point0, *polygon0.getLineSegment(i)));
//   }
//   return d;
// }
// double distance2(const Polygon2D& polygon0, const Point2D& point0) {
//   return distance2(point0, polygon0);
// }
// double distance2(const LineSegment2D& segment, const Polygon2D& polygon) {}
// double distance2(const Polygon2D& polygon, const LineSegment2D& segment) {}
// distance(const Polygon2D& polygon0, const Polygon2D polygon1) {}

} // namespace geometry
