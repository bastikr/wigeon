#pragma once

#include <array>

#include "wigeon/vector1d.h"


namespace wigeon {

struct Point1D {
  Point1D(double x) : data({{x}}) {}

  double x() const {return data[0];}

  Point1D operator+(const Vector1D& vector) const;
  Point1D operator-(const Vector1D& vector) const;
  Vector1D operator-(const Point1D& point) const;

  std::array<double, 1> data;
};

Point1D operator+(const Point1D& point, const Vector1D& vector);
Point1D operator+(const Vector1D& vector, const Point1D& point);
Point1D operator-(const Point1D& point, const Vector1D& vector);
Point1D operator-(const Vector1D& vector, const Point1D& point);

Vector1D operator-(const Point1D& point0, const Point1D& point1);

} // namespace wigeon
