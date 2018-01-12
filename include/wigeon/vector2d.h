#pragma once

#include <array>

#include "wigeon/rotations2d.h"


namespace wigeon {

struct Vector2D {
  Vector2D(double x, double y) : data({{x, y}}) {}

  double x() const {return data[0];}
  double y() const {return data[1];}

  double length2() const;
  double length() const;

  std::array<double, 2> data;
};


Vector2D operator+(const Vector2D& vector0, const Vector2D& vector1);

Vector2D operator-(const Vector2D& vector);
Vector2D operator-(const Vector2D& vector0, const Vector2D& vector1);

Vector2D operator*(const Vector2D& vector, double a);
Vector2D operator*(double a, const Vector2D& vector);
double operator*(const Vector2D& vector0, const Vector2D& vector1);

Vector2D operator/(const Vector2D& vector, double a);


struct UnitVector2D : public Vector2D {
  UnitVector2D(const Vector2D& v) : Vector2D(v/v.length()) {}
  UnitVector2D(double x, double y) : UnitVector2D(Vector2D(x, y)) {};
};

UnitVector2D normalvector(const Vector2D&);
UnitVector2D normalvector(const UnitVector2D&);

Vector2D rotate(const Rotation2D&, const Vector2D&);
UnitVector2D rotate(const Rotation2D&, const UnitVector2D&);

double cross(const Vector2D& vector0, const Vector2D& vector1);

} // namespace wigeon
