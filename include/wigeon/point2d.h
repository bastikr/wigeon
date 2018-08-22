#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"


namespace wigeon {

struct Point2D {
  Point2D(double x, double y) : data({{x, y}}) {}

  double& x() {return data[0];}
  double x() const {return data[0];}

  double& y() {return data[1];}
  double y() const {return data[1];}

  std::array<double, 2> data;
};

Point2D operator+(const Point2D&, const Vector2D&);
Point2D operator+(const Vector2D&, const Point2D&);
Point2D operator-(const Point2D&, const Vector2D&);

Vector2D operator-(const Point2D&, const Point2D&);

Point2D rotate(const Rotation2D&, const Point2D&);

} // namespace wigeon
