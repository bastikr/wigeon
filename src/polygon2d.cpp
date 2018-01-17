#include "wigeon/polygon2d.h"

#include <algorithm>


namespace wigeon {

void Polygon2D::append(const Point2D& point) {
  data.push_back(point);
}

void Polygon2D::append(double x, double y) {
  data.emplace_back(x, y);
}

void Polygon2D::append(const LineSegment2D& segment) {
  data.push_back(segment.point0());
  data.push_back(segment.point1());
}

int Polygon2D::size() const {
  return data.size();
}

Polygon2D operator+(const Polygon2D& polygon, const Vector2D& v) {
  Polygon2D polygon_new;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_new.append(*it + v);
  }
  return polygon_new;
}

Polygon2D operator-(const Polygon2D& polygon, const Vector2D& v) {
  Polygon2D polygon_new;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_new.append(*it - v);
  }
  return polygon_new;
}

boost::optional<Rectangle2D> Polygon2D::bounding_box() const {
  if (size()==0)
    return boost::optional<Rectangle2D>();
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

boost::optional<Point2D> Polygon2D::point(int i) const {
  if (i<0 || i>=size())
    return boost::optional<Point2D>();
  else
    return data[i];
}

boost::optional<LineSegment2D> Polygon2D::edge(int i) const {
  if (i<0 || i>size()-1)
    return boost::optional<LineSegment2D>();
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

boost::optional<Point2D> Polygon2D::point_looped(int i) const {
  if (size()==0)
    return boost::optional<Point2D>();
  int i_ = positive_modulo(i, size());
  return data[i_];
}

boost::optional<LineSegment2D> Polygon2D::edge_looped(int i) const {
  if (size()==0)
    return boost::optional<LineSegment2D>();
  int i0 = positive_modulo(i, size());
  int i1 = positive_modulo(i0 + 1, size());
  return LineSegment2D(data[i0], data[i1]);
}

Polygon2D rotate(const Rotation2D& R, const Polygon2D& polygon) {
  Polygon2D polygon_rotated;
  for (auto it=polygon.data.begin(); it!=polygon.data.end(); ++it) {
    polygon_rotated.append(rotate(R, *it));
  }
  return polygon_rotated;
}

} // namespace wigeon
