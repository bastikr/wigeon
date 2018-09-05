#include "wigeon/polyline2d.h"

#include <algorithm>


namespace wigeon {

PolyLine2D::PolyLine2D(std::initializer_list<Point2D> points)
    : points(points) {}

PolyLine2D::PolyLine2D(const LineSegment2D& segment)
    : points({{segment.point0(), segment.point1()}}) {}

void PolyLine2D::push_back(const Point2D& point) {
  points.push_back(point);
}

void PolyLine2D::push_back(double x, double y) {
  points.emplace_back(x, y);
}

size_t PolyLine2D::size() const {
  return points.size();
}

double PolyLine2D::length() const {
  double l = 0;
  for (size_t i=0; i<size()-1; ++i) {
    l += edge(i).length();
  }
  return l;
}

PolyLine2D PolyLine2D::reverse() const {
  std::vector<Point2D> rpoints(points.rbegin(), points.rend());
  PolyLine2D rpolygon;
  rpolygon.points = rpoints;
  return rpolygon;
}

PolyLine2D operator+(const PolyLine2D& polyline, const Vector2D& vector) {
  PolyLine2D polyline_new;
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    polyline_new.push_back(*it + vector);
  }
  return polyline_new;
}

PolyLine2D operator+(const Vector2D& vector, const PolyLine2D& polyline) {
  PolyLine2D polyline_new;
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    polyline_new.push_back(vector + *it);
  }
  return polyline_new;
}

PolyLine2D operator-(const PolyLine2D& polyline, const Vector2D& vector) {
  PolyLine2D polyline_new;
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    polyline_new.push_back(*it - vector);
  }
  return polyline_new;
}


Rectangle2D PolyLine2D::bounding_box() const {
  if (size()==0)
    throw "0-size polyline has no bounding box.";
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

Point2D PolyLine2D::point(size_t i) const {
  if (i>=size())
    throw "Access of out-of-bounds element.";
  else
    return points[i];
}

LineSegment2D PolyLine2D::edge(size_t i) const {
  if (i>size()-1)
    throw "Access of out-of-bounds element.";
  if (i==size()-1)
    return LineSegment2D(points[i], points[0]);
  return LineSegment2D(points[i], points[i+1]);
}

PolyLine2D rotate(const Rotation2D& R, const PolyLine2D& polyline) {
  PolyLine2D polyline_rotated;
  for (auto it=polyline.points.begin(); it!=polyline.points.end(); ++it) {
    polyline_rotated.push_back(rotate(R, *it));
  }
  return polyline_rotated;
}

} // namespace wigeon
