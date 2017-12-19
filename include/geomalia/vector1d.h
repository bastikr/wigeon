#pragma once

#include <array>

#include "geomalia/point1d.h"


namespace geomalia {

struct Vector1D {
  Vector1D(double x) : data({{x}}) {}

  double x() const {return data[0];}

  double length2() const;
  double length() const;

  Point1D operator+(Point1D point) const;
  Vector1D operator+(Vector1D vector) const;

  Vector1D operator-() const;
  Point1D operator-(Point1D point) const;
  Vector1D operator*(double a) const;
  double operator*(const Vector1D& vector) const;
  Vector1D operator/(double a) const;

  std::array<double, 1> data;
};

} // namespace geomalia
