#pragma once

#include <array>


namespace wigeon {

struct Vector1D {
  Vector1D(double x) : data({{x}}) {}

  double x() const {return data[0];}

  double length2() const;
  double length() const;

  std::array<double, 1> data;
};


Vector1D operator+(const Vector1D& vector0, const Vector1D& vector1);

Vector1D operator-(const Vector1D& vector);
Vector1D operator-(const Vector1D& vector0, const Vector1D& vector1);

Vector1D operator*(const Vector1D& vector, double a);
Vector1D operator*(double a, const Vector1D& vector);
double operator*(const Vector1D& vector0, const Vector1D& vector1);

Vector1D operator/(const Vector1D& vector, double a);


struct UnitVector1D : public Vector1D {
  UnitVector1D(double x);
  UnitVector1D(const Vector1D& v) : Vector1D(v.x()<0 ? -1 : 0) {}
};

} // namespace wigeon
