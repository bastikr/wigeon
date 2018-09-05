#pragma once

#include <array>


namespace wigeon {

struct Point1D;

struct Vector1D {
  Vector1D() {}
  Vector1D(double x) : data({{x}}) {}
  explicit Vector1D(const Point1D&);

  double x() const {return data[0];}
  void set_x(double x) {data[0] = x;}

  double length2() const;
  double length() const;

  std::array<double, 1> data;
};


Vector1D operator+(const Vector1D&, const Vector1D&);

Vector1D operator-(const Vector1D&);
Vector1D operator-(const Vector1D&, const Vector1D&);

Vector1D operator*(const Vector1D&, double);
Vector1D operator*(double, const Vector1D&);
double operator*(const Vector1D&, const Vector1D&);

Vector1D operator/(const Vector1D&, double);


struct UnitVector1D : public Vector1D {
  UnitVector1D() {};
  UnitVector1D(double x): Vector1D(x<0 ? -1 : 1) {}
  UnitVector1D(const Vector1D& v) : UnitVector1D(v.x()) {}
};

} // namespace wigeon
