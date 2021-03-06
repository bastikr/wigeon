#pragma once

#include <array>

#include "wigeon/vector1d.h"


namespace wigeon {

struct Point1D {
  Point1D() {}
  Point1D(double x);
  explicit Point1D(const Vector1D& v);

  double x() const;
  void set_x(double x);

  std::array<double, 1> data;
};

Point1D operator+(const Point1D&, const Vector1D&);
Point1D operator+(const Vector1D&, const Point1D&);
Point1D operator-(const Point1D&, const Vector1D&);

Vector1D operator-(const Point1D&, const Point1D&);

} // namespace wigeon
