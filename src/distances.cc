#include "geometry/distances.h"

#include <cmath>
#include <algorithm>


namespace geometry {

// point - ...

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

double distance2(const Point2D& point, const Line2D& line) {
  const Vector2D& v = line.getDirection();
  Vector2D w = point - line.getPoint();
  double alpha = v*v;
  return pow(v.y()*w.x() - v.x()*w.y(), 2)/alpha;
}

double distance2(const Line2D& line, const Point2D& point) {
  return distance2(point, line);
}

double distance2(const Point2D& point, const Ray2D& ray) {
  const Vector2D& v = ray.getDirection();
  Vector2D w = point - ray.getPoint();
  if (w*ray.getDirection()<=0)
    return w.length2();
  double alpha = v*v;
  return pow(v.y()*w.x() - v.x()*w.y(), 2)/alpha;
}

double distance2(const Ray2D& ray, const Point2D& point) {
  return distance2(point, ray);
}

double distance2(const Point2D& point, const Rectangle2D& rectangle) {
  double d = distance2(point, LineSegment2D(rectangle.getPoint00(), rectangle.getPoint01()));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.getPoint01(), rectangle.getPoint11())));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.getPoint11(), rectangle.getPoint10())));
  d = std::min(d, distance2(point, LineSegment2D(rectangle.getPoint10(), rectangle.getPoint00())));
  return d;
}

double distance2(const Rectangle2D& rectangle, const Point2D& point) {
  return distance2(point, rectangle);
}

double distance2(const Point2D& point, const Circle2D& circle) {
  double d2 = distance2(point, circle.center);
  double d = circle.radius - sqrt(d2);
  return d*d;
}

double distance2(const Circle2D& circle, const Point2D& point) {
  return distance2(point, circle);
}


// LineSegment - ...

bool isintersecting(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  Vector2D v = segment0.getPoint1() - segment0.getPoint0();
  Vector2D w1 = segment1.getPoint0() - segment0.getPoint0();
  Vector2D w2 = segment1.getPoint1() - segment0.getPoint0();
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

double distance2(const LineSegment2D& segment0, const LineSegment2D& segment1) {
  double d = distance2(segment0.getPoint0(), segment1);
  d = std::min(d, distance2(segment0.getPoint1(), segment1));
  d = std::min(d, distance2(segment1.getPoint0(), segment0));
  d = std::min(d, distance2(segment1.getPoint1(), segment0));
  if (isintersecting(segment0, segment1))
    return -d;
  return d;
}

double distance2(const LineSegment2D& segment, const Line2D& line) {
  Vector2D w0 = segment.getPoint0() - line.getPoint();
  Vector2D w1 = segment.getPoint1() - line.getPoint();

  double c0 = cross(line.direction, w0);
  double c1 = cross(line.direction, w1);

  double d0 = distance2(line, segment.getPoint0());
  double d1 = distance2(line, segment.getPoint1());

  double dmin = std::min(d0, d1);

  if ((c0<0 && c1<0) || (c0>1 && c1>1)) {
    return dmin;
  } else {
    return -dmin;
  }
}

double distance2(const Line2D& line, const LineSegment2D& segment) {
  return distance2(segment, line);
}

double isintersecting(const LineSegment2D& segment, const Ray2D& ray) {
  const Vector2D& v = ray.getDirection();
  Vector2D w1 = segment.getPoint0() - ray.getPoint();
  Vector2D w2 = segment.getPoint1() - ray.getPoint();
  double alpha = v*v;

  double c1 = cross(v, w1);
  double c2 = cross(v, w2);

  if ((c1>=0 && c2>=0) || (c1<=0 && c2<=0))
    return false;
  double r1 = (v*w1)/alpha;
  double r2 = (v*w2)/alpha;
  Line2D line = Line2D(ray.getPoint(), ray.getDirection());
  if (r1 + r2 > 0)
    return true;
  return false;
}

double distance2(const LineSegment2D& segment, const Ray2D& ray) {
  double d = distance2(ray.getPoint(), segment);
  d = std::min(d, distance2(segment.getPoint1(), ray));
  d = std::min(d, distance2(segment.getPoint0(), ray));
  if (isintersecting(segment, ray))
    return -d;
  return d;
}

double distance2(const Ray2D& ray, const LineSegment2D& segment) {
  return distance2(segment, ray);
}

} // namespace geometry
