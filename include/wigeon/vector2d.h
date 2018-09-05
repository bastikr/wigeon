#pragma once

#include <array>

#include "wigeon/rotations2d.h"


namespace wigeon {

struct Point2D;

struct Vector2D {
  Vector2D() {}
  Vector2D(double x, double y) : data({{x, y}}) {}
  explicit Vector2D(const Point2D&);

  double x() const {return data[0];}
  void set_x(double x) {data[0] = x;}

  double y() const {return data[1];}
  void set_y(double y) {data[1] = y;}

  double length2() const;
  double length() const;

  Vector2D reverse() const;

  std::array<double, 2> data;
};


Vector2D operator+(const Vector2D&, const Vector2D&);

Vector2D operator-(const Vector2D&);
Vector2D operator-(const Vector2D&, const Vector2D&);

Vector2D operator*(const Vector2D&, double);
Vector2D operator*(double, const Vector2D&);
double operator*(const Vector2D&, const Vector2D&);

Vector2D operator/(const Vector2D&, double);


struct UnitVector2D : public Vector2D {
  UnitVector2D() {}
  UnitVector2D(const Vector2D& v) : Vector2D(v/v.length()) {}
  UnitVector2D(double x, double y) : UnitVector2D(Vector2D(x, y)) {};
};

UnitVector2D normalvector(const Vector2D&);
UnitVector2D normalvector(const UnitVector2D&);

Vector2D rotate(const Rotation2D&, const Vector2D&);
UnitVector2D rotate(const Rotation2D&, const UnitVector2D&);

double cross(const Vector2D& vector0, const Vector2D& vector1);

} // namespace wigeon
