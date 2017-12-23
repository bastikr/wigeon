#pragma once

#include <array>


namespace geomalia {

struct Vector2D {
  Vector2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  double length2() const;
  double length() const;

  Vector2D operator+(Vector2D vector) const;

  Vector2D operator-() const;
  Vector2D operator-(Vector2D vector) const;
  Vector2D operator*(double a) const;
  double operator*(const Vector2D& vector) const;
  Vector2D operator/(double a) const;

  std::array<double, 2> data;
};

double cross(const Vector2D& vector0, const Vector2D& vector1);

} // namespace geomalia
