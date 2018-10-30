#pragma once

#include <vector>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"
#include "wigeon/rectangle2d.h"


namespace wigeon {

struct PolyLine2D {
  PolyLine2D();
  PolyLine2D(std::initializer_list<Point2D> points);
  template<class InputIt>
  PolyLine2D(InputIt first, InputIt last)
      : points(first, last) {}
  explicit PolyLine2D(const LineSegment2D&);

  void push_back(const Point2D&);
  void push_back(double x, double y);

  size_t size() const;

  double length() const;

  Point2D point(size_t i) const;
  LineSegment2D edge(size_t i) const;

  PolyLine2D reverse() const;

  std::vector<Point2D> points;
};

PolyLine2D operator+(const PolyLine2D&, const Vector2D&);
PolyLine2D operator+(const Vector2D&, const PolyLine2D&);

PolyLine2D operator-(const PolyLine2D&, const Vector2D&);

PolyLine2D rotate(const Rotation2D&, const PolyLine2D&);

} // namespace wigeon
