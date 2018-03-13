#pragma once

#include <array>

#include "wigeon/rotations2d.h"
#include "wigeon/vector2d.h"


namespace wigeon {

struct Point2D {
  Point2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  std::array<double, 2> data;
};

Point2D operator+(const Point2D& point, const Vector2D& vector);
Point2D operator+(const Vector2D& vector, const Point2D& point);
Point2D operator-(const Point2D& point, const Vector2D& vector);

Vector2D operator-(const Point2D& point0, const Point2D& point1);

Point2D rotate(const Rotation2D&, const Point2D&);

} // namespace wigeon
