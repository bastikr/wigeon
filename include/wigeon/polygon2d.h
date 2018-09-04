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
  Polygon2D() {}
  Polygon2D(std::initializer_list<Point2D> points)
      : points(points) {}
  explicit Polygon2D(const LineSegment2D&);
  explicit Polygon2D(const Triangle2D&);
  explicit Polygon2D(const Rectangle2D&);

  void push_back(const Point2D&);
  void push_back(double x, double y);

  size_t size() const;
  double area() const;

  double length() const;

  Rectangle2D bounding_box() const;

  Point2D point(size_t i) const;
  LineSegment2D edge(size_t i) const;

  Point2D point_looped(int i) const;
  LineSegment2D edge_looped(int i) const;

  Polygon2D reverse() const;

  std::vector<Point2D> points;
};

Polygon2D operator+(const Polygon2D&, const Vector2D&);
Polygon2D operator+(const Vector2D&, const Polygon2D&);

Polygon2D operator-(const Polygon2D&, const Vector2D&);

Polygon2D rotate(const Rotation2D&, const Polygon2D&);

} // namespace wigeon
