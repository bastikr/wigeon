#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"


namespace wigeon {

struct Point2D {
  Point2D() {}
  Point2D(double x, double y) : data({{x, y}}) {}
  explicit Point2D(const Vector2D& v) : data(v.data) {};

  double x() const {return data[0];}
  void set_x(double x) {data[0] = x;}

  double y() const {return data[1];}
  void set_y(double y) {data[1] = y;}

  std::array<double, 2> data;
};

Point2D operator+(const Point2D&, const Vector2D&);
Point2D operator+(const Vector2D&, const Point2D&);
Point2D operator-(const Point2D&, const Vector2D&);

Vector2D operator-(const Point2D&, const Point2D&);

Point2D rotate(const Rotation2D&, const Point2D&);

} // namespace wigeon
