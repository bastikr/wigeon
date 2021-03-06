#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"
#include "wigeon/point2d.h"
#include "wigeon/linesegment2d.h"


namespace wigeon {

struct Triangle2D {
  Triangle2D() {}
  Triangle2D(const Point2D&, const Point2D&, const Point2D&);

  Point2D point0() const;
  void set_point0(const Point2D&);

  Point2D point1() const;
  void set_point1(const Point2D&);

  Point2D point2() const;
  void set_point2(const Point2D&);

  double length() const;
  double area() const;

  Triangle2D reverse() const;

  std::array<double, 6> data;
};

Triangle2D operator+(const Triangle2D&, const Vector2D&);
Triangle2D operator+(const Vector2D&, const Triangle2D&);

Triangle2D operator-(const Triangle2D&, const Vector2D&);

Triangle2D rotate(const Rotation2D&, const Triangle2D&);

} // namespace wigeon
