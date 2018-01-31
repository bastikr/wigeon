#pragma once

#include <vector>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/rectangle2d.h"


namespace wigeon {

struct PolyLine2D {
  PolyLine2D() : points() {}
  explicit PolyLine2D(const LineSegment2D&);

  void push_back(const Point2D& point);
  void push_back(double x, double y);

  int size() const;

  Rectangle2D bounding_box() const;

  Point2D point(int i) const;
  LineSegment2D edge(int i) const;

  std::vector<Point2D> points;
};

PolyLine2D operator+(const PolyLine2D& polygon, const Vector2D& v);
PolyLine2D operator-(const PolyLine2D& polygon, const Vector2D& v);

PolyLine2D rotate(const Rotation2D&, const PolyLine2D&);

} // namespace wigeon
