#pragma once

#include <array>


namespace geometry {

struct Vector2D;

struct Point2D {
  Point2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  Point2D operator+(const Vector2D& vector) const;
  Point2D operator-(const Vector2D& vector) const;
  Vector2D operator-(const Point2D& point) const;

  std::array<double, 2> data;
};

} // namespace geometry
