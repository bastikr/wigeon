#include "wigeon/intersections.h"

#include "wigeon/distances.h"


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

Points2D intersections(const Line2D& line, const Ray2D& ray) {
  const Point2D& p0 = ray.point();
  const Point2D& p1 = line.point();
  const Vector2D& w0 = ray.direction();
  const Vector2D& w1 = line.direction();
  double a = w0*w1;
  Points2D points;
  if (1-a*a < 1e-15)
    return Points2D();
  double c0 = (p1-p0) * (w0 - w1*(w0*w1)) / (1-a*a);
  if (c0 <= 0)
    return Points2D();
  points.push_back(p0 + w0*c0);
  return points;
}

Points2D intersections(const Ray2D& ray, const Line2D& line) {
  return intersections(line, ray);
}

Points2D intersections(const Ray2D& ray, const LineSegment2D& segment) {
  Points2D points = intersections(ray, Line2D(segment));
  if (points.size()==0)
    return points;

  Vector2D w = points[0] - segment.point0();
  double c0 = w*segment.direction();
  if (c0<=-1e-15 || c0>=segment.length()*(1+1e-15))
    return Points2D();

  return points;
}

Points2D intersections(const LineSegment2D& segment, const Ray2D& ray) {
  return intersections(ray, segment);
}

namespace {

bool is_same_intersection(const Point2D& p, const Points2D& points, bool is_last) {
  if (points.size()==0)
    return false;
  if (distance2(points.back(), p) < 1e-15)
    return true;
  if (is_last && distance2(points.front(), p) < 1e-15)
    return true;
  return false;
}

} // anonymous namespace

Points2D intersections(const Ray2D& ray, const Polygon2D& polygon) {
  Points2D points;
  Points2D points_part;
  for (int i=0; i<polygon.size(); ++i) {
    points_part = intersections(ray, *polygon.edge(i));
    if (points_part.size()==1 && !is_same_intersection(points_part[0], points, i==polygon.size()-1))
      points.push_back(points_part[0]);
  }
  return points;
}

Points2D intersections(const Polygon2D& polygon, const Ray2D& ray) {
  return intersections(ray, polygon);
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
    if (points_part.size()==1 && !is_same_intersection(points_part[0], points, i==polygon.size()-1))
      points.push_back(points_part[0]);
  }
  return points;
}

Points2D intersections(const Polygon2D& polygon, const LineSegment2D& segment) {
  return intersections(segment, polygon);
}


Points2D intersections(const Polygon2D& polygon0, const Polygon2D& polygon1) {
  Points2D points;
  Points2D points_part;
  for (int i=0; i<polygon0.size(); ++i) {
    points_part = intersections(*polygon0.edge(i), polygon1);
    if (points_part.size() > 0) {
      points.insert(points.end(), points_part.begin(), points_part.end());
    }
  }
  return points;
}

} // namespace wigeon
