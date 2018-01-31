#include "wigeon/polygon2d.h"

#include <algorithm>


namespace wigeon {

Polygon2D::Polygon2D(const LineSegment2D& segment)
    : data({{segment.point0(), segment.point1()}}) {}

Polygon2D::Polygon2D(const Triangle2D& triangle)
    : data({{triangle.point0(), triangle.point1(), triangle.point2()}}) {}

Polygon2D::Polygon2D(const Rectangle2D& rectangle)
    : data({{rectangle.point00(), rectangle.point10(),
             rectangle.point11(), rectangle.point01()}}) {}

void Polygon2D::push_back(const Point2D& point) {
  data.push_back(point);
}

void Polygon2D::push_back(double x, double y) {
  data.emplace_back(x, y);
}

int Polygon2D::size() const {
  return data.size();
}

double Polygon2D::area() const { 
  double x = point(0).x();
  double y = point(0).y();
  double A = data.back().x()*y - data.back().y()*x;
  for (auto it=data.begin(); it!=data.end(); ++it) {
    A += x*it->y() - y*it->x();
    x = it->x();
    y = it->y();
  }
  return A/2;
}

Polygon2D operator+(const Polygon2D& polygon, const Vector2D& v) {
  Polygon2D polygon_new;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_new.push_back(*it + v);
  }
  return polygon_new;
}

Polygon2D operator-(const Polygon2D& polygon, const Vector2D& v) {
  Polygon2D polygon_new;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_new.push_back(*it - v);
  }
  return polygon_new;
}

Rectangle2D Polygon2D::bounding_box() const {
  if (size()==0)
    throw "0-size polygon has no bounding box.";
  double xmin = data[0].x();
  double xmax = data[0].x();
  double ymin = data[0].y();
  double ymax = data[0].y();
  Point2D p(0,0);
  for (auto it=++data.begin(); it!=data.end(); ++it) {
    p = *it;
    xmin = std::min(xmin, p.x());
    xmax = std::max(xmax, p.x());
    ymin = std::min(ymin, p.y());
    ymax = std::max(ymax, p.y());
  }
  return Rectangle2D(xmin, ymin, xmax, ymax);
}

Point2D Polygon2D::point(int i) const {
  if (i<0 || i>=size())
    throw "Access of out-of-bounds element.";
  else
    return data[i];
}

LineSegment2D Polygon2D::edge(int i) const {
  if (i<0 || i>size()-1)
    throw "Access of out-of-bounds element.";
  if (i==size()-1)
    return LineSegment2D(data[i], data[0]);
  return LineSegment2D(data[i], data[i+1]);
}

namespace {

int positive_modulo(int a, int b) {
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
  return data[i_];
}

LineSegment2D Polygon2D::edge_looped(int i) const {
  if (size()==0)
    throw "Can't access element of 0-size polygon.";
  int i0 = positive_modulo(i, size());
  int i1 = positive_modulo(i0 + 1, size());
  return LineSegment2D(data[i0], data[i1]);
}

Polygon2D rotate(const Rotation2D& R, const Polygon2D& polygon) {
  Polygon2D polygon_rotated;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_rotated.push_back(rotate(R, *it));
  }
  return polygon_rotated;
}

} // namespace wigeon
