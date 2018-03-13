#include "wigeon/polygon2d.h"

#include <algorithm>


namespace wigeon {

Polygon2D::Polygon2D(const LineSegment2D& segment)
    : points({{segment.point0(), segment.point1()}}) {}

Polygon2D::Polygon2D(const Triangle2D& triangle)
    : points({{triangle.point0(), triangle.point1(), triangle.point2()}}) {}

Polygon2D::Polygon2D(const Rectangle2D& rectangle)
    : points({{rectangle.point00(), rectangle.point10(),
             rectangle.point11(), rectangle.point01()}}) {}

void Polygon2D::push_back(const Point2D& point) {
  points.push_back(point);
}

void Polygon2D::push_back(double x, double y) {
  points.emplace_back(x, y);
}

size_t Polygon2D::size() const {
  return points.size();
}

double Polygon2D::area() const { 
  double x = point(0).x();
  double y = point(0).y();
  double A = points.back().x()*y - points.back().y()*x;
  for (auto it=points.begin(); it!=points.end(); ++it) {
    A += x*it->y() - y*it->x();
    x = it->x();
    y = it->y();
  }
  return A/2;
}

double Polygon2D::length() const {
  double l = 0;
  for (size_t i=0; i<size(); ++i) {
    l += edge(i).length();
  }
  return l;
}

Polygon2D operator+(const Polygon2D& polygon, const Vector2D& vector) {
  Polygon2D polygon_new;
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    polygon_new.push_back(*it + vector);
  }
  return polygon_new;
}

Polygon2D operator+(const Vector2D& vector, const Polygon2D& polygon) {
  Polygon2D polygon_new;
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    polygon_new.push_back(vector + *it);
  }
  return polygon_new;
}

Polygon2D operator-(const Polygon2D& polygon, const Vector2D& vector) {
  Polygon2D polygon_new;
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    polygon_new.push_back(*it - vector);
  }
  return polygon_new;
}

Rectangle2D Polygon2D::bounding_box() const {
  if (size()==0)
    throw "0-size polygon has no bounding box.";
  double xmin = points[0].x();
  double xmax = points[0].x();
  double ymin = points[0].y();
  double ymax = points[0].y();
  Point2D p(0,0);
  for (auto it=++points.begin(); it!=points.end(); ++it) {
    p = *it;
    xmin = std::min(xmin, p.x());
    xmax = std::max(xmax, p.x());
    ymin = std::min(ymin, p.y());
    ymax = std::max(ymax, p.y());
  }
  return Rectangle2D(xmin, ymin, xmax, ymax);
}

Point2D Polygon2D::point(size_t i) const {
  if (i>=size())
    throw "Access of out-of-bounds element.";
  else
    return points[i];
}

LineSegment2D Polygon2D::edge(size_t i) const {
  if (i>size()-1)
    throw "Access of out-of-bounds element.";
  if (i==size()-1)
    return LineSegment2D(points[i], points[0]);
  return LineSegment2D(points[i], points[i+1]);
}

namespace {

size_t positive_modulo(int a, int b) {
  if (a >= 0) {
    return a % b;
  } else {
    return (a % b + b) % b;
  }
}

} // anonymous namespace

Point2D Polygon2D::point_looped(int i) const {
  if (size()==0)
    throw "Can't access element of 0-size polygon.";
  int i_ = positive_modulo(i, size());
  return points[i_];
}

LineSegment2D Polygon2D::edge_looped(int i) const {
  if (size()==0)
    throw "Can't access element of 0-size polygon.";
  int i0 = positive_modulo(i, size());
  int i1 = positive_modulo(i0 + 1, size());
  return LineSegment2D(points[i0], points[i1]);
}

Polygon2D rotate(const Rotation2D& R, const Polygon2D& polygon) {
  Polygon2D polygon_rotated;
  for (auto it=polygon.points.begin(); it!=polygon.points.end(); ++it) {
    polygon_rotated.push_back(rotate(R, *it));
  }
  return polygon_rotated;
}

} // namespace wigeon
