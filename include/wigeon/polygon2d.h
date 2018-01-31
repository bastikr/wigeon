#pragma once

#include <vector>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/triangle2d.h"
#include "wigeon/rectangle2d.h"


namespace wigeon {

struct Polygon2D {
  Polygon2D() : data() {}
  explicit Polygon2D(const LineSegment2D&);
  explicit Polygon2D(const Triangle2D&);
  explicit Polygon2D(const Rectangle2D&);

  void push_back(const Point2D& point);
  void push_back(double x, double y);

  int size() const;
  double area() const;

  Rectangle2D bounding_box() const;

  Point2D point(int i) const;
  LineSegment2D edge(int i) const;

  Point2D point_looped(int i) const;
  LineSegment2D edge_looped(int i) const;

  std::vector<Point2D> data;
};

Polygon2D operator+(const Polygon2D& polygon, const Vector2D& v);
Polygon2D operator-(const Polygon2D& polygon, const Vector2D& v);

Polygon2D rotate(const Rotation2D&, const Polygon2D&);

} // namespace wigeon
