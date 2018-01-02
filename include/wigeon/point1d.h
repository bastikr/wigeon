#pragma once

#include <array>


namespace wigeon {

struct Vector1D;

struct Point1D {
  Point1D(double x) : data({{x}}) {}

  double x() const {return data[0];}

  Point1D operator+(const Vector1D& vector) const;
  Point1D operator-(const Vector1D& vector) const;
  Vector1D operator-(const Point1D& point) const;

  std::array<double, 1> data;
};

} // namespace wigeon
