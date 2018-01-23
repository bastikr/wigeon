#include "wigeon/distances.h"

#include <cmath>
#include <algorithm>


namespace wigeon {

// Point

double distance2(const Point2D& point0, const Point2D& point1) {
  double dx = point1.x() - point0.x();
  double dy = point1.y() - point0.y();
  return dx*dx + dy*dy;
}


// LineSegment

double distance2(const LineSegment2D& segment, const Point2D& point) {
  Vector2D v = segment.point1() - segment.point0();
  Vector2D w = point - segment.point0();
  double alpha = v*v;
  double r = (v*w)/alpha;
  if (r <= 0)
    return distance2(point, segment.point0());
  if (r >= 1)
    return distance2(point, segment.point1());
  return pow(v.y()*w.x() - v.x()*w.y(), 2)/alpha;
}

double distance2(const Point2D& point, const LineSegment2D& segment) {
  return distance2(segment, point);
}

namespace {
bool isintersecting(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  Vector2D v = segment0.point1() - segment0.point0();
  Vector2D w1 = segment1.point0() - segment0.point0();
  Vector2D w2 = segment1.point1() - segment0.point0();
  double alpha = v*v;

  double c1 = cross(v, w1);
  double c2 = cross(v, w2);

  if ((c1>=0 && c2>=0) || (c1<=0 && c2<=0)) {
    return false;
  } else {
    double r1 = (v*w1)/alpha;
    double r2 = (v*w2)/alpha;
    if (0<r1 && r1<1 && 0<r2 && r2<1)
      return true;
  }
  return false;
}
} // namespace

double distance2(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  double d = distance2(segment0.point0(), segment1);
  d = std::min(d, distance2(segment0.point1(), segment1));
  d = std::min(d, distance2(segment1.point0(), segment0));
  d = std::min(d, distance2(segment1.point1(), segment0));
  if (isintersecting(segment0, segment1))
    return -d;
  return d;
}


// Line

double distance2(const Line2D& line, const Point2D& point) {
  const UnitVector2D& v = line.direction();
  Vector2D w = point - line.point();
  return pow(v.y()*w.x() - v.x()*w.y(), 2);
}

double distance2(const Point2D& point, const Line2D& line) {
  return distance2(line, point);
}

double distance2(const Line2D& line, const LineSegment2D& segment) {
  Vector2D w0 = segment.point0() - line.point();
  Vector2D w1 = segment.point1() - line.point();

  double c0 = cross(line.direction(), w0);
  double c1 = cross(line.direction(), w1);

  double d0 = distance2(line, segment.point0());
  double d1 = distance2(line, segment.point1());

  double dmin = std::min(d0, d1);

  if ((c0<0 && c1<0) || (c0>1 && c1>1)) {
    return dmin;
  } else {
    return -dmin;
  }
}

double distance2(const LineSegment2D& segment, const Line2D& line) {
  return distance2(line, segment);
}


// Ray

double distance2(const Ray2D& ray, const Point2D& point) {
  const UnitVector2D& v = ray.direction();
  Vector2D w = point - ray.point();
  if (w*ray.direction()<=0)
    return w.length2();
  return pow(v.y()*w.x() - v.x()*w.y(), 2);
}

double distance2(const Point2D& point, const Ray2D& ray) {
  return distance2(ray, point);
}

namespace {
bool isintersecting(const LineSegment2D& segment, const Ray2D& ray) {
  const UnitVector2D& v = ray.direction();
  Vector2D w1 = segment.point0() - ray.point();
  Vector2D w2 = segment.point1() - ray.point();

  double c1 = cross(v, w1);
  double c2 = cross(v, w2);

  if ((c1>=0 && c2>=0) || (c1<=0 && c2<=0))
    return false;
  double r1 = (v*w1);
  double r2 = (v*w2);
  if (r1 + r2 > 0)
    return true;
  return false;
}
} // namespace

double distance2(const Ray2D& ray, const LineSegment2D& segment) {
  double d = distance2(ray.point(), segment);
  d = std::min(d, distance2(segment.point1(), ray));
  d = std::min(d, distance2(segment.point0(), ray));
  if (isintersecting(segment, ray))
    return -d;
  return d;
}

double distance2(const LineSegment2D& segment, const Ray2D& ray) {
  return distance2(ray, segment);
}


// Circle

double distance2(const Circle2D& circle, const Point2D& point) {
  double d2 = distance2(point, circle.center());
  double d = circle.radius() - sqrt(d2);
  return d*d;
}

double distance2(const Point2D& point, const Circle2D& circle) {
  return distance2(circle, point);
}


// Rectangle

double distance2(const Rectangle2D& rectangle, const Point2D& point) {
  double d = distance2(point, LineSegment2D(rectangle.point00(), rectangle.point01()));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.point01(), rectangle.point11())));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.point11(), rectangle.point10())));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.point10(), rectangle.point00())));
  return d;
}

double distance2(const Point2D& point, const Rectangle2D& rectangle) {
  return distance2(rectangle, point);
}


// Polygon

double distance2(const Polygon2D& polygon, const Point2D& point) {
  size_t size = polygon.size();
  if (size==0)
    return std::numeric_limits<double>::quiet_NaN();
  if (size==1)
    return distance2(*polygon.point(0), point);

  double d2 = std::numeric_limits<double>::infinity();
  for (int i=0; i<size; ++i) {
    d2 = std::min(d2, distance2(*polygon.edge(i), point));
  }
  return d2;
}

double distance2(const Point2D& point, const Polygon2D& polygon) {
  return distance2(polygon, point);
}

} // namespace wigeon
