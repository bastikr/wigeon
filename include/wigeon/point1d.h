#pragma once

#include <array>

#include "wigeon/vector1d.h"


namespace wigeon {

struct Point1D {
  Point1D(double x) : data({{x}}) {}

  double& x() {return data[0];}

  double x() const {return data[0];}

  std::array<double, 1> data;
};

Point1D operator+(const Point1D&, const Vector1D&);
Point1D operator+(const Vector1D&, const Point1D&);
Point1D operator-(const Point1D&, const Vector1D&);

Vector1D operator-(const Point1D&, const Point1D&);

} // namespace wigeon
