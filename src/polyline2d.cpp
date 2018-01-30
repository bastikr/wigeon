#include "wigeon/polyline2d.h"

#include <algorithm>


namespace wigeon {

PolyLine2D::PolyLine2D(const LineSegment2D& segment)
    : data({{segment.point0(), segment.point1()}}) {}


void PolyLine2D::push_back(const Point2D& point) {
  data.push_back(point);
}

void PolyLine2D::push_back(double x, double y) {
  data.emplace_back(x, y);
}

int PolyLine2D::size() const {
  return data.size();
}

PolyLine2D operator+(const PolyLine2D& polyline, const Vector2D& v) {
  PolyLine2D polyline_new;
  for (auto it=polyline.data.begin(); it!=polyline.data.end(); ++it) {
    polyline_new.push_back(*it + v);
  }
  return polyline_new;
}

PolyLine2D operator-(const PolyLine2D& polyline, const Vector2D& v) {
  PolyLine2D polyline_new;
  for (auto it=polyline.data.begin(); it!=polyline.data.end(); ++it) {
    polyline_new.push_back(*it - v);
  }
  return polyline_new;
}

Rectangle2D PolyLine2D::bounding_box() const {
  if (size()==0)
    throw "0-size polyline has no bounding box.";
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

Point2D PolyLine2D::point(int i) const {
  if (i<0 || i>=size())
    throw "Access of out-of-bounds element.";
  else
    return data[i];
}

LineSegment2D PolyLine2D::edge(int i) const {
  if (i<0 || i>size()-1)
    throw "Access of out-of-bounds element.";
  if (i==size()-1)
    return LineSegment2D(data[i], data[0]);
  return LineSegment2D(data[i], data[i+1]);
}

PolyLine2D rotate(const Rotation2D& R, const PolyLine2D& polyline) {
  PolyLine2D polyline_rotated;
  for (auto it=polyline.data.begin(); it!=polyline.data.end(); ++it) {
    polyline_rotated.push_back(rotate(R, *it));
  }
  return polyline_rotated;
}

} // namespace wigeon
