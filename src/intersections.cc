#include "wigeon/intersections.h"


namespace wigeon {

Points2D intersections(const Line2D& line0, const Line2D& line1) {
  const Point2D& p0 = line0.point();
  const Point2D& p1 = line1.point();
  const Vector2D& w0 = line0.direction();
  const Vector2D& w1 = line1.direction();
  double a = w0*w1;
  Points2D points;
  if (1-a*a < 1e-15)
    return Points2D();
  double c0 = (p1-p0) * (w0 - w1*(w0*w1)) / (1-a*a);
  points.push_back(p0 + w0*c0);
  return points;
}

Points2D intersections(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  Points2D points = intersections(Line2D(segment0), Line2D(segment1));
  if (points.size()==0)
    return points;

  Vector2D w = points[0] - segment0.point0();
  double c0 = w*segment0.direction();
  if (c0<=0 || c0>=segment0.length())
    return Points2D();

  w = points[0] - segment1.point0();
  double c1 = w*segment1.direction();
  if (c1<=0 || c1>=segment1.length())
    return Points2D();

  return points;
}

Points2D intersections(const LineSegment2D& segment, const Polygon2D& polygon) {
  Points2D points;
  Points2D points_part;
  for (int i=0; i<polygon.size(); ++i) {
    points_part = intersections(segment, *polygon.edge(i));
    if (points_part.size()==1) {
      points.push_back(points_part[0]);
    }
  }
  return points;
}

Points2D intersections(const Polygon2D& polygon, const LineSegment2D& segment) {
  return intersections(segment, polygon);
}

} // namespace wigeon
